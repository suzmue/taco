#ifndef TACO_TRANSPOSE_H
#define TACO_TRANSPOSE_H

#include "taco/taco_tensor_t.h"

namespace taco {
// 3rd-order transpose implementation for CSF
int transpose_qsort(taco_tensor_t* A, taco_tensor_t* B);
int transpose_bylevel(taco_tensor_t* A, taco_tensor_t* B);
int transpose_onepass(taco_tensor_t* A, taco_tensor_t* B);
int transpose(taco_tensor_t* A, taco_tensor_t* B);



// Implementations
int transpose(taco_tensor_t* A, taco_tensor_t* B){
    return transpose_qsort(A, B);
}


struct coo_t{
    int32_t idx[3];
    double val;
};


int compare_coords(const void*p,const void*q){
    // Get the values at given addresses 
    struct coo_t l = *(struct coo_t*)p; 
    struct coo_t r = *(struct coo_t*)q; 
    
    if (l.idx[0] < r.idx[0] ) {
        return -1;
    } else if (l.idx[0] > r.idx[0]){
        return 1;
    }

    if (l.idx[1] < r.idx[1] ) {
        return -1;
    } else if (l.idx[1] > r.idx[1]){
        return 1;
    }

    if (l.idx[2] < r.idx[2] ) {
        return -1;
    } else if (l.idx[2] > r.idx[2]){
        return 1;
    }
    
    return 0;
}


int transpose_qsort(taco_tensor_t *A, taco_tensor_t *B) {
    int* A0_pos_arr = (int*)(A->indices[0][0]);
    int* A0_idx_arr = (int*)(A->indices[0][1]);
    int* A1_pos_arr = (int*)(A->indices[1][0]);
    int* A1_idx_arr = (int*)(A->indices[1][1]);
    int* A2_pos_arr = (int*)(A->indices[2][0]);
    int* A2_idx_arr = (int*)(A->indices[2][1]);
    double* A_val_arr = (double*)(A->vals);

    int*  B0_pos_arr = (int*)(B->indices[0][0]);
    int*  B0_idx_arr = (int*)(B->indices[0][1]);
    int*  B1_pos_arr = (int*)(B->indices[1][0]);
    int*  B1_idx_arr = (int*)(B->indices[1][1]);
    int*  B2_pos_arr = (int*)(B->indices[2][0]);
    int*  B2_idx_arr = (int*)(B->indices[2][1]);
    double*  B_val_arr = (double*)(B->vals);

    // Unpack B into C (in coo)

    int32_t init_alloc_size = 1048576;
    int32_t C_capacity = init_alloc_size;
    int32_t c_size = 0;
    struct coo_t *C = (struct coo_t *)malloc(sizeof(struct coo_t) * C_capacity);

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
        int32_t iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
                int32_t kB = B2_idx_arr[B2_pos];
                if (C_capacity <= (c_size + 1)) {
                    int32_t C_capacity_new = 2 * (c_size + 1);
                    C = (struct coo_t *)realloc(C, sizeof(struct coo_t) * C_capacity_new);
                    C_capacity = C_capacity_new;
                }
                C[c_size].val = B_val_arr[B2_pos];
                C[c_size].idx[0] = kB;
                C[c_size].idx[1] = jB;
                C[c_size].idx[2] = iB;

                c_size++;
            }
        }
    }
    // sort COO
    qsort(C, c_size, sizeof(struct coo_t), compare_coords);

    // pack C into A
    int32_t A0_pos_capacity = init_alloc_size;
    int32_t A0_idx_capacity = init_alloc_size;
    A0_pos_arr = (int*)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int*)malloc(sizeof(int) * A0_idx_capacity);
    A0_pos_arr[0] = 0;
    int32_t A1_pos_capacity = init_alloc_size;
    int32_t A1_idx_capacity = init_alloc_size;
    A1_pos_arr = (int*)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int*)malloc(sizeof(int) * A1_idx_capacity);
    A1_pos_arr[0] = 0;
    int32_t A2_pos_capacity = init_alloc_size;
    int32_t A2_idx_capacity = init_alloc_size;
    A2_pos_arr = (int*)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr = (int*)malloc(sizeof(int) * A2_idx_capacity);
    A2_pos_arr[0] = 0;
    int32_t A_vals_capacity = init_alloc_size;
    A_val_arr = (double*)malloc(sizeof(double) * A_vals_capacity);

    int32_t A0_pos = 0;
    int32_t A1_pos = 0;
    int32_t A2_pos = 0;
    int32_t C0_pos = 0;
    while (C0_pos < c_size) {
        int32_t iC = C[C0_pos].idx[0];
        int32_t C0_end = C0_pos + 1;
        while((C0_end < c_size) && (C[C0_end].idx[0] == iC)){
            C0_end ++;
        }

        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        while(C1_pos < C0_end) {
            int32_t jC = C[C1_pos].idx[1];
            int32_t C1_end = C1_pos + 1;
            while((C1_end < C0_end) && (C[C1_end].idx[1] == jC)){
                C1_end ++;
            }

            int32_t A2_pos_start = A2_pos;
            for(int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++){
                int32_t kC = C[C2_pos].idx[2];
                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1)) {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double*)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C[C2_pos].val;

                if (A2_idx_capacity <= A2_pos) {
                    A2_idx_capacity = 2 * A2_pos;
                    A2_idx_arr = (int*)realloc(A2_idx_arr, sizeof(int) * A2_idx_capacity);
                }
                A2_idx_arr[A2_pos] = kC;
                A2_pos++;
            }
                if (A2_pos_capacity <= (A1_pos + 1)) {
                A2_pos_capacity = 2 * (A1_pos + 1);
                A2_pos_arr = (int*)realloc(A2_pos_arr, sizeof(int) * A2_pos_capacity);
            }
            A2_pos_arr[(A1_pos + 1)] = A2_pos;
            int32_t A2_pos_inserted = A2_pos - A2_pos_start;
            if (A2_pos_inserted > 0) {
                if (A1_idx_capacity <= A1_pos) {
                    A1_idx_capacity = 2 * A1_pos;
                    A1_idx_arr = (int*)realloc(A1_idx_arr, sizeof(int) * A1_idx_capacity);
                }
                A1_idx_arr[A1_pos] = jC;
                A1_pos++;
            }
            C1_pos = C1_end;
        }
        if (A1_pos_capacity <= (A0_pos + 1)) {
            A1_pos_capacity = 2 * (A0_pos + 1);
            A1_pos_arr = (int*)realloc(A1_pos_arr, sizeof(int) * A1_pos_capacity);
        }
        A1_pos_arr[(A0_pos + 1)] = A1_pos;
        int32_t A1_pos_inserted = A1_pos - A1_pos_start;
        if (A1_pos_inserted > 0) {
            if (A0_idx_capacity <= A0_pos) {
                A0_idx_capacity = 2 * A0_pos;
                A0_idx_arr = (int*)realloc(A0_idx_arr, sizeof(int) * A0_idx_capacity);
            }
            A0_idx_arr[A0_pos] = iC;
            A0_pos++;
        }
        C0_pos = C0_end;
    }

    free(C);
    A0_pos_arr[(0 + 1)] = A0_pos;

    A->indices[0][0] = (uint8_t*)(A0_pos_arr);
    A->indices[0][1] = (uint8_t*)(A0_idx_arr);
    A->indices[1][0] = (uint8_t*)(A1_pos_arr);
    A->indices[1][1] = (uint8_t*)(A1_idx_arr);
    A->indices[2][0] = (uint8_t*)(A2_pos_arr);
    A->indices[2][1] = (uint8_t*)(A2_idx_arr);
    A->vals = (uint8_t*)A_val_arr;

    return 0;
}

int transpose_bylevel(taco_tensor_t* A, taco_tensor_t* B) {
      int* A0_pos_arr = (int*)(A->indices[0][0]);
  int* A0_idx_arr = (int*)(A->indices[0][1]);
  int* A1_pos_arr = (int*)(A->indices[1][0]);
  int* A1_idx_arr = (int*)(A->indices[1][1]);
  int* A2_pos_arr = (int*)(A->indices[2][0]);
  int* A2_idx_arr = (int*)(A->indices[2][1]);
  double* A_val_arr = (double*)(A->vals);

  int* B0_pos_arr = (int*)(B->indices[0][0]);
  int* B0_idx_arr = (int*)(B->indices[0][1]);
  int* B1_pos_arr = (int*)(B->indices[1][0]);
  int* B1_idx_arr = (int*)(B->indices[1][1]);
  int* B2_pos_arr = (int*)(B->indices[2][0]);
  int* B2_idx_arr = (int*)(B->indices[2][1]);
  double* B_val_arr = (double*)(B->vals);

  // Allocate space in A.
  // Allocate A0 (store ks).
  int32_t B2_dim = B->dimensions[2];
  int32_t k_count_capacity = B2_dim + 1;
  int32_t *k_count_arr = (int32_t *)calloc(k_count_capacity, sizeof(int32_t)); 

  for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
    int32_t B0_end = B0_pos + 1;
    for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
      int32_t B1_end = B1_pos + 1;
      for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
        int32_t kB = B2_idx_arr[B2_pos];
        k_count_arr[kB + 1] = 1;
      }
    }
  }

  for(int k_count_pos = 1; k_count_pos < k_count_capacity; k_count_pos ++) {
    k_count_arr[k_count_pos] = k_count_arr[k_count_pos - 1] + k_count_arr[k_count_pos];
  }

  int32_t A0_pos_capacity = 2;
  int32_t A0_idx_capacity = k_count_arr[k_count_capacity - 1];
  A0_pos_arr = (int*)malloc(sizeof(int) * A0_pos_capacity);
  A0_idx_arr = (int*)malloc(sizeof(int) * A0_idx_capacity);

  A0_pos_arr[0] = 0;
  A0_pos_arr[1] = k_count_arr[k_count_capacity - 1];

  int32_t A0_pos = 0;
  for(int k_count_idx = 0; k_count_idx < k_count_capacity - 1; k_count_idx ++) {
    if(k_count_arr[k_count_idx] < k_count_arr[k_count_idx + 1]) {
      A0_idx_arr[A0_pos] = k_count_idx;
      A0_pos ++;
    }
  }

  // Allocate A1 (store js / k).
  int32_t B1_dim = B->dimensions[1];
  int32_t nnzk = k_count_arr[k_count_capacity - 1];
  int32_t j_count_capacity = (B1_dim * nnzk) + 1;

  int32_t *j_count_arr = (int32_t *)calloc(j_count_capacity, sizeof(int32_t)); 

  for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
    int32_t B0_end = B0_pos + 1;
    for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
      int32_t jB = B1_idx_arr[B1_pos];
      int32_t B1_end = B1_pos + 1;
      for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
        int32_t kB = B2_idx_arr[B2_pos];

        int32_t j_count_pos = (B1_dim * k_count_arr[kB]) + jB + 1;
        j_count_arr[j_count_pos] = 1;
      }
    }
  }

  for(int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos ++) {
    j_count_arr[j_count_pos] = j_count_arr[j_count_pos - 1] + j_count_arr[j_count_pos];
  }

  int32_t A1_pos_capacity = k_count_arr[B2_dim] + 1;
  int32_t A1_idx_capacity = j_count_arr[j_count_capacity - 1];
  A1_pos_arr = (int*)malloc(sizeof(int) * A1_pos_capacity);
  A1_idx_arr = (int*)malloc(sizeof(int) * A1_idx_capacity);
  
  A1_pos_arr[0] = 0;
  for(int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++) {
    A1_pos_arr[A0_pos + 1] = j_count_arr[(A0_pos + 1) * B1_dim];
  }

  int32_t A1_pos = 0;
  for(int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos ++) {
    if(j_count_arr[j_count_pos - 1] < j_count_arr[j_count_pos]) {
      A1_idx_arr[A1_pos] = (j_count_pos - 1) %  B1_dim;
      A1_pos ++;
    }
  }

  // Allocate A2 (store is / (k,j))
  int32_t nnzkj = j_count_arr[j_count_capacity - 1];
  int32_t i_count_capacity = nnzkj + 1;

  int32_t *i_count_arr = (int32_t *)calloc(i_count_capacity, sizeof(int32_t)); 


  for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
    int32_t B0_end = B0_pos + 1;
    for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
      int32_t jB = B1_idx_arr[B1_pos];
      int32_t B1_end = B1_pos + 1;
      for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
        int32_t kB = B2_idx_arr[B2_pos];
        int i_count_pos = j_count_arr[B1_dim * k_count_arr[kB] + jB] + 1;
        i_count_arr[i_count_pos] ++;
      }
    }
  }

  for(int32_t i_count_pos = 1; i_count_pos < i_count_capacity; i_count_pos++ ) {
    i_count_arr[i_count_pos] = i_count_arr[i_count_pos - 1] + i_count_arr[i_count_pos];
  }

  int32_t A2_pos_capacity = i_count_capacity;
  int32_t A2_idx_capacity = i_count_arr[i_count_capacity - 1];
  int32_t A2_vals_capacity = A2_idx_capacity;

  A2_pos_arr  = (int *)malloc(sizeof(int) * A2_pos_capacity);
  A2_idx_arr  = (int *)malloc(sizeof(int) * A2_idx_capacity);
  A_val_arr = (double *)malloc(sizeof(double) * A2_vals_capacity);
  A2_pos_arr[0] = 0;

  memcpy(A2_pos_arr, i_count_arr, sizeof(int) * i_count_capacity);

  // Fill in values and last level indices.
  for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
    int32_t iB = B0_idx_arr[B0_pos];
    int32_t B0_end = B0_pos + 1;
    for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
      int32_t jB = B1_idx_arr[B1_pos];
      int32_t B1_end = B1_pos + 1;
      for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
        int32_t kB = B2_idx_arr[B2_pos];
        int A2_pos = i_count_arr[j_count_arr[B1_dim * k_count_arr[kB] + jB]];

        A2_idx_arr[A2_pos] = iB;
        A_val_arr[A2_pos] = B_val_arr[B2_pos];

        i_count_arr[j_count_arr[B1_dim * k_count_arr[kB] + jB]]++;
      }
    }
  }
  
  free(i_count_arr);
  free(j_count_arr);
  free(k_count_arr);

  A->indices[0][0] = (uint8_t*)(A0_pos_arr);
  A->indices[0][1] = (uint8_t*)(A0_idx_arr);
  A->indices[1][0] = (uint8_t*)(A1_pos_arr);
  A->indices[1][1] = (uint8_t*)(A1_idx_arr);
  A->indices[2][0] = (uint8_t*)(A2_pos_arr);
  A->indices[2][1] = (uint8_t*)(A2_idx_arr);
  A->vals = (uint8_t*)A_val_arr;
  return 0;
}


int transpose_onepass(taco_tensor_t *A, taco_tensor_t *B) {
    int* A0_pos_arr = (int*)(A->indices[0][0]);
    int* A0_idx_arr = (int*)(A->indices[0][1]);
    int* A1_pos_arr = (int*)(A->indices[1][0]);
    int* A1_idx_arr = (int*)(A->indices[1][1]);
    int* A2_pos_arr = (int*)(A->indices[2][0]);
    int* A2_idx_arr = (int*)(A->indices[2][1]);
    double* A_val_arr = (double*)(A->vals);

    int* B0_pos_arr = (int*)(B->indices[0][0]);
    int* B0_idx_arr = (int*)(B->indices[0][1]);
    int* B1_pos_arr = (int*)(B->indices[1][0]);
    int* B1_idx_arr = (int*)(B->indices[1][1]);
    int* B2_pos_arr = (int*)(B->indices[2][0]);
    int* B2_idx_arr = (int*)(B->indices[2][1]);
    double* B_val_arr = (double*)(B->vals);

    // Allocate space in A.
    // Allocate A0 (store ks).
    int32_t B2_dim = B->dimensions[2];
    int32_t k_count_capacity = B2_dim + 1;
    int32_t *k_count_arr = (int32_t *)calloc(k_count_capacity, sizeof(int32_t)); 

    int32_t B1_dim = B->dimensions[1];
    int32_t j_count_capacity = (B1_dim * B2_dim) + 1;
    int32_t *j_count_arr = (int32_t *)calloc(j_count_capacity, sizeof(int32_t)); 

    int32_t i_count_capacity = (B1_dim * B2_dim) + 1;
    int32_t *i_count_arr = (int32_t *)calloc(i_count_capacity, sizeof(int32_t)); 





    for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
        int32_t B0_end = B0_pos + 1;
        for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
                int32_t kB = B2_idx_arr[B2_pos];

                int k_count_pos = kB + 1;
                k_count_arr[k_count_pos] = 1;

                int j_count_pos = B1_dim * kB + jB + 1;
                j_count_arr[j_count_pos] = 1;

                int i_count_pos = B1_dim * kB + jB + 1;
                i_count_arr[i_count_pos] ++;

            }
        }
    }

    for(int k_count_pos = 1; k_count_pos < k_count_capacity; k_count_pos ++) {
        k_count_arr[k_count_pos] = k_count_arr[k_count_pos - 1] + k_count_arr[k_count_pos];
    }

    int32_t A0_pos_capacity = 2;
    int32_t A0_idx_capacity = k_count_arr[k_count_capacity - 1];
    A0_pos_arr = (int*)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int*)malloc(sizeof(int) * A0_idx_capacity);

    A0_pos_arr[0] = 0;
    A0_pos_arr[1] = k_count_arr[k_count_capacity - 1];

    int32_t A0_pos = 0;
    for(int k_count_idx = 0; k_count_idx < k_count_capacity - 1; k_count_idx ++) {
        if(k_count_arr[k_count_idx] < k_count_arr[k_count_idx + 1]) {
            A0_idx_arr[A0_pos] = k_count_idx;
            A0_pos ++;
        }
    }

    // Allocate A1 (store js / k).
    for(int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos ++) {
        j_count_arr[j_count_pos] = j_count_arr[j_count_pos - 1] + j_count_arr[j_count_pos];
    }

    int32_t A1_pos_capacity = k_count_arr[B2_dim] + 1;
    int32_t A1_idx_capacity = j_count_arr[j_count_capacity - 1];
    A1_pos_arr = (int*)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int*)malloc(sizeof(int) * A1_idx_capacity);
    
    A1_pos_arr[0] = 0;
    for(int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++) {
        A1_pos_arr[A0_pos + 1] = j_count_arr[(A0_idx_arr[A0_pos] + 1) * B1_dim];
    }

    int32_t A1_pos = 0;
    for(int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos ++) {
        if(j_count_arr[j_count_pos - 1] < j_count_arr[j_count_pos]) {
            A1_idx_arr[A1_pos] = (j_count_pos - 1) %    B1_dim;
            A1_pos ++;
        }
    }

    // Allocate A2 (store is / (k,j))
    for(int32_t i_count_pos = 1; i_count_pos < i_count_capacity; i_count_pos++ ) {
        i_count_arr[i_count_pos] = i_count_arr[i_count_pos - 1] + i_count_arr[i_count_pos];
    }

    int32_t A2_pos_capacity = i_count_capacity;
    int32_t A2_idx_capacity = i_count_arr[i_count_capacity - 1];
    int32_t A2_vals_capacity = A2_idx_capacity;

    A2_pos_arr    = (int *)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr    = (int *)malloc(sizeof(int) * A2_idx_capacity);
    A_val_arr = (double *)malloc(sizeof(double) * A2_vals_capacity);
    
    A2_pos_arr[0] = 0;
    for(int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos ++){
        for(int32_t A1_pos = A1_pos_arr[A0_pos]; A1_pos < A1_pos_arr[A0_pos + 1]; A1_pos++) {
            A2_pos_arr[A1_pos + 1] = i_count_arr[(A0_idx_arr[A0_pos] * B1_dim) + A1_idx_arr[A1_pos] + 1];
        }
    }

    // Fill in values and last level indices.
    for(int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
        int32_t iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for(int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++) {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for(int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++) {
                int32_t kB = B2_idx_arr[B2_pos];

                int i_count_pos = B1_dim * kB + jB;
                int A2_pos = i_count_arr[i_count_pos];

                A2_idx_arr[A2_pos] = iB;
                A_val_arr[A2_pos] = B_val_arr[B2_pos];

                i_count_arr[i_count_pos]++;
            }
        }
    }

  free(i_count_arr);
  free(j_count_arr);
  free(k_count_arr);

    A->indices[0][0] = (uint8_t*)(A0_pos_arr);
    A->indices[0][1] = (uint8_t*)(A0_idx_arr);
    A->indices[1][0] = (uint8_t*)(A1_pos_arr);
    A->indices[1][1] = (uint8_t*)(A1_idx_arr);
    A->indices[2][0] = (uint8_t*)(A2_pos_arr);
    A->indices[2][1] = (uint8_t*)(A2_idx_arr);
    A->vals = (uint8_t*)A_val_arr;
    return 0;
}

}


#endif
