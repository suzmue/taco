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

/**
 * This file includes all correct schedules that take a list of coordinates
 * in order 012 and changes them to order 210.
 * 
 * Functions in this file:
    *  3 sorts:
        * transpose_coo_102_012_3
        * transpose_coo_102_021_3
        * transpose_coo_102_102_3
        * transpose_coo_102_120_3
        * transpose_coo_102_201_3
        * transpose_coo_102_012_3
    * 2 sorts:
        * transpose_coo_102_01_2
        * transpose_coo_102_02_2
        * transpose_coo_102_10_2
        * transpose_coo_102_12_2
        * transpose_coo_102_20_2
        * transpose_coo_102_21_2
    * 1 sort:
        * transpose_coo_102_0_1
        * transpose_coo_102_1_1  
        * transpose_coo_102_2_1
    * 0 sort:
        * transpose_coo_102_0
 **/

struct coo_t
{
	int32_t	idx0;
	int32_t	idx1;
	int32_t	idx2;
	double	val;
};

int transpose_coo_102_012_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_021_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_102_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_120_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_201_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_210_3(struct coo_t *C_coords, int c_size, int order, int *dimensions);

int transpose_coo_102_01_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// int transpose_coo_102_02_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_10_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_12_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// int transpose_coo_102_20_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_21_2(struct coo_t *C_coords, int c_size, int order, int *dimensions);

// int transpose_coo_102_0_1(struct coo_t *C_coords, int c_size, int order, int *dimensions);
int transpose_coo_102_1_1(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// int transpose_coo_102_2_1(struct coo_t *C_coords, int c_size, int order, int *dimensions);

// int transpose_coo_102_0(struct coo_t *C_coords, int c_size, int order, int *dimensions);



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
    }else if(r->idx1 > s->idx1) {
        return 1;
    }
        if(r->idx2 < s->idx2) {
        return -1;
    }else if(r->idx2 > s->idx2) {
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
    }else if(r->idx2 > s->idx2) {
        return 1;
    }

    if(r->idx1 < s->idx1) {
        return -1;
    }else if(r->idx1 > s->idx1) {
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
    }else if(r->idx1 > s->idx1) {
        return 1;
    }
    if(r->idx0 < s->idx0) {
        return -1;
    } else if (r->idx0 > s->idx0) {
        return 1;
    }
    
        if(r->idx2 < s->idx2) {
        return -1;
    }else if(r->idx2 > s->idx2) {
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
    }else if(r->idx2 > s->idx2) {
        return 1;
    }
    if(r->idx1 < s->idx1) {
        return -1;
    }else if(r->idx1 > s->idx1) {
        return 1;
    }
    if(r->idx0 < s->idx0) {
        return -1;
    } else if (r->idx0 > s->idx0) {
        return 1;
    }
    
    
    return 0;

}



int main(int argc, char* argv[]) {
  std::string filename = "~/research/benchmark/facebook.tns";
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


            long idx1 = strtol(linePtr, &linePtr, 10);
    A[size].idx1 = (int32_t)idx1 - 1;
    dimensions[1] = std::max(dimensions[1], (int)idx1 - 1);

            long idx2 = strtol(linePtr, &linePtr, 10);
    A[size].idx2 = (int32_t)idx2 - 1;
    dimensions[2] = std::max(dimensions[2], (int)idx2 - 1);
    

    long idx0 = strtol(linePtr, &linePtr, 10);
    A[size].idx0 = (int32_t)idx0 - 1;
    dimensions[0] = std::max(dimensions[0], (int)idx0 - 1);







    double val = strtod(linePtr, &linePtr);
    A[size].val = val;
    size ++;

  } while (std::getline(stream, line));

  stream.close();
    
    cout << "size = " << size << endl;
    cout<< "[" << dimensions[0] << ", "<< dimensions[1] << ", "<< dimensions[2] << "]" << endl;

  // Create tensors

     qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t;                                   
  t.start();                                             
  qsort(A, size, sizeof(struct coo_t), cmp_210);
  t.stop();                                              
  taco::util::TimeResults r = t.getResult();        
  cout << "qsort:" << endl;
  cout << r << endl;   
  t.clear_cache();


    qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t1;                                   
  t1.start();                                             
  transpose_coo_102_012_3(A, size, order, dimensions);
  t1.stop();                                              
  taco::util::TimeResults r1 = t1.getResult();        
  cout << "transpose_coo_102_012_3:" << endl; 
  cout << r1 <<  endl;   
  t1.clear_cache();

        qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t2;                                   
  t2.start();                                             
  transpose_coo_102_021_3(A, size, order, dimensions);
  t2.stop();                                              
  taco::util::TimeResults r2 = t2.getResult();        
  cout << "transpose_coo_102_021_3:" << endl; cout << r2 <<  endl;   
  t2.clear_cache();

 qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t3;                                   
  t3.start();                                             
  transpose_coo_102_102_3(A, size, order, dimensions);
  t3.stop();                                              
  taco::util::TimeResults r3 = t3.getResult();        
  cout << "transpose_coo_102_102_3:\t"  << endl; cout<< r3 << "" << endl;   
  t3.clear_cache();

   qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t4;                                   
  t4.start();                                             
  transpose_coo_102_120_3(A, size, order, dimensions);
  t4.stop();                                              
  taco::util::TimeResults r4 = t4.getResult();        
  cout << "transpose_coo_102_120_3:\t" << endl; cout << r4 << "" << endl;   
  t4.clear_cache();


   qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t5;                                   
  t5.start();                                             
  transpose_coo_102_201_3(A, size, order, dimensions);
  t5.stop();                                              
  taco::util::TimeResults r5 = t5.getResult();        
  cout << "transpose_coo_102_201_3:\t"  << endl; cout<< r5 << "" << endl;   
  t5.clear_cache();

     qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t6;                                   
  t6.start();                                             
  transpose_coo_102_210_3(A, size, order, dimensions);
  t6.stop();                                              
  taco::util::TimeResults r6 = t6.getResult();        
  cout << "transpose_coo_102_210_3:\t"  << endl; cout<< r6 << "" << endl;   
  t6.clear_cache();

  // 2 sorts
qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t9;                                   
  t9.start();                                             
  transpose_coo_102_01_2(A, size, order, dimensions);
  t9.stop();                                              
  taco::util::TimeResults r9 = t9.getResult();        
  cout << "transpose_coo_102_01_2:\t\t"  << endl; cout<< r9 << "" << endl;   
  t9.clear_cache();

//    qsort(A, size, sizeof(struct coo_t), cmp_012);

//   taco::util::Timer t12;                                   
//   t12.start();                                             
//   transpose_coo_102_02_2(A, size, order, dimensions);
//   t12.stop();                                              
//   taco::util::TimeResults r12 = t12.getResult();        
//   cout << "transpose_coo_102_02_2:\t\t"  << endl; cout<< r12 << "" << endl;   
//   t12.clear_cache();

   qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t10;                                   
  t10.start();                                             
  transpose_coo_102_10_2(A, size, order, dimensions);
  t10.stop();                                              
  taco::util::TimeResults r10 = t10.getResult();        
  cout << "transpose_coo_102_10_2:\t\t"  << endl; cout<< r10 << "" << endl;   
  t10.clear_cache();

   qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t8;                                   
  t8.start();                                             
  transpose_coo_102_12_2(A, size, order, dimensions);
  t8.stop();                                              
  taco::util::TimeResults r8 = t8.getResult();        
  cout << "transpose_coo_102_12_2:\t\t"  << endl; cout<< r8 << "" << endl;   
  t8.clear_cache();



//    qsort(A, size, sizeof(struct coo_t), cmp_012);

//   taco::util::Timer t11;                                   
//   t11.start();                                             
//   transpose_coo_102_20_2(A, size, order, dimensions);
//   t11.stop();                                              
//   taco::util::TimeResults r11 = t11.getResult();        
//   cout << "transpose_coo_102_20_2:\t\t"  << endl; cout<< r11 << "" << endl;   
//   t11.clear_cache();

       qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t7;                                   
  t7.start();                                             
  transpose_coo_102_21_2(A, size, order, dimensions);
  t7.stop();                                              
  taco::util::TimeResults r7 = t7.getResult();        
  cout << "transpose_coo_102_21_2:\t\t"  << endl; cout<< r7 << "" << endl;   
  t7.clear_cache();

        // 1 sorts

         
//  qsort(A, size, sizeof(struct coo_t), cmp_012);

//   taco::util::Timer t13;                                   
//   t13.start();                                             
//   transpose_coo_102_0_1(A, size, order, dimensions);
//   t13.stop();                                              
//   taco::util::TimeResults r13 = t13.getResult();        
//   cout << "transpose_coo_102_0_1:\t\t"  << endl; cout<< r13 << "" << endl;   
//   t13.clear_cache();
      
 qsort(A, size, sizeof(struct coo_t), cmp_012);

  taco::util::Timer t14;                                   
  t14.start();                                             
  transpose_coo_102_1_1(A, size, order, dimensions);
  t14.stop();                                              
  taco::util::TimeResults r14 = t14.getResult();        
  cout << "transpose_coo_102_1_1:\t\t"  << endl; cout<< r14 << "" << endl;   
  t14.clear_cache();

//  qsort(A, size, sizeof(struct coo_t), cmp_012);

//   taco::util::Timer t15;                                   
//   t15.start();                                             
//   transpose_coo_102_2_1(A, size, order, dimensions);
//   t15.stop();                                              
//   taco::util::TimeResults r15 = t15.getResult();        
//   cout << "transpose_coo_102_2_1:\t\t"  << endl; cout<< r15 << "" << endl;   
//   t15.clear_cache();

// 0 sort

//  qsort(A, size, sizeof(struct coo_t), cmp_012);

//   taco::util::Timer t16;                                   
//   t16.start();                                             
//   transpose_coo_102_0(A, size, order, dimensions);
//   t16.stop();                                              
//   taco::util::TimeResults r16 = t16.getResult();        
//   cout << "transpose_coo_102_0:\t\t"  << endl; cout<< r16 << "" << endl;   
//   t16.clear_cache();



        







}




// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_012_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_201 = (int *)malloc(c_size*sizeof(int));
	int *quotient_201 = (int *)malloc(c_size*sizeof(int));
	int current_201 = 0;
	bucket_201[0] = 0;
	quotient_201[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_201++;
			quotient_201[current_201] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_201++;
			quotient_201[current_201] = i;
		}
		bucket_201[i] = current_201;
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
		perm[idx] = bucket_201[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_201[bucket_201[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_201[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B0_count);
	free(B1_count);
	free(B2_count);
	free(bucket_201);
	free(quotient_201);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_021_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}

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
	free(B0_count);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_102_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Fix and sort on [1]
	// Create buckets and quotient
	int *bucket_01 = (int *)malloc(c_size*sizeof(int));
	int *quotient_01 = (int *)malloc(c_size*sizeof(int));
	int current_01 = 0;
	bucket_01[0] = 0;
	quotient_01[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_01++;
			quotient_01[current_01] = i;
		}
		bucket_01[i] = current_01;
	}

	// Histogram sort on mode 0 into the permutation array
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_01[i];
		B0_count[idx0]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_01[bucket_01[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_01[perm[i]] ++;
	}
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_201 = (int *)malloc(c_size*sizeof(int));
	int *quotient_201 = (int *)malloc(c_size*sizeof(int));
	int current_201 = 0;
	bucket_201[0] = 0;
	quotient_201[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_201++;
			quotient_201[current_201] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_201++;
			quotient_201[current_201] = i;
		}
		bucket_201[i] = current_201;
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
		perm[idx] = bucket_201[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_201[bucket_201[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_201[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B0_count);
	free(bucket_01);
	free(quotient_01);
	free(B2_count);
	free(bucket_201);
	free(quotient_201);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_120_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Fix and sort on [1]
	// Create buckets and quotient
	int *bucket_21 = (int *)malloc(c_size*sizeof(int));
	int *quotient_21 = (int *)malloc(c_size*sizeof(int));
	int current_21 = 0;
	bucket_21[0] = 0;
	quotient_21[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_21++;
			quotient_21[current_21] = i;
		}
		bucket_21[i] = current_21;
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
		perm[idx] = bucket_21[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_21[bucket_21[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_21[perm[i]] ++;
	}
	// Fix and sort on [1]
	// Create buckets and quotient
	int *bucket_01 = (int *)malloc(c_size*sizeof(int));
	int *quotient_01 = (int *)malloc(c_size*sizeof(int));
	int current_01 = 0;
	bucket_01[0] = 0;
	quotient_01[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_01++;
			quotient_01[current_01] = i;
		}
		bucket_01[i] = current_01;
	}

	// Histogram sort on mode 0 into the permutation array
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_01[i];
		B0_count[idx0]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_01[bucket_01[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_01[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(bucket_21);
	free(quotient_21);
	free(B0_count);
	free(bucket_01);
	free(quotient_01);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_201_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
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
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_210_3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
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

	// Fix and sort on [1]
	// Create buckets and quotient
	int *bucket_01 = (int *)malloc(c_size*sizeof(int));
	int *quotient_01 = (int *)malloc(c_size*sizeof(int));
	int current_01 = 0;
	bucket_01[0] = 0;
	quotient_01[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_01++;
			quotient_01[current_01] = i;
		}
		bucket_01[i] = current_01;
	}

	// Histogram sort on mode 0 into the permutation array
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_01[i];
		B0_count[idx0]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_01[bucket_01[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_01[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B0_count);
	free(bucket_01);
	free(quotient_01);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_01_2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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
	free(B0_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_10_2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Fix and sort on [1]
	// Create buckets and quotient
	int *bucket_01 = (int *)malloc(c_size*sizeof(int));
	int *quotient_01 = (int *)malloc(c_size*sizeof(int));
	int current_01 = 0;
	bucket_01[0] = 0;
	quotient_01[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_01++;
			quotient_01[current_01] = i;
		}
		bucket_01[i] = current_01;
	}

	// Histogram sort on mode 0 into the permutation array
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_01[i];
		B0_count[idx0]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_01[bucket_01[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_01[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B0_count);
	free(bucket_01);
	free(quotient_01);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_12_2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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

	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_201 = (int *)malloc(c_size*sizeof(int));
	int *quotient_201 = (int *)malloc(c_size*sizeof(int));
	int current_201 = 0;
	bucket_201[0] = 0;
	quotient_201[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_201++;
			quotient_201[current_201] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_201++;
			quotient_201[current_201] = i;
		}
		bucket_201[i] = current_201;
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
		perm[idx] = bucket_201[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_201[bucket_201[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_201[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(bucket_201);
	free(quotient_201);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_21_2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}

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
	free(bucket_20);
	free(quotient_20);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be [1, 0, 2]
int transpose_coo_102_1_1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in [1, 0, 2]

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
	free(B1_count);
	return 0;
}
