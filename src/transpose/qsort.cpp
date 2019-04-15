#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "taco/taco_tensor_t.h"


namespace taco{
// transpose_qsort transposes by converting to COO and sort.

struct coo_t
{
    int32_t idx[3];
    double val;
};

struct coord_t
{
    uint64_t crd;
    double val;
};

int compare_crd_vals(const void *p, const void *q)
{
    uint64_t r = ((struct coord_t *)p)->crd;
    uint64_t s = ((struct coord_t *)q)->crd;
    return (r < s) ? -1 : 1;
}

int compare_coords(const void *p, const void *q)
{
    // Get the values at given addresses
    struct coo_t l = *(struct coo_t *)p;
    struct coo_t r = *(struct coo_t *)q;

    if (l.idx[0] < r.idx[0])
    {
        return -1;
    }
    else if (l.idx[0] > r.idx[0])
    {
        return 1;
    }

    if (l.idx[1] < r.idx[1])
    {
        return -1;
    }
    else if (l.idx[1] > r.idx[1])
    {
        return 1;
    }

    if (l.idx[2] < r.idx[2])
    {
        return -1;
    }
    else if (l.idx[2] > r.idx[2])
    {
        return 1;
    }

    return 0;
}


int transpose_qsort(taco_tensor_t *A, taco_tensor_t *B)
{
    uint32_t B0_size = B->dimensions[0];
    uint8_t B0_dim_size = 32;
    uint64_t A2_mask = 0xFFFFFFFF00000000;
    while (!(B0_size & (1 << (B0_dim_size - 1))))
    {
        B0_dim_size--;
        A2_mask |= (1 << (B0_dim_size));
    }
    A2_mask = ~A2_mask;

    uint32_t B1_size = B->dimensions[1];
    uint8_t B1_dim_size = 32;
    uint64_t A1_mask = 0xFFFFFFFF00000000;
    while (!(B1_size & (1 << (B1_dim_size - 1))))
    {
        B1_dim_size--;
        A1_mask |= (1 << (B1_dim_size));
    }
    A1_mask = ~A1_mask;

    uint32_t B2_size = B->dimensions[2];
    uint8_t B2_dim_size = 32;
    uint64_t A0_mask = 0xFFFFFFFF00000000;
    while (!(B2_size & (1 << (B2_dim_size - 1))))
    {
        B2_dim_size--;
        A0_mask |= (1 << (B2_dim_size));
    }
    A0_mask = ~A0_mask;

    if (B0_dim_size + B1_dim_size + B2_dim_size > 64)
    {
        std::cout << "FAIL" << std::endl;
        return -1;
    }

    uint8_t sh1 = B0_dim_size;
    uint8_t sh2 = sh1 + B1_dim_size;

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

    // Unpack B into C (in coo)

    int32_t init_alloc_size = 1048576;
    int32_t C_capacity = init_alloc_size;
    int32_t c_size = 0;
    struct coord_t *C = (struct coord_t *)malloc(sizeof(struct coord_t) * C_capacity);

    for (int32_t B0_pos = B0_pos_arr[0]; B0_pos < B0_pos_arr[1]; B0_pos++)
    {
        uint64_t iB = (uint64_t)B0_idx_arr[B0_pos];
        int32_t B0_end = B0_pos + 1;
        for (int32_t B1_pos = B1_pos_arr[B0_pos]; B1_pos < B1_pos_arr[B0_end]; B1_pos++)
        {
            uint64_t jB = (uint64_t)B1_idx_arr[B1_pos];
            int32_t B1_end = B1_pos + 1;
            for (int32_t B2_pos = B2_pos_arr[B1_pos]; B2_pos < B2_pos_arr[B1_end]; B2_pos++)
            {
                uint64_t kB = (uint64_t)B2_idx_arr[B2_pos];
                if (C_capacity <= (c_size + 1))
                {
                    int32_t C_capacity_new = 2 * (c_size + 1);
                    C = (struct coord_t *)realloc(C, sizeof(struct coord_t) * C_capacity_new);
                    C_capacity = C_capacity_new;
                }
                C[c_size].val = B_val_arr[B2_pos];
                uint64_t crd = (iB) | (jB << sh1) | (kB << (sh2));
                C[c_size].crd = crd;

                c_size++;
            }
        }
    }
    // sort COO
    qsort(C, c_size, sizeof(struct coord_t), compare_crd_vals);

    // pack C into A
    int32_t A0_pos_capacity = init_alloc_size;
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
        uint64_t iC = ((C[C0_pos].crd >> (sh2)) & A0_mask);
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (((C[C0_end].crd >> (sh2)) & A0_mask) == iC))
        {
            C0_end++;
        }

        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        while (C1_pos < C0_end)
        {
            uint64_t jC = (C[C1_pos].crd >> sh1) & A1_mask;
            int32_t C1_end = C1_pos + 1;
            while ((C1_end < C0_end) && (((C[C1_end].crd >> (sh1)) & A1_mask) == jC))
            {
                C1_end++;
            }

            int32_t A2_pos_start = A2_pos;
            for (int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++)
            {
                uint64_t kC = (C[C2_pos].crd) & A2_mask;

                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1))
                {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C[C2_pos].val;

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

int transpose_qsort2(taco_tensor_t *A, taco_tensor_t *B)
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

    // Unpack B into C (in coo)

    int32_t init_alloc_size = 1048576;
    int32_t C_capacity = init_alloc_size;
    int32_t c_size = 0;
    struct coo_t *C = (struct coo_t *)malloc(sizeof(struct coo_t) * C_capacity);

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
                if (C_capacity <= (c_size + 1))
                {
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
        int32_t iC = C[C0_pos].idx[0];
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (C[C0_end].idx[0] == iC))
        {
            C0_end++;
        }

        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        while (C1_pos < C0_end)
        {
            int32_t jC = C[C1_pos].idx[1];
            int32_t C1_end = C1_pos + 1;
            while ((C1_end < C0_end) && (C[C1_end].idx[1] == jC))
            {
                C1_end++;
            }

            int32_t A2_pos_start = A2_pos;
            for (int32_t C2_pos = C1_pos; C2_pos < C1_end; C2_pos++)
            {
                int32_t kC = C[C2_pos].idx[2];
                // Pack values into A.
                if (A_vals_capacity <= ((A2_pos + 1) * 1))
                {
                    int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
                    A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                    A_vals_capacity = A_vals_capacity_new;
                }
                A_val_arr[A2_pos] = C[C2_pos].val;

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