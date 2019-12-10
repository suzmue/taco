#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "taco/taco_tensor_t.h"
#include <vector>

namespace taco {

struct coo_t
{
    int32_t idx1;
    int32_t idx2;
    double val;
};


int transpose_132(struct taco_tensor_t *A, struct taco_tensor_t *B)
{
    int32_t B0_size = B->dimensions[0];
    int32_t B1_size = B->dimensions[1];
    int32_t B2_size = B->dimensions[2];

    int *A0_pos_arr = (int *)(A->indices[0][0]);
    int *A0_idx_arr = (int *)(A->indices[0][1]);
    int *A1_pos_arr = (int *)(A->indices[1][0]);
    int *A1_idx_arr = (int *)(A->indices[1][1]);
    int *A2_pos_arr = (int *)(A->indices[2][0]);
    int *A2_idx_arr = (int *)(A->indices[2][1]);
    double *A_val_arr = (double *)(A->vals);

    int *B0_pos_arr = (int *)(B->indices[0][0]);
    int *B0_idx_arr = (int *)(B->indices[0][1]);
    int *B1_pos_arr = (int *)(B->indices[1][0]);
    int *B1_idx_arr = (int *)(B->indices[1][1]);
    int *B2_pos_arr = (int *)(B->indices[2][0]);
    int *B2_idx_arr = (int *)(B->indices[2][1]);
    double *B_val_arr = (double *)(B->vals);

    int32_t init_alloc_size = 1048576;

    int C_old_capacity = init_alloc_size;
    struct coo_t *C_old = (struct coo_t *)malloc(sizeof(struct coo_t) * C_old_capacity);

    int32_t c_size = 0;
    int num_subtrees = B0_pos_arr[1];
    int * C_counts = (int *)calloc(sizeof(int), num_subtrees + 1);
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        int count = 0;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int kB = B2_idx_arr[B2_pos];
                if (C_old_capacity <= (c_size + 1))
                {
                    int32_t C_capacity_new = 2 * (c_size + 1);
                    C_old = (struct coo_t *)realloc(C_old, sizeof(struct coo_t) * C_capacity_new);
                    C_old_capacity = C_capacity_new;
                }
                C_old[c_size].idx1 = kB;
                C_old[c_size].idx2 = jB;
                C_old[c_size].val = B_val_arr[B2_pos];
                count ++;

                c_size++;
            }
        }
        C_counts[B0_pos + 1] = C_counts[B0_pos] + count;
    } 


    struct coo_t *C_new = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
    struct coo_t *C_temp;

    // Do each of the sorts.
    int32_t *quotient = (int32_t*)malloc(c_size*sizeof(int32_t));
        int32_t *bucket = (int32_t*)malloc(c_size*sizeof(int32_t));
    int j = 0;
    for(int i = 0; i < num_subtrees; i ++){

        while(j < C_counts[i + 1]){
            quotient[j] = C_counts[i];
            bucket[j] = C_counts[i];
            std::cout << bucket[j] << std::endl;
            j ++;
        }
    }

    // count into a hash table for level 1
    int32_t A1_size = B2_size;
    int32_t *A1_count = (int32_t*)calloc(A1_size, sizeof(int32_t));
    for(int i = 0; i < c_size; i ++){
        int32_t kB = C_old[i].idx1;            
        A1_count[kB]++;
    }
    // Move data
    for(int iA = 1; iA < A1_size; iA ++){
        A1_count[iA] += A1_count[iA-1];
    }
    int *perm = (int *)malloc(c_size*sizeof(int));
    for(int i = c_size - 1; i >= 0; i --) {
        int32_t iA = C_old[i].idx1;            
        int idx = A1_count[iA] - 1;
        perm[idx] = i;
        A1_count[iA]--;
    }

    for (int i = 0; i < c_size; i ++) { 
        std::cout << bucket[perm[i]] << " " << quotient[bucket[perm[i]]] <<  " " << perm[i] << " " << C_old[perm[i]].val << std::endl;
        C_new[quotient[bucket[perm[i]]]] = C_old[perm[i]];
        std::cout << quotient[bucket[perm[i]]] << " " << C_new[quotient[bucket[perm[i]]]].val << std::endl;
        quotient[bucket[perm[i]]] ++;
    }

    //Swap
    C_temp = C_old;
    C_old = C_new;
    C_new = C_temp;

    for(int i = 0; i < c_size; i ++ ){
        std::cout <<  C_old[i].idx1 << " " <<  C_old[i].idx2 <<  " " << C_old[i].val << std::endl;
    }



    // pack C into A
    int32_t A0_pos_capacity = 2;
    int32_t A0_idx_capacity = init_alloc_size;
    A0_pos_arr = (int *)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int *)malloc(sizeof(int) * A0_idx_capacity);
    A0_pos_arr[0] = 0;
    int32_t A1_pos_capacity = init_alloc_size;
    int32_t A1_idx_capacity = init_alloc_size;
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);
    A1_pos_arr[0] = 0;
    int32_t A2_pos_capacity = init_alloc_size;
    int32_t A2_idx_capacity = init_alloc_size;
    A2_pos_arr = (int *)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr = (int *)malloc(sizeof(int) * A2_idx_capacity);
    A2_pos_arr[0] = 0;
    int32_t A_vals_capacity = init_alloc_size;
    A_val_arr = (double *)malloc(sizeof(double) * A_vals_capacity);

    int32_t A0_pos = 0;
    int32_t A1_pos = 0;
    int32_t A2_pos = 0;
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++) {
        int32_t iC = B0_idx_arr[B0_pos];
        std::cout << "iC: " << iC << std::endl;
        // int32_t C0_end = B0_pos + 1;
        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C_counts[B0_pos];
        int32_t C0_end = C_counts[B0_pos + 1];
                    std::cout << "C0_end: " << C0_end << std::endl;

        while (C1_pos < C0_end) {
            std::cout << "C1_pos: " << C1_pos << std::endl;

            int32_t jC = (C_old[C1_pos].idx1);
            std::cout << "jC: " << iC << std::endl;
            int32_t C1_end = C1_pos + 1;
            while ((C1_end < C0_end) && (((C_old[C1_end].idx1)) == jC))
            {
                C1_end++;
            }

            int32_t A2_pos_start = A2_pos;
            for (int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++)
            {

                int32_t kC = C_old[C2_pos].idx2;
                std::cout << "kC: " << kC << std::endl;
                std::cout << iC << ", "<< jC << ", " << kC << std::endl;

                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1))
                {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C_old[C2_pos].val;

                if (A2_idx_capacity <= A2_pos)
                {
                    A2_idx_capacity = 2 * A2_pos;
                    A2_idx_arr = (int *)realloc(A2_idx_arr, sizeof(int) * A2_idx_capacity);
                }
                A2_idx_arr[A2_pos] = kC;
                A2_pos++;
            }
            if (A2_pos_capacity <= (A1_pos + 1))
            {
                A2_pos_capacity = 2 * (A1_pos + 1);
                A2_pos_arr = (int *)realloc(A2_pos_arr, sizeof(int) * A2_pos_capacity);
            }
            A2_pos_arr[(A1_pos + 1)] = A2_pos;
            int32_t A2_pos_inserted = A2_pos - A2_pos_start;
            if (A2_pos_inserted > 0)
            {
                if (A1_idx_capacity <= A1_pos)
                {
                    A1_idx_capacity = 2 * A1_pos;
                    A1_idx_arr = (int *)realloc(A1_idx_arr, sizeof(int) * A1_idx_capacity);
                }
                std::cout << "A1_idx:" << A1_pos <<  " " << jC << std::endl;
                A1_idx_arr[A1_pos] = jC;
                A1_pos++;
            }
            C1_pos = C1_end;
        }
        if (A1_pos_capacity <= (A0_pos + 1))
        {
            A1_pos_capacity = 2 * (A0_pos + 1);
            A1_pos_arr = (int *)realloc(A1_pos_arr, sizeof(int) * A1_pos_capacity);
        }
        std::cout << "A1_pos: " << A0_pos + 1 << ", " << A1_pos << std::endl;
        A1_pos_arr[(A0_pos + 1)] = A1_pos;
        int32_t A1_pos_inserted = A1_pos - A1_pos_start;
        if (A1_pos_inserted > 0)
        {
            if (A0_idx_capacity <= A0_pos)
            {
                A0_idx_capacity = 2 * A0_pos;
                A0_idx_arr = (int *)realloc(A0_idx_arr, sizeof(int) * A0_idx_capacity);
            }
            std::cout << "A0: " << A0_pos << ", " << iC << std::endl;
            A0_idx_arr[A0_pos] = iC;
            A0_pos++;
        }
    }

    free(C_new);
    free(C_old);

    A0_pos_arr[(0 + 1)] = A0_pos;

    A->indices[0][0] = (uint8_t *)(A0_pos_arr);
    A->indices[0][1] = (uint8_t *)(A0_idx_arr);
    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->indices[2][0] = (uint8_t *)(A2_pos_arr);
    A->indices[2][1] = (uint8_t *)(A2_idx_arr);
    A->vals = (uint8_t *)A_val_arr;

    return 0;
}
}