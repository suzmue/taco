
#include <iostream>
#include "taco.h"
#include "taco/util/timers.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>

#include "taco/tensor.h"
#include "taco/format.h"
#include "taco/error.h"
#include "taco/util/strings.h"
#include "taco/util/files.h"
#include <cstdio>
#include <cstdlib>
#include <vector>


struct coo_t
{
	int32_t	idx0;
	int32_t	idx1;
	int32_t	idx2;
	double	val;
};


using namespace taco;
int cmp_012(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_12(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_2(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_021(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_21(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_1(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_102(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_02(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_120(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_20(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_0(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_201(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_01(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_210(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_10(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2)
int transpose_coo_012_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_012);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2)
int transpose_coo_012_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_12);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2)
int transpose_coo_012_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2)
int transpose_coo_012_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2)
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1)
int transpose_coo_021_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_021);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1)
int transpose_coo_021_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 1)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_21);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1)
int transpose_coo_021_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
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
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1)
int transpose_coo_021_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
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
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2)
int transpose_coo_102_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 0, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_102);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2)
int transpose_coo_102_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_02);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2)
int transpose_coo_102_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2)
int transpose_coo_102_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0)
int transpose_coo_120_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 2, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_120);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0)
int transpose_coo_120_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_20);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0)
int transpose_coo_120_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0)
int transpose_coo_120_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1)
int transpose_coo_201_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 0, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_201);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1)
int transpose_coo_201_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_01);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1)
int transpose_coo_201_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1)
int transpose_coo_201_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0)
int transpose_coo_210_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 1, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_210);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0)
int transpose_coo_210_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0)

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_10);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0)
int transpose_coo_210_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0)
int transpose_coo_210_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
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


	free(B1_count);

	// Histogram sort on mode 2
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
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}

int main(int argc, char* argv[]) {
  char *p;
  int TOTAL;
  int SPLIT;
  long conv = strtol(argv[1], &p, 10);

  TOTAL = conv;

  conv = strtol(argv[2], &p, 10);
  SPLIT = conv;
   std::string filename = argv[3];

  // Read tensor data  
  int order = 3;
  int * dimensions = (int*)malloc(sizeof(int)*order);
  memset(dimensions, 0, sizeof(int)*order);
  
  int32_t init_alloc_size = 1048576;
  int32_t A_capacity = init_alloc_size;
  struct coo_t *A = (struct coo_t *)malloc(sizeof(struct coo_t)* A_capacity);

  std::fstream stream;
  util::openStream(stream, filename, fstream::in);

  std::string line;
  if (!std::getline(stream, line)) {
    return -1;
  }


  int size = 0;

  do {
      if(size >= A_capacity){
          int32_t A_capacity_new = 2 * (A_capacity);
          A = (struct coo_t*)realloc(A, sizeof(struct coo_t) * A_capacity_new);
          A_capacity = A_capacity_new;
        }

    char* linePtr = (char*)line.data();

    // Generated by coo/gen_taco_to_list.py

	long idx0 = strtol(linePtr, &linePtr, 10);
	A[size].idx0 = (int32_t)idx0 - 1;
	dimensions[0] = std::max(dimensions[0], (int)idx0 - 1);
	long idx1 = strtol(linePtr, &linePtr, 10);
	A[size].idx1 = (int32_t)idx1 - 1;
	dimensions[1] = std::max(dimensions[1], (int)idx1 - 1);
	long idx2 = strtol(linePtr, &linePtr, 10);
	A[size].idx2 = (int32_t)idx2 - 1;
	dimensions[2] = std::max(dimensions[2], (int)idx2 - 1);

    double val = strtod(linePtr, &linePtr);
    A[size].val = val;
    size ++;

  } while (std::getline(stream, line));

  stream.close();

		if(0 % TOTAL == SPLIT){
		cout << "012, 0, 0" ;
		// (0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_012_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(1 % TOTAL == SPLIT){
		cout << "012, 1, 0" ;
		// (0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_012_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(2 % TOTAL == SPLIT){
		cout << "012, 2, 0" ;
		// (0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_012_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(3 % TOTAL == SPLIT){
		cout << "012, 3, 0" ;
		// (0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_012_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(4 % TOTAL == SPLIT){
		cout << "021, 0, 0" ;
		// (0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_021_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(5 % TOTAL == SPLIT){
		cout << "021, 1, 0" ;
		// (0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_021_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(6 % TOTAL == SPLIT){
		cout << "021, 2, 1" ;
		// (0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_021_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(7 % TOTAL == SPLIT){
		cout << "021, 3, 1" ;
		// (0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_021_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(8 % TOTAL == SPLIT){
		cout << "102, 0, 0" ;
		// (1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_102_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(9 % TOTAL == SPLIT){
		cout << "102, 1, 1" ;
		// (1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_102_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(10 % TOTAL == SPLIT){
		cout << "102, 2, 1" ;
		// (1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_102_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(11 % TOTAL == SPLIT){
		cout << "102, 3, 1" ;
		// (1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_102_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(12 % TOTAL == SPLIT){
		cout << "120, 0, 0" ;
		// (1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_120_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(13 % TOTAL == SPLIT){
		cout << "120, 1, 1" ;
		// (1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_120_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(14 % TOTAL == SPLIT){
		cout << "120, 2, 2" ;
		// (1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_120_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(15 % TOTAL == SPLIT){
		cout << "120, 3, 2" ;
		// (1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_120_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(16 % TOTAL == SPLIT){
		cout << "201, 0, 0" ;
		// (2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_201_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(17 % TOTAL == SPLIT){
		cout << "201, 1, 1" ;
		// (2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_201_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(18 % TOTAL == SPLIT){
		cout << "201, 2, 1" ;
		// (2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_201_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(19 % TOTAL == SPLIT){
		cout << "201, 3, 1" ;
		// (2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_201_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(20 % TOTAL == SPLIT){
		cout << "210, 0, 0" ;
		// (2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_210_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(21 % TOTAL == SPLIT){
		cout << "210, 1, 1" ;
		// (2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_210_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(22 % TOTAL == SPLIT){
		cout << "210, 2, 2" ;
		// (2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_210_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(23 % TOTAL == SPLIT){
		cout << "210, 3, 2" ;
		// (2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_012);
			transpose_coo_210_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
	free(A);
	free(dimensions);
}
