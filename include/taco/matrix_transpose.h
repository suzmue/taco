#include "taco/taco_tensor_t.h"

namespace taco
{
int mat_csr_transpose_halfperm(taco_tensor_t *A, taco_tensor_t *B);

int mat_csr_transpose_qsort(taco_tensor_t *A, taco_tensor_t *B);

int mat_csf_transpose_halfperm(taco_tensor_t *A, taco_tensor_t *B);

int mat_csf_transpose_qsort(taco_tensor_t *A, taco_tensor_t *B);

struct coo_t
{
    int32_t idx[2];
    double val;
};

int compare_2(const void *p, const void *q)
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

    return 0;
}

int mat_csr_transpose_halfperm(taco_tensor_t *A, taco_tensor_t *B)
{
    int A0_size = (int)(A->dimensions[0]);
    int *A1_pos_arr = (int *)(A->indices[1][0]);
    int *A1_idx_arr = (int *)(A->indices[1][1]);
    double *A_val_arr = (double *)(A->vals);
    int B0_size = (int)(B->dimensions[0]);
    int *B1_pos_arr = (int *)(B->indices[1][0]);
    int *B1_idx_arr = (int *)(B->indices[1][1]);
    double *B_val_arr = (double *)(B->vals);

    int32_t C_capacity = A0_size + 1;
    int32_t  *C = (int32_t *)calloc(C_capacity, sizeof(int32_t));

    for (int32_t iB = 0; iB < B0_size; iB++)
    {
        for (int32_t B1_pos = B1_pos_arr[iB]; B1_pos < B1_pos_arr[iB + 1]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            C[jB + 1] ++;
        }
    }

    // Prefix sum of column count.
    for(int c_pos = 1; c_pos < C_capacity; c_pos ++){
        C[c_pos] += C[c_pos - 1];
    }

    int32_t A1_pos_capacity = A0_size + 1;
    int32_t A1_idx_capacity = C[C_capacity - 1];
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);

    memcpy(A1_pos_arr, C, sizeof(int) * A1_pos_capacity);

    int32_t A_vals_capacity = A1_idx_capacity;
    A_val_arr = (double *)malloc(sizeof(double) * A_vals_capacity);

    for (int32_t iB = 0; iB < B0_size; iB++)
    {
        for (int32_t B1_pos = B1_pos_arr[iB]; B1_pos < B1_pos_arr[iB + 1]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            int32_t val = B_val_arr[B1_pos];
            int32_t A1_pos = C[jB];
            A1_idx_arr[A1_pos] = iB;
            A_val_arr[A1_pos] = val;
            C[jB] ++;
        }
    }

    free(C);

    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->vals = (uint8_t *)A_val_arr;

    return 0;
}

int mat_csr_transpose_qsort(taco_tensor_t *A, taco_tensor_t *B)
{
    int A0_size = (int)(A->dimensions[0]);
    int *A1_pos_arr = (int *)(A->indices[1][0]);
    int *A1_idx_arr = (int *)(A->indices[1][1]);
    double *A_val_arr = (double *)(A->vals);
    int B0_size = (int)(B->dimensions[0]);
    int *B1_pos_arr = (int *)(B->indices[1][0]);
    int *B1_idx_arr = (int *)(B->indices[1][1]);
    double *B_val_arr = (double *)(B->vals);

    int32_t init_alloc_size = 1048576;
    int32_t C_capacity = init_alloc_size;
    int32_t c_size = 0;
    struct coo_t *C = (struct coo_t *)malloc(sizeof(struct coo_t) * C_capacity);
    for (int32_t iB = 0; iB < B0_size; iB++)
    {
        for (int32_t B1_pos = B1_pos_arr[iB]; B1_pos < B1_pos_arr[iB + 1]; B1_pos++)
        {
            int32_t jB = B1_idx_arr[B1_pos];
            if (C_capacity <= (c_size + 1))
            {
                int32_t C_capacity_new = 2 * (c_size + 1);
                C = (struct coo_t *)realloc(C, sizeof(struct coo_t) * C_capacity_new);
                C_capacity = C_capacity_new;
            }
            C[c_size].val = B_val_arr[B1_pos];
            C[c_size].idx[0] = jB;
            C[c_size].idx[1] = iB;

            c_size++;
        }
    }
    // sort COO
    qsort(C, c_size, sizeof(struct coo_t), compare_2);

    int32_t A1_pos_capacity = init_alloc_size;
    int32_t A1_idx_capacity = init_alloc_size;
    A1_pos_arr = (int *)malloc(sizeof(int) * A1_pos_capacity);
    A1_idx_arr = (int *)malloc(sizeof(int) * A1_idx_capacity);
    A1_pos_arr[0] = 0;
    int32_t A_vals_capacity = init_alloc_size;
    A_val_arr = (double *)malloc(sizeof(double) * A_vals_capacity);

    int32_t A1_pos = 0;
    int32_t C0_pos = 0;
    for(int iA = 0; iA < A0_size; iA ++ ){
        if(C0_pos >= c_size || C[C0_pos * 1].idx[0] != iA) {
            A1_pos_arr[iA + 1] = A1_pos_arr[iA];
            continue;
        }
        int32_t iC = C[C0_pos * 1].idx[0];
        int32_t A0_pos = (0 * A0_size) + iC;
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (C[C0_end * 1].idx[0] == iC))
        {
            C0_end++;
        }
        for (int32_t C1_pos = C0_pos; C1_pos < C0_end; C1_pos++)
        {
            int32_t jC = C[(C1_pos * 1) + 0].idx[1];
            if (A_vals_capacity <= ((A1_pos + 1) * 1))
            {
                int32_t A_vals_capacity_new = 2 * ((A1_pos + 1) * 1);
                A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                A_vals_capacity = A_vals_capacity_new;
            }
            A_val_arr[A1_pos] = C[C1_pos].val;
            if (A1_idx_capacity <= A1_pos)
            {
                A1_idx_capacity = 2 * A1_pos;
                A1_idx_arr = (int *)realloc(A1_idx_arr, sizeof(int) * A1_idx_capacity);
            }
            A1_idx_arr[A1_pos] = jC;
            A1_pos++;
        }
        if (A1_pos_capacity <= (A0_pos + 1))
        {
            A1_pos_capacity = 2 * (A0_pos + 1);
            A1_pos_arr = (int *)realloc(A1_pos_arr, sizeof(int) * A1_pos_capacity);
        }
        A1_pos_arr[(A0_pos + 1)] = A1_pos;
        C0_pos = C0_end;
    }

    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->vals = (uint8_t *)A_val_arr;

    return 0;
}

int mat_csf_transpose_halfperm(taco_tensor_t *A, taco_tensor_t *B)
{
    return 0;
}

int mat_csf_transpose_qsort(taco_tensor_t *A, taco_tensor_t *B)
{
    int *A0_pos_arr = (int *)(A->indices[0][0]);
    int *A0_idx_arr = (int *)(A->indices[0][1]);
    int *A1_pos_arr = (int *)(A->indices[1][0]);
    int *A1_idx_arr = (int *)(A->indices[1][1]);
    double *A_val_arr = (double *)(A->vals);
    int *B0_pos_arr = (int *)(B->indices[0][0]);
    int *B0_idx_arr = (int *)(B->indices[0][1]);
    int *B1_pos_arr = (int *)(B->indices[1][0]);
    int *B1_idx_arr = (int *)(B->indices[1][1]);
    double *B_val_arr = (double *)(B->vals);

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
            if (C_capacity <= (c_size + 1))
            {
                int32_t C_capacity_new = 2 * (c_size + 1);
                C = (struct coo_t *)realloc(C, sizeof(struct coo_t) * C_capacity_new);
                C_capacity = C_capacity_new;
            }
            C[c_size].val = B_val_arr[B1_pos];
            C[c_size].idx[0] = jB;
            C[c_size].idx[1] = iB;

            c_size++;
        }
    }
    // sort COO
    qsort(C, c_size, sizeof(struct coo_t), compare_2);

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
    int32_t A_vals_capacity = init_alloc_size;
    A_val_arr = (double *)malloc(sizeof(double) * A_vals_capacity);

    int32_t A0_pos = 0;
    int32_t A1_pos = 0;
    int32_t C0_pos = 0;
    while (C0_pos < c_size)
    {
        int32_t iC = C[C0_pos * 1].idx[0];
        int32_t C0_end = C0_pos + 1;
        while ((C0_end < c_size) && (C[C0_end * 1].idx[0] == iC))
        {
            C0_end++;
        }
        int32_t A1_pos_start = A1_pos;
        int32_t C1_pos = C0_pos;
        for (int32_t C1_pos = C0_pos; C1_pos < C0_end; C1_pos++)
        {
            int32_t jC = C[(C1_pos * 1) + 0].idx[1];
            int32_t C1_end = C1_pos + 1;
            if (A_vals_capacity <= ((A1_pos + 1) * 1))
            {
                int32_t A_vals_capacity_new = 2 * ((A1_pos + 1) * 1);
                A_val_arr = (double *)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
                A_vals_capacity = A_vals_capacity_new;
            }
            A_val_arr[A1_pos] = B_val_arr[C1_pos];
            if (A1_idx_capacity <= A1_pos)
            {
                A1_idx_capacity = 2 * A1_pos;
                A1_idx_arr = (int *)realloc(A1_idx_arr, sizeof(int) * A1_idx_capacity);
            }
            A1_idx_arr[A1_pos] = jC;
            A1_pos++;
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
    A0_pos_arr[(0 + 1)] = A0_pos;

    A->indices[0][0] = (uint8_t *)(A0_pos_arr);
    A->indices[0][1] = (uint8_t *)(A0_idx_arr);
    A->indices[1][0] = (uint8_t *)(A1_pos_arr);
    A->indices[1][1] = (uint8_t *)(A1_idx_arr);
    A->vals = (uint8_t *)A_val_arr;
    return 0;
}
} // namespace taco