#include <iostream>
#include "taco.h"
#include "taco/transpose.h"
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


using namespace taco;

int pack(taco_tensor_t *A, taco_tensor_t *B);
int readFile(std::string filename, taco_tensor_t* C);

int main(int argc, char* argv[]) {
  std::string filename = "~/research/benchmark/matmul_2-2-2.tns";
  // Read tensor data
  Format csf({Sparse,Sparse,Sparse});
  
  Tensor<double> C("C", {1,1,1}, Format({Sparse,Sparse,Sparse}));
  C.pack();
  taco_tensor_t *Ct = (taco_tensor_t*)C.getTacoTensorT();
  readFile(filename, Ct);
  // Create tensors
  Tensor<double> B("B", {1,1,1}, csf);
  Tensor<double> A("A", {1,1,1}, csf);
    B.pack();

  taco_tensor_t *At = (taco_tensor_t*)A.getTacoTensorT();
  taco_tensor_t *Bt = (taco_tensor_t*)B.getTacoTensorT();
  pack(Bt, Ct);

  taco::util::Timer timer;                                   
  timer.start();                                             
  taco::transpose_qsort(At, Bt);
  timer.stop();                                              
  taco::util::TimeResults result = timer.getResult();        
  cout << filename << " " << result << " ms" << endl;   
  timer.clear_cache();

    taco::util::Timer timer5;                                   
  timer5.start();                                             
  taco::transpose_qsort2(At, Bt);
  timer5.stop();                                              
  result = timer5.getResult();        
  cout << filename << " " << result << " ms" << endl;   
  timer.clear_cache();


  taco::util::Timer timer2;                                  
  timer2.start();                                             
  taco::transpose_bylevel(At, Bt);
  timer2.stop();                                              
  result = timer2.getResult();        
  cout << filename << " " << result << " ms" << endl;
    timer.clear_cache();    

  taco::util::Timer timer3;                                   
  timer3.start();                                             
  taco::transpose_onepass(At, Bt);
  timer3.stop();                                              
  result = timer3.getResult();        
  cout << filename << " " << result << " ms" << endl;       
  timer.clear_cache();

  taco::util::Timer timer4;                                   
  timer4.start();                                             
  taco::transpose_onepass_opt(At, Bt);
  timer4.stop();                                              
  result = timer4.getResult();        
  cout << filename << " " << result << " ms" << endl;   
}

int readFile(std::string filename, taco_tensor_t *A) {
  int*  A0_pos_arr;
  int*  A0_idx_arr;
  int*  A1_idx_arr ;
  int*  A2_idx_arr ;
  double*  A_val_arr;


  int* dimensions = (int32_t*)malloc(sizeof(int)*3);
  memset(dimensions, 0, sizeof(int)*3);
  
  int32_t init_alloc_size = 1048576;
  int32_t A_capacity = init_alloc_size;
  int32_t A0_pos_capacity = init_alloc_size;
  int32_t A0_idx_capacity = init_alloc_size;
  A0_pos_arr = (int*)malloc(sizeof(int) * A0_pos_capacity);
  A0_idx_arr = (int*)malloc(sizeof(int) * A0_idx_capacity);
  int32_t A1_idx_capacity = init_alloc_size;
  A1_idx_arr = (int*)malloc(sizeof(int) * A1_idx_capacity);
  int32_t A2_idx_capacity = init_alloc_size;
  A2_idx_arr = (int*)malloc(sizeof(int) * A2_idx_capacity);

  A0_pos_arr[0] = 0;
  int32_t A_vals_capacity = init_alloc_size;
  A_val_arr = (double*)malloc(sizeof(double) * A_vals_capacity);



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

          A0_idx_arr = (int*)realloc(A0_idx_arr, sizeof(int) * A_capacity_new);
          A1_idx_arr = (int*)realloc(A1_idx_arr, sizeof(int) * A_capacity_new);
          A2_idx_arr = (int*)realloc(A2_idx_arr, sizeof(int) * A_capacity_new);

          A_val_arr = (double*)realloc(A_val_arr, sizeof(double) * A_capacity_new);
          A_capacity = A_capacity_new;
        }

    char* linePtr = (char*)line.data();
    // i
      long idx = strtol(linePtr, &linePtr, 10);
      A0_idx_arr[size] = (int)idx - 1;
      dimensions[0] = std::max(dimensions[0], (int)idx);
      // j 
      idx = strtol(linePtr, &linePtr, 10);
      A1_idx_arr[size] = (int)idx - 1;
      dimensions[1] = std::max(dimensions[1], (int)idx);

      // k
      idx = strtol(linePtr, &linePtr, 10);
      A2_idx_arr[size] = (int)idx - 1;
      dimensions[2] = std::max(dimensions[2], (int)idx);


    double val = strtod(linePtr, &linePtr);
    A_val_arr[size] = val;
    size ++;

  } while (std::getline(stream, line));

  stream.close();
  A0_pos_arr[1] = size;

  A->indices[0][0] = (uint8_t*)(A0_pos_arr);
  A->indices[0][1] = (uint8_t*)(A0_idx_arr);
  A->indices[1][1] = (uint8_t*)(A1_idx_arr);
  A->indices[2][1] = (uint8_t*)(A2_idx_arr);

  A->vals = (uint8_t*)A_val_arr;
  A->dimensions = (int32_t*)dimensions;

  return 0;
}

int pack(taco_tensor_t *A, taco_tensor_t *B) {
  int*  A0_pos_arr = (int*)(A->indices[0][0]);
  int*  A0_idx_arr = (int*)(A->indices[0][1]);
  int*  A1_pos_arr = (int*)(A->indices[1][0]);
  int*  A1_idx_arr = (int*)(A->indices[1][1]);
  int*  A2_pos_arr = (int*)(A->indices[2][0]);
  int*  A2_idx_arr = (int*)(A->indices[2][1]);
  double*  A_val_arr = (double*)(A->vals);
  int*  B0_pos_arr = (int*)(B->indices[0][0]);
  int*  B0_idx_arr = (int*)(B->indices[0][1]);
  int*  B1_idx_arr = (int*)(B->indices[1][1]);
  int*  B2_idx_arr = (int*)(B->indices[2][1]);
  double*  B_val_arr = (double*)(B->vals);

  int32_t init_alloc_size = 1048576;
  int32_t A0_pos_capacity = init_alloc_size;
  int32_t A0_idx_capacity = init_alloc_size;
  A0_pos_arr = (int*)malloc(sizeof(int) * A0_pos_capacity);
  A0_idx_arr = (int*)malloc(sizeof(int) * A0_idx_capacity);
  A0_pos_arr[0] = 0;
  int32_t A1_pos_capacity = init_alloc_size;
  int32_t A1_idx_capacity = init_alloc_size;
  A1_pos_arr = (int*)malloc(sizeof(int) * A1_pos_capacity);
  A1_idx_arr = (int*)malloc(sizeof(int) * A1_idx_capacity);
  A1_pos_arr[0] = 0;
  int32_t A2_pos_capacity = init_alloc_size;
  int32_t A2_idx_capacity = init_alloc_size;
  A2_pos_arr = (int*)malloc(sizeof(int) * A2_pos_capacity);
  A2_idx_arr = (int*)malloc(sizeof(int) * A2_idx_capacity);
  A2_pos_arr[0] = 0;
  int32_t A_vals_capacity = init_alloc_size;
  A_val_arr = (double*)malloc(sizeof(double) * A_vals_capacity);

  int32_t A0_pos = 0;
  int32_t A1_pos = 0;
  int32_t A2_pos = 0;
  int32_t B0_pos = B0_pos_arr[0];
  while (B0_pos < B0_pos_arr[1]) {
    int32_t iB = B0_idx_arr[B0_pos * 1];
    int32_t B0_end = B0_pos + 1;
    while ((B0_end < B0_pos_arr[1]) && (B0_idx_arr[B0_end * 1] == iB)) {
      B0_end++;
    }
    int32_t A1_pos_start = A1_pos;
    int32_t B1_pos = B0_pos;
    for (int32_t B1_pos = B0_pos; B1_pos < B0_end; B1_pos++) {
      int32_t jB = B1_idx_arr[(B1_pos * 1) + 0];
      int32_t B1_end = B1_pos + 1;
      int32_t A2_pos_start = A2_pos;
      int32_t B2_pos = B1_pos;
      for (int32_t B2_pos = B1_pos; B2_pos < B1_end; B2_pos++) {
        int32_t kB = B2_idx_arr[(B2_pos * 1) + 0];
        int32_t B2_end = B2_pos + 1;
        if (A_vals_capacity <= ((A2_pos + 1) * 1)) {
          int32_t A_vals_capacity_new = 2 * ((A2_pos + 1) * 1);
          A_val_arr = (double*)realloc(A_val_arr, sizeof(double) * A_vals_capacity_new);
          A_vals_capacity = A_vals_capacity_new;
        }
        A_val_arr[A2_pos] = B_val_arr[B2_pos];
        if (A2_idx_capacity <= A2_pos) {
          A2_idx_capacity = 2 * A2_pos;
          A2_idx_arr = (int*)realloc(A2_idx_arr, sizeof(int) * A2_idx_capacity);
        }
        A2_idx_arr[A2_pos] = kB;
        A2_pos++;
      }
      if (A2_pos_capacity <= (A1_pos + 1)) {
        A2_pos_capacity = 2 * (A1_pos + 1);
        A2_pos_arr = (int*)realloc(A2_pos_arr, sizeof(int) * A2_pos_capacity);
      }
      A2_pos_arr[(A1_pos + 1)] = A2_pos;
      int32_t A2_pos_inserted = A2_pos - A2_pos_start;
      if (A2_pos_inserted > 0) {
        if (A1_idx_capacity <= A1_pos) {
          A1_idx_capacity = 2 * A1_pos;
          A1_idx_arr = (int*)realloc(A1_idx_arr, sizeof(int) * A1_idx_capacity);
        }
        A1_idx_arr[A1_pos] = jB;
        A1_pos++;
      }
    }
    if (A1_pos_capacity <= (A0_pos + 1)) {
      A1_pos_capacity = 2 * (A0_pos + 1);
      A1_pos_arr = (int*)realloc(A1_pos_arr, sizeof(int) * A1_pos_capacity);
    }
    A1_pos_arr[(A0_pos + 1)] = A1_pos;
    int32_t A1_pos_inserted = A1_pos - A1_pos_start;
    if (A1_pos_inserted > 0) {
      if (A0_idx_capacity <= A0_pos) {
        A0_idx_capacity = 2 * A0_pos;
        A0_idx_arr = (int*)realloc(A0_idx_arr, sizeof(int) * A0_idx_capacity);
      }
      A0_idx_arr[A0_pos] = iB;
      A0_pos++;
    }
    B0_pos = B0_end;
  }
  A0_pos_arr[(0 + 1)] = A0_pos;

  A->indices[0][0] = (uint8_t*)(A0_pos_arr);
  A->indices[0][1] = (uint8_t*)(A0_idx_arr);
  A->indices[1][0] = (uint8_t*)(A1_pos_arr);
  A->indices[1][1] = (uint8_t*)(A1_idx_arr);
  A->indices[2][0] = (uint8_t*)(A2_pos_arr);
  A->indices[2][1] = (uint8_t*)(A2_idx_arr);
  A->vals = (uint8_t*)A_val_arr;
  A->dimensions[0] = B->dimensions[0];
  A->dimensions[1] = B->dimensions[1];
  A->dimensions[2] = B->dimensions[2];

  std::cout << A->dimensions[0] << " " << A->dimensions[1] << " " << A->dimensions[2] << " " << endl;

  return 0;
}
