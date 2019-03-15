#include <iostream>
#include "taco.h"
#include "taco/matrix_transpose.h"
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

int main(int argc, char* argv[]) {
  std::string filename = argv[1];
  // Read tensor data
  Format csr({Dense,Sparse});

  // Create tensors
  Tensor<double> B = taco::read(filename, csr, true);
  Tensor<double> A("A", {B.getDimension(1),B.getDimension(0)}, csr);

  taco_tensor_t *At = (taco_tensor_t*)A.getTacoTensorT();
  taco_tensor_t *Bt = (taco_tensor_t*)B.getTacoTensorT();

  taco::util::Timer timer;                                   
  timer.start();                                             
  taco::mat_csr_transpose_halfperm(At, Bt);
  timer.stop();                                              
  taco::util::TimeResults result = timer.getResult();        
  cout << "halfperm:\t\"" << filename << "\":\t" << result << " ms" << endl;   
  timer.clear_cache();

  taco::util::Timer timer2;                                   
  timer2.start();                                             
  taco::mat_csr_transpose_qsort(At, Bt);
  timer2.stop();                                              
  result = timer2.getResult();        
  cout << "coordinate:\t\"" << filename << "\":\t" << result << " ms" << endl;   


}
