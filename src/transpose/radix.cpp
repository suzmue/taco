#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "taco/taco_tensor_t.h"
#include <vector>

namespace taco {

struct coo_t
{
    int32_t idx[3];
    double val;
};

int transpose_radixsort(taco_tensor_t *A, taco_tensor_t *B)
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

    // Bucket into a hash table for level one
    int32_t A1_size = B1_size;
    std::vector<std::vector<int>> A1_count(A1_size);
    int C_temp_capacity = init_alloc_size;
    struct coo_t *C_temp = (struct coo_t *)malloc(sizeof(struct coo_t) * C_temp_capacity);

    int32_t c_size = 0;
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int kB = B2_idx_arr[B2_pos];
                if (C_temp_capacity <= (c_size + 1))
                {
                    int32_t C_capacity_new = 2 * (c_size + 1);
                    C_temp = (struct coo_t *)realloc(C_temp, sizeof(struct coo_t) * C_capacity_new);
                    C_temp_capacity = C_capacity_new;
                }
                C_temp[c_size].val = B_val_arr[B2_pos];
                C_temp[c_size].idx[0] = kB;
                C_temp[c_size].idx[1] = jB;
                C_temp[c_size].idx[2] = iB;

                A1_count[jB].push_back(c_size);

                c_size++;
            }
        }
    }

    // Bucket into hash table for level 0.
    int32_t A0_size = B2_size;
    std::vector<std::vector<int>> A0_count(A0_size);
    for (int32_t jA = 0; jA < A1_size; jA++)
    {
        for (uint32_t b = 0; b < A1_count[jA].size(); b++)
        {
            A0_count[C_temp[A1_count[jA][b]].idx[0]].push_back(A1_count[jA][b]);
        }
    }

    // Build output and pack.
    int *C = (int *)malloc(sizeof(int *) * c_size);
    int C_pos = 0;
    for (int32_t kA = 0; kA < A0_size; kA++)
    {
        for (uint32_t b = 0; b < A0_count[kA].size(); b++)
        {
            C[C_pos] = A0_count[kA][b];
            C_pos++;
        }
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
    int32_t C0_pos = 0;
    while (C0_pos < c_size)
    {
        int32_t iC = (C_temp[C[C0_pos]].idx[0]);
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (((C_temp[C[C0_end]].idx[0])) == iC))
        {
            C0_end++;
        }

        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        while (C1_pos < C0_end)
        {
            int32_t jC = (C_temp[C[C1_pos]].idx[1]);
            int32_t C1_end = C1_pos + 1;
            while ((C1_end < C0_end) && (((C_temp[C[C1_end]].idx[1])) == jC))
            {
                C1_end++;
            }

            int32_t A2_pos_start = A2_pos;
            for (int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++)
            {
                int32_t kC = (C_temp[C[C2_pos]].idx[2]);

                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1))
                {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C_temp[C[C2_pos]].val;

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
        A1_pos_arr[(A0_pos + 1)] = A1_pos;
        int32_t A1_pos_inserted = A1_pos - A1_pos_start;
        if (A1_pos_inserted > 0)
        {
            if (A0_idx_capacity <= A0_pos)
            {
                A0_idx_capacity = 2 * A0_pos;
                A0_idx_arr = (int *)realloc(A0_idx_arr, sizeof(int) * A0_idx_capacity);
            }
            A0_idx_arr[A0_pos] = iC;
            A0_pos++;
        }
        C0_pos = C0_end;
    }

    free(C);
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

int transpose_radixsort2(taco_tensor_t *A, taco_tensor_t *B)
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

    // Bucket into a hash table for level one
    int32_t A1_size = B1_size;
    std::vector<std::vector<int>> A1_count(A1_size);
    int8_t *A1_bool= (int8_t*)calloc(A1_size, sizeof(int8_t));

    std::vector<int> A1_idx;
    int C_temp_capacity = init_alloc_size;
    struct coo_t *C_temp = (struct coo_t *)malloc(sizeof(struct coo_t) * C_temp_capacity);

    int32_t c_size = 0;
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int kB = B2_idx_arr[B2_pos];
                if (C_temp_capacity <= (c_size + 1))
                {
                    int32_t C_capacity_new = 2 * (c_size + 1);
                    C_temp = (struct coo_t *)realloc(C_temp, sizeof(struct coo_t) * C_capacity_new);
                    C_temp_capacity = C_capacity_new;
                }
                C_temp[c_size].val = B_val_arr[B2_pos];
                C_temp[c_size].idx[0] = kB;
                C_temp[c_size].idx[1] = jB;
                C_temp[c_size].idx[2] = iB;

                if (!A1_bool[jB])
                {
                    A1_idx.push_back(jB);
                    A1_bool[jB] = 1;
                }

                A1_count[jB].push_back(c_size);
                c_size++;
            }
        }
    }

    // Bucket into hash table for level 0.
    std::sort(A1_idx.begin(), A1_idx.end());

    int32_t A0_size = B2_size;
    std::vector<std::vector<int>> A0_count(A0_size);
    int8_t *A0_bool= (int8_t*)calloc(A0_size, sizeof(int8_t));    
    std::vector<int> A0_idx;
    for (uint32_t jA_pos = 0; jA_pos < A1_idx.size(); jA_pos++)
    {
        int32_t jA = A1_idx[jA_pos];
        for (uint32_t b = 0; b < A1_count[jA].size(); b++)
        {
            int32_t kA = C_temp[A1_count[jA][b]].idx[0];
            if (!A0_bool[kA])
            {
                A0_idx.push_back(kA);
                A0_bool[kA] = 1;
            }

            A0_count[kA].push_back(A1_count[jA][b]);
        }
    }

    std::sort(A0_idx.begin(), A0_idx.end());
    // Build output and pack.
    int *C = (int *)malloc(sizeof(int *) * c_size);
    int C_pos = 0;
    for (uint32_t kA_pos = 0; kA_pos < A0_idx.size(); kA_pos++)
    {
        int32_t kA = A0_idx[kA_pos];
        for (uint32_t b = 0; b < A0_count[kA].size(); b++)
        {
            C[C_pos] = A0_count[kA][b];
            C_pos++;
        }
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
    int32_t C0_pos = 0;
    while (C0_pos < c_size)
    {
        int32_t iC = (C_temp[C[C0_pos]].idx[0]);
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (((C_temp[C[C0_end]].idx[0])) == iC))
        {
            C0_end++;
        }

        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        while (C1_pos < C0_end)
        {
            int32_t jC = (C_temp[C[C1_pos]].idx[1]);
            int32_t C1_end = C1_pos + 1;
            while ((C1_end < C0_end) && (((C_temp[C[C1_end]].idx[1])) == jC))
            {
                C1_end++;
            }

            int32_t A2_pos_start = A2_pos;
            for (int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++)
            {
                int32_t kC = (C_temp[C[C2_pos]].idx[2]);

                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1))
                {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C_temp[C[C2_pos]].val;

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
        A1_pos_arr[(A0_pos + 1)] = A1_pos;
        int32_t A1_pos_inserted = A1_pos - A1_pos_start;
        if (A1_pos_inserted > 0)
        {
            if (A0_idx_capacity <= A0_pos)
            {
                A0_idx_capacity = 2 * A0_pos;
                A0_idx_arr = (int *)realloc(A0_idx_arr, sizeof(int) * A0_idx_capacity);
            }
            A0_idx_arr[A0_pos] = iC;
            A0_pos++;
        }
        C0_pos = C0_end;
    }

    free(C);
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