#ifndef TACO_TRANSPOSE_COO_H
#define TACO_TRANSPOSE_COO_H

#include "taco/taco_tensor_t.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace taco
{


struct coo_t
{
	int32_t	idx0;
	int32_t	idx1;
	int32_t	idx2;
	double	val;
};


// merge_012_sort performs a merge sort comparing on 012
void merge_012_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_012_sort(C, C_scratch, start, m);
		merge_012_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx0 <  C_scratch[e_i].idx0)
			{
                C[i] = C_scratch[s_i];
                s_i ++;
			} else if (C_scratch[s_i].idx0 == C_scratch[e_i].idx0){
                if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx1)
                {
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else if (C_scratch[s_i].idx1 == C_scratch[e_i].idx1){
                    if(C_scratch[s_i].idx2 <=  C_scratch[e_i].idx2)
                    {
                        C[i] = C_scratch[s_i];
                        s_i ++;
                    } else {
                        C[i] = C_scratch[e_i];
				        e_i ++;
                    }
                } else {
                    C[i] = C_scratch[e_i];
                    e_i ++;
                }
            } else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// merge_012_sort performs a merge sort comparing on 012
void merge_102_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_102_sort(C, C_scratch, start, m);
		merge_102_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx1)
			{
                C[i] = C_scratch[s_i];
                s_i ++;
			} else if (C_scratch[s_i].idx1 == C_scratch[e_i].idx1){
                if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx1)
                {
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else if (C_scratch[s_i].idx0 == C_scratch[e_i].idx0){
                    if(C_scratch[s_i].idx2 <=  C_scratch[e_i].idx2)
                    {
                        C[i] = C_scratch[s_i];
                        s_i ++;
                    } else {
                        C[i] = C_scratch[e_i];
				        e_i ++;
                    }
                } else {
                    C[i] = C_scratch[e_i];
                    e_i ++;
                }
            } else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// merge_012_sort performs a merge sort comparing on 012
void merge_210_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_210_sort(C, C_scratch, start, m);
		merge_210_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx2)
			{
                C[i] = C_scratch[s_i];
                s_i ++;
			} else if (C_scratch[s_i].idx2 == C_scratch[e_i].idx2){
                if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx1)
                {
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else if (C_scratch[s_i].idx1 == C_scratch[e_i].idx1){
                    if(C_scratch[s_i].idx0 <=  C_scratch[e_i].idx0)
                    {
                        C[i] = C_scratch[s_i];
                        s_i ++;
                    } else {
                        C[i] = C_scratch[e_i];
				        e_i ++;
                    }
                } else {
                    C[i] = C_scratch[e_i];
                    e_i ++;
                }
            } else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// merge_012_sort performs a merge sort comparing on 012
void merge_210_sort_opt(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_210_sort(C, C_scratch, start, m);
		merge_210_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx2)
			{
                C[i] = C_scratch[s_i];
                s_i ++;
			} else if (C_scratch[s_i].idx2 == C_scratch[e_i].idx2){
                if(C_scratch[s_i].idx1 <  C_scratch[e_i].idx1)
                {
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else if (C_scratch[s_i].idx1 == C_scratch[e_i].idx1){
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else {
                    C[i] = C_scratch[e_i];
                    e_i ++;
                }
            } else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}


// merge_021_sort performs a merge sort comparing on 021
void merge_021_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_021_sort(C, C_scratch, start, m);
		merge_021_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx0 <  C_scratch[e_i].idx0)
			{
                C[i] = C_scratch[s_i];
                s_i ++;
			} else if (C_scratch[s_i].idx0 == C_scratch[e_i].idx0){
                if(C_scratch[s_i].idx2 <  C_scratch[e_i].idx2)
                {
                    C[i] = C_scratch[s_i];
                    s_i ++;
                } else if (C_scratch[s_i].idx2 == C_scratch[e_i].idx2){
                    if(C_scratch[s_i].idx1 <=  C_scratch[e_i].idx1)
                    {
                        C[i] = C_scratch[s_i];
                        s_i ++;
                    } else {
                        C[i] = C_scratch[e_i];
				        e_i ++;
                    }
                } else {
                    C[i] = C_scratch[e_i];
                    e_i ++;
                }
            } else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}


// merge_0_sort performs a merge sort comparing on 0
void merge_0_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_0_sort(C, C_scratch, start, m);
		merge_0_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx0 <=  C_scratch[e_i].idx0)
			{
				C[i] = C_scratch[s_i];
				s_i ++;
			} else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// merge_1_sort performs a merge sort comparing on 1
void merge_1_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_1_sort(C, C_scratch, start, m);
		merge_1_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx1 <=  C_scratch[e_i].idx1)
			{
				C[i] = C_scratch[s_i];
				s_i ++;
			} else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// merge_2_sort performs a merge sort comparing on 2
void merge_2_sort(struct coo_t* C, struct coo_t* C_scratch, int start, int end)
{
	if(end > start + 1)
	{
		int m = start + (end - start) / 2;
		merge_2_sort(C, C_scratch, start, m);
		merge_2_sort(C, C_scratch, m, end);
		// Copy to scratch space
		memcpy(&C_scratch[start], &C[start], sizeof(struct coo_t)*(end-start));
		int i = start;
		int s_i = start;
		int e_i = m;
		while(s_i < m && e_i < end)
		{
			if(C_scratch[s_i].idx2 <=  C_scratch[e_i].idx2)
			{
				C[i] = C_scratch[s_i];
				s_i ++;
			} else {
				C[i] = C_scratch[e_i];
				e_i ++;
			}
			i++;
		}
		// Add any remaining s_i
		while(s_i < m)
		{
			C[i] = C_scratch[s_i];
			s_i ++;
			i++;
		}
		// Add any remaining e_i
		while(e_i < end)
		{
			C[i] = C_scratch[e_i];
			e_i ++;
			i++;
		}
	}
}

// transpose permutes the modes of the coordinates to be [0, 2, 1]
int transpose_coo_021(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [0, 2, 1]
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_0 = (int *)malloc(c_size*sizeof(int));
	int *quotient_0 = (int *)malloc(c_size*sizeof(int));
	int current_0 = 0;
	bucket_0[0] = 0;
	quotient_0[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_0++;
			quotient_0[current_0] = i;
		}
		bucket_0[i] = current_0;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_0[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_0[bucket_0[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_0[perm[i]] ++;
	}

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_0);
	free(quotient_0);
	return 0;
}

// transpose permutes the modes of the coordinates to be [2, 1, 0]
int transpose_coo_210(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [2, 1, 0]

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size + 1, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size + 1, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	return 0;
}

// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size + 1, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	return 0;
}


// transpose permutes the modes of the coordinates to be [0, 2, 1]
int transpose_coo_count_021(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [0, 2, 1]

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 <= B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B0_count);
	return 0;
}

// transpose permutes the modes of the coordinates to be [0, 2, 1]
int transpose_coo_count_021_skip(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [0, 2, 1]

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 <= B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B0_count);
	return 0;
}


// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_count_102(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 <= B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B0_count);
	free(B1_count);
	return 0;
}


// transpose permutes the modes of the coordinates to be [2, 1, 0]
int transpose_coo_count_210(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [2, 1, 0]

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 <= B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B0_count);
	free(B1_count);
	free(B2_count);
	return 0;
}


} // namespace taco
#endif
