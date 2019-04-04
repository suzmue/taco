#ifndef TACO_TRANSPOSE_H
#define TACO_TRANSPOSE_H

#include "taco/taco_tensor_t.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace taco
{
// 3rd-order transpose implementation for CSF
// -----------------------------------------------------------------------------------------------
// Qsort Implementations: 

// transpose_qsort transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1. converting to coordinate format, where the coordinates are packed into a 64 bit int
// 2. calling Cs qsort
// 3. Pack
int transpose_qsort(taco_tensor_t *A, taco_tensor_t *B);
// transpose_qsort2 transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by"
// 1. converting to coordinate format
// 2. calling Cs qsort (comparing each coordinate)
// 3. Pack
int transpose_qsort2(taco_tensor_t *A, taco_tensor_t *B);

// -----------------------------------------------------------------------------------------------
// Radix sort Implementations:

// transpose_radixsort transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1. Iterate over input, bucket by dimension B1, convert to coordinate format
// 2. Iterate over buckets, and bucket by B2.
// 3. Iterate over buckets and put in sorted array.
// 4. Pack
int transpose_radixsort(taco_tensor_t *A, taco_tensor_t *B);
// transpose_radixsort2 transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1. Iterate over input, bucket by dimension B1, convert to coordinate format, track used buckets
// 1.1 Sort used buckets
// 2. Iterate over buckets, and bucket by B2.
// 2.1 Sort used buckets
// 3. Iterate over buckets and put in sorted array.
// 4. Pack
int transpose_radixsort2(taco_tensor_t *A, taco_tensor_t *B);

// -----------------------------------------------------------------------------------------------
// Halfperm style implementations:


int transpose_bylevel(taco_tensor_t *A, taco_tensor_t *B);
int transpose_onepass(taco_tensor_t *A, taco_tensor_t *B);
int transpose_onepass_opt(taco_tensor_t *A, taco_tensor_t *B);

int transpose(taco_tensor_t *A, taco_tensor_t *B);

// Implementations
int transpose(taco_tensor_t *A, taco_tensor_t *B)
{
    return transpose_qsort(A, B);
}

} // namespace taco
#endif
