#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "taco/taco_tensor_t.h"


namespace taco {

int transpose_bylevel(taco_tensor_t *A, taco_tensor_t *B)
{
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

    // Allocate space in A.
    // Allocate A0 (store ks).
    int32_t B2_dim = B->dimensions[2];
    int32_t k_count_capacity = B2_dim + 1;
    int32_t *k_count_arr = (int32_t *)calloc(k_count_capacity, sizeof(int32_t));

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int32_t kB = B2_idx_arr[B2_pos];
                k_count_arr[kB + 1] = 1;
            }
        }
    }

    for (int k_count_pos = 1; k_count_pos < k_count_capacity; k_count_pos++)
    {
        k_count_arr[k_count_pos] = k_count_arr[k_count_pos - 1] + k_count_arr[k_count_pos];
    }

    int32_t A0_pos_capacity = 2;
    int32_t A0_idx_capacity = k_count_arr[k_count_capacity - 1];
    A0_pos_arr = (int *)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int *)malloc(sizeof(int) * A0_idx_capacity);

    A0_pos_arr[0] = 0;
    A0_pos_arr[1] = k_count_arr[k_count_capacity - 1];

    int32_t A0_pos = 0;
    for (int k_count_idx = 0; k_count_idx < k_count_capacity - 1; k_count_idx++)
    {
        if (k_count_arr[k_count_idx] < k_count_arr[k_count_idx + 1])
        {
            A0_idx_arr[A0_pos] = k_count_idx;
            A0_pos++;
        }
    }

    // Allocate A1 (store js / k).
    int32_t B1_dim = B->dimensions[1];
    int32_t nnzk = k_count_arr[k_count_capacity - 1];
    int32_t j_count_capacity = (B1_dim * nnzk) + 1;

    int32_t *j_count_arr = (int32_t *)calloc(j_count_capacity, sizeof(int32_t));

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int32_t kB = B2_idx_arr[B2_pos];

                int32_t j_count_pos = (B1_dim * k_count_arr[kB]) + jB + 1;
                j_count_arr[j_count_pos] = 1;
            }
        }
    }

    for (int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos++)
    {
        j_count_arr[j_count_pos] = j_count_arr[j_count_pos - 1] + j_count_arr[j_count_pos];
    }

    int32_t A1_pos_capacity = k_count_arr[B2_dim] + 1;
    int32_t A1_idx_capacity = j_count_arr[j_count_capacity - 1];
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);

    A1_pos_arr[0] = 0;
    for (int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        A1_pos_arr[A0_pos + 1] = j_count_arr[(A0_pos + 1) * B1_dim];
    }

    int32_t A1_pos = 0;
    for (int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos++)
    {
        if (j_count_arr[j_count_pos - 1] < j_count_arr[j_count_pos])
        {
            A1_idx_arr[A1_pos] = (j_count_pos - 1) % B1_dim;
            A1_pos++;
        }
    }

    // Allocate A2 (store is / (k,j))
    int32_t nnzkj = j_count_arr[j_count_capacity - 1];
    int32_t i_count_capacity = nnzkj + 1;

    int32_t *i_count_arr = (int32_t *)calloc(i_count_capacity, sizeof(int32_t));

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int32_t kB = B2_idx_arr[B2_pos];
                int i_count_pos = j_count_arr[B1_dim * k_count_arr[kB] + jB] + 1;
                i_count_arr[i_count_pos]++;
            }
        }
    }

    for (int32_t i_count_pos = 1; i_count_pos < i_count_capacity; i_count_pos++)
    {
        i_count_arr[i_count_pos] = i_count_arr[i_count_pos - 1] + i_count_arr[i_count_pos];
    }

    int32_t A2_pos_capacity = i_count_capacity;
    int32_t A2_idx_capacity = i_count_arr[i_count_capacity - 1];
    int32_t A2_vals_capacity = A2_idx_capacity;

    A2_pos_arr = (int *)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr = (int *)malloc(sizeof(int) * A2_idx_capacity);
    A_val_arr = (double *)malloc(sizeof(double) * A2_vals_capacity);
    A2_pos_arr[0] = 0;

    memcpy(A2_pos_arr, i_count_arr, sizeof(int) * i_count_capacity);

    // Fill in values and last level indices.
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
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

    A->indices[0][0] = (uint8_t *)(A0_pos_arr);
    A->indices[0][1] = (uint8_t *)(A0_idx_arr);
    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->indices[2][0] = (uint8_t *)(A2_pos_arr);
    A->indices[2][1] = (uint8_t *)(A2_idx_arr);
    A->vals = (uint8_t *)A_val_arr;
    return 0;
}

int transpose_onepass(taco_tensor_t *A, taco_tensor_t *B)
{
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

    // A(k, j i) = B(i, j, k)
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

    // TODO(suzmue):
    // - just count js/ k
    // -

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int32_t kB = B2_idx_arr[B2_pos];

                int k_count_pos = kB + 1;
                k_count_arr[k_count_pos] = 1;

                int j_count_pos = B1_dim * kB + jB + 1;
                j_count_arr[j_count_pos] = 1;

                int i_count_pos = B1_dim * kB + jB + 1;
                i_count_arr[i_count_pos]++;
            }
        }
    }

    for (int k_count_pos = 1; k_count_pos < k_count_capacity; k_count_pos++)
    {
        k_count_arr[k_count_pos] = k_count_arr[k_count_pos - 1] + k_count_arr[k_count_pos];
    }

    int32_t A0_pos_capacity = 2;
    int32_t A0_idx_capacity = k_count_arr[k_count_capacity - 1];
    A0_pos_arr = (int *)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int *)malloc(sizeof(int) * A0_idx_capacity);

    A0_pos_arr[0] = 0;
    A0_pos_arr[1] = k_count_arr[k_count_capacity - 1];

    int32_t A0_pos = 0;
    for (int k_count_idx = 0; k_count_idx < k_count_capacity - 1; k_count_idx++)
    {
        if (k_count_arr[k_count_idx] < k_count_arr[k_count_idx + 1])
        {
            A0_idx_arr[A0_pos] = k_count_idx;
            A0_pos++;
        }
    }

    // Allocate A1 (store js / k).
    for (int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos++)
    {
        j_count_arr[j_count_pos] = j_count_arr[j_count_pos - 1] + j_count_arr[j_count_pos];
    }

    int32_t A1_pos_capacity = k_count_arr[B2_dim] + 1;
    int32_t A1_idx_capacity = j_count_arr[j_count_capacity - 1];
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);

    A1_pos_arr[0] = 0;
    for (int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        A1_pos_arr[A0_pos + 1] = j_count_arr[(A0_idx_arr[A0_pos] + 1) * B1_dim];
    }

    int32_t A1_pos = 0;
    for (int j_count_pos = 1; j_count_pos < j_count_capacity; j_count_pos++)
    {
        if (j_count_arr[j_count_pos - 1] < j_count_arr[j_count_pos])
        {
            A1_idx_arr[A1_pos] = (j_count_pos - 1) % B1_dim;
            A1_pos++;
        }
    }

    // Allocate A2 (store is / (k,j))
    for (int32_t i_count_pos = 1; i_count_pos < i_count_capacity; i_count_pos++)
    {
        i_count_arr[i_count_pos] = i_count_arr[i_count_pos - 1] + i_count_arr[i_count_pos];
    }

    int32_t A2_pos_capacity = i_count_capacity;
    int32_t A2_idx_capacity = i_count_arr[i_count_capacity - 1];
    int32_t A2_vals_capacity = A2_idx_capacity;

    A2_pos_arr = (int *)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr = (int *)malloc(sizeof(int) * A2_idx_capacity);
    A_val_arr = (double *)malloc(sizeof(double) * A2_vals_capacity);

    A2_pos_arr[0] = 0;
    for (int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        for (int32_t A1_pos = A1_pos_arr[A0_pos]; A1_pos < A1_pos_arr[A0_pos + 1]; A1_pos++)
        {
            A2_pos_arr[A1_pos + 1] = i_count_arr[(A0_idx_arr[A0_pos] * B1_dim) + A1_idx_arr[A1_pos] + 1];
        }
    }

    // Fill in values and last level indices.
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
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

    A->indices[0][0] = (uint8_t *)(A0_pos_arr);
    A->indices[0][1] = (uint8_t *)(A0_idx_arr);
    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->indices[2][0] = (uint8_t *)(A2_pos_arr);
    A->indices[2][1] = (uint8_t *)(A2_idx_arr);
    A->vals = (uint8_t *)A_val_arr;
    return 0;
}

int transpose_onepass_opt(taco_tensor_t *A, taco_tensor_t *B)
{
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

    // A(k, j, i) = B(i, j, k)
    // Allocate space in A.
    // Allocate A0 (store ks).
    // TODO(suzmue): remove j_count_arr
    int32_t B2_dim = B->dimensions[2];
    int32_t k_count_capacity = B2_dim + 1;
    int32_t *k_count_arr = (int32_t *)calloc(k_count_capacity, sizeof(int32_t));

    int32_t B1_dim = B->dimensions[1];
    int32_t j_count_capacity = (B1_dim * B2_dim) + 1;
    int32_t *j_count_arr = (int32_t *)calloc(j_count_capacity, sizeof(int32_t));

    int32_t i_count_capacity = (B1_dim * B2_dim) + 1;
    int32_t *i_count_arr = (int32_t *)calloc(i_count_capacity, sizeof(int32_t));

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                int32_t kB = B2_idx_arr[B2_pos];

                int k_count_pos = kB + 1;
                k_count_arr[k_count_pos] = 1;

                int j_count_pos = B1_dim * kB + jB + 1;
                j_count_arr[j_count_pos] = 1;

                int i_count_pos = B1_dim * kB + jB + 1;
                i_count_arr[i_count_pos]++;
            }
        }
    }

    for (int k_count_pos = 1; k_count_pos < k_count_capacity; k_count_pos++)
    {
        k_count_arr[k_count_pos] = k_count_arr[k_count_pos - 1] + k_count_arr[k_count_pos];
    }

    int32_t A0_pos_capacity = 2;
    int32_t A0_idx_capacity = k_count_arr[k_count_capacity - 1];
    A0_pos_arr = (int *)malloc(sizeof(int) * A0_pos_capacity);
    A0_idx_arr = (int *)malloc(sizeof(int) * A0_idx_capacity);

    A0_pos_arr[0] = 0;
    A0_pos_arr[1] = k_count_arr[k_count_capacity - 1];

    int32_t A0_pos = 0;
    for (int k_count_idx = 0; k_count_idx < k_count_capacity - 1; k_count_idx++)
    {
        if (k_count_arr[k_count_idx] < k_count_arr[k_count_idx + 1])
        {
            A0_idx_arr[A0_pos] = k_count_idx;
            A0_pos++;
        }
    }

    // Allocate A1 (store js / k).

    int last_j = 0;
    int last_i = 0;
    for (int A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        int offset = A0_idx_arr[A0_pos] * B1_dim + 1;
        j_count_arr[offset - 1] = last_j;
        i_count_arr[offset - 1] = last_i;
        for (int count_pos = offset; count_pos < offset + B1_dim; count_pos++)
        {
            j_count_arr[count_pos] = last_j + j_count_arr[count_pos];
            i_count_arr[count_pos] = last_i + i_count_arr[count_pos];
            last_j = j_count_arr[count_pos];
            last_i = i_count_arr[count_pos];
        }
    }

    int32_t A1_pos_capacity = k_count_arr[B2_dim] + 1;
    int32_t A1_idx_capacity = j_count_arr[j_count_capacity - 1];
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);

    A1_pos_arr[0] = 0;

    for (int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        A1_pos_arr[A0_pos + 1] = j_count_arr[(A0_idx_arr[A0_pos] + 1) * B1_dim];
    }

    int32_t A1_pos = 0;
    for (int A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        int offset = A0_idx_arr[A0_pos] * B1_dim + 1;
        for (int count_pos = offset; count_pos < offset + B1_dim; count_pos++)
        {
            if (j_count_arr[count_pos - 1] < j_count_arr[count_pos])
            {
                A1_idx_arr[A1_pos] = (count_pos - 1) % B1_dim;
                A1_pos++;
            }
        }
    }

    // Allocate A2 (store is / (k,j))

    int32_t A2_pos_capacity = A1_idx_capacity + 1;
    int32_t A2_idx_capacity = i_count_arr[i_count_capacity - 1];
    int32_t A2_vals_capacity = A2_idx_capacity;

    A2_pos_arr = (int *)malloc(sizeof(int) * A2_pos_capacity);
    A2_idx_arr = (int *)malloc(sizeof(int) * A2_idx_capacity);
    A_val_arr = (double *)malloc(sizeof(double) * A2_vals_capacity);

    A2_pos_arr[0] = 0;

    for (int32_t A0_pos = 0; A0_pos < A0_pos_arr[1]; A0_pos++)
    {
        for (int32_t A1_pos = A1_pos_arr[A0_pos]; A1_pos < A1_pos_arr[A0_pos + 1]; A1_pos++)
        {
            A2_pos_arr[A1_pos + 1] = i_count_arr[B1_dim * A0_idx_arr[A0_pos] + A1_idx_arr[A1_pos] + 1];
        }
    }

    // Fill in values and last level indices.
    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        int32_t iB = B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
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