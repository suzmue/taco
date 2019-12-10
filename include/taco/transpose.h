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
// bucket sort Implementations:

// transpose_bucketsort transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1. Iterate over input, bucket by dimension B1, convert to coordinate format
// 2. Iterate over buckets, and bucket by B2.
// 3. Iterate over buckets and put in sorted array.
// 4. Pack
int transpose_bucketsort(taco_tensor_t *A, taco_tensor_t *B);
// transpose_bucketsort2 transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1. Iterate over input, bucket by dimension B1, convert to coordinate format, track used buckets
// 1.1 Sort used buckets
// 2. Iterate over buckets, and bucket by B2.
// 2.1 Sort used buckets
// 3. Iterate over buckets and put in sorted array.
// 4. Pack
int transpose_bucketsort2(taco_tensor_t *A, taco_tensor_t *B);

int transpose_bucketsort_skip_merge(taco_tensor_t *A, taco_tensor_t *B);
int transpose_bucketsort_skip(taco_tensor_t *A, taco_tensor_t *B);
int transpose_bucketsort_all(taco_tensor_t *A, taco_tensor_t *B);


// -----------------------------------------------------------------------------------------------
// counting sort Implementations:

int transpose_countsort_skip_merge(taco_tensor_t *A, taco_tensor_t *B);
int transpose_countsort_skip(taco_tensor_t *A, taco_tensor_t *B);
int transpose_countsort_all(taco_tensor_t *A, taco_tensor_t *B);


// -----------------------------------------------------------------------------------------------
// radix sort Implementations:

int transpose_radixsort_skip_merge(taco_tensor_t *A, taco_tensor_t *B);
int transpose_radixsort_skip(taco_tensor_t *A, taco_tensor_t *B);
int transpose_radixsort_all(taco_tensor_t *A, taco_tensor_t *B);

int transpose_radixsort_pow2_all(taco_tensor_t *A, taco_tensor_t *B);
int transpose_radixsort_pow2_skip(taco_tensor_t *A, taco_tensor_t *B);

int transpose_radixsort_bycoord_all(taco_tensor_t *A, taco_tensor_t *B);
int transpose_radixsort_bycoord_pow2_all(taco_tensor_t *A, taco_tensor_t *B);
int transpose_radixsort_bycoord_pow2_skip(taco_tensor_t *A, taco_tensor_t *B);

// -----------------------------------------------------------------------------------------------
// Halfperm style implementations:

// tranpose_bylevel transposes a 3-tensor (A(k,j,i) = B(i,j,k)) by:
// 1.1 Iterating over the input and counting the number of ks.
// 1.2 Performing a prefix sum.
// 1.3 Building the A1 level, and allocate nnz_k * j space to count next level
// 2.1 Iterating over the input and counting the unique js / ks.
// 2.2 Performing a prefix sum.
// 2.3 Building the A2 level, and allocate nnz_k * j space to count next level
// 2.1 Iterating over the input and counting the unique is / jk.
// 2.2 Performing a prefix sum.
// 2.3 Building the A3 level
// 3.0 Iterate over the input and insert the i coordinate and value into the already built data structure.
int transpose_bylevel(taco_tensor_t *A, taco_tensor_t *B);
int transpose_onepass(taco_tensor_t *A, taco_tensor_t *B);
int transpose_onepass_opt(taco_tensor_t *A, taco_tensor_t *B);

int transpose(taco_tensor_t *A, taco_tensor_t *B);

// Implementations
int transpose(taco_tensor_t *A, taco_tensor_t *B)
{
    return transpose_qsort(A, B);
}


int transpose_123(taco_tensor_t *A, taco_tensor_t *B);
int transpose_132(taco_tensor_t *A, taco_tensor_t *B);

} // namespace taco
#endif
