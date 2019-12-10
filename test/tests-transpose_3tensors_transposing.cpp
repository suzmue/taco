#include "test.h"
#include "test_tensors.h"

#include "taco/tensor.h"
#include "taco/storage/storage.h"
#include "taco/transpose.h"

using namespace taco;

namespace transposing_tests {

typedef int                     IndexType;
typedef std::vector<IndexType>  IndexArray; // Index values
typedef std::vector<IndexArray> Index;      // [0,2] index arrays per Index
typedef std::vector<Index>      Indices;    // One Index per level


IndexVar i("i"), j("j"), m("m"), n("n"), k("k"), l("l");

struct TestData {
    TestData(Tensor<double> tensorA, Tensor<double> tensorB, Indices expectedIndices,
            vector<double> expectedValues)
        : tensorA(tensorA),
            tensorB(tensorB), expectedIndices(expectedIndices), expectedValues(expectedValues) {
    }

    Tensor<double> tensorA;
    Tensor<double> tensorB;
    Indices expectedIndices;
    vector<double> expectedValues;
};

struct transposing : public TestWithParam<TestData> {};

// Taken from tensor.cpp
void this_unpack(Tensor<double> tensorA, taco_tensor_t *A){
    vector<ModeIndex> modeIndices;
    TensorStorage storage = tensorA.getStorage();
    Format format = storage.getFormat();

    size_t num = 1;
    for (int i = 0; i < storage.getOrder(); i++) {
      ModeFormat modeType = format.getModeFormats()[i];
      if (modeType == Dense) {
        Array size = makeArray({*(int*)A->indices[i][0]});
        modeIndices.push_back(ModeIndex({size}));
        num *= ((int*)A->indices[i][0])[0];
      } else if (modeType == Sparse) {
        auto size = ((int*)A->indices[i][0])[num];
        Array pos = Array(type<int>(), A->indices[i][0], num+1, Array::UserOwns);
        Array idx = Array(type<int>(), A->indices[i][1], size, Array::UserOwns);
        modeIndices.push_back(ModeIndex({pos, idx}));
        num = size;
      } else {
        taco_not_supported_yet;
      }
    }
    storage.setIndex(taco::Index(format, modeIndices));
    storage.setValues(Array(storage.getComponentType(), A->vals, num));
}

TEST_P(transposing, reordering) {


    Tensor<double> tensorA = GetParam().tensorA;
    Tensor<double> tensorB = GetParam().tensorB;
    tensorB.pack();
    auto& expectedIndices = GetParam().expectedIndices;
    auto& expectedValues = GetParam().expectedValues;

    
        taco_tensor_t *A = (taco_tensor_t*)tensorA.getTacoTensorT();
        taco_tensor_t *B = (taco_tensor_t*)tensorB.getTacoTensorT();

        taco::transpose_132(A, B);
        this_unpack(tensorA, A);

        ASSERT_COMPONENTS_EQUALS(expectedIndices, expectedValues, tensorA);
}

INSTANTIATE_TEST_CASE_P(3tensor_132_small, transposing,
    Values(
           TestData(Tensor<double>("A",{10,10,10},Format({Sparse, Sparse,Sparse})),
                    d333a("B",Format({Sparse, Sparse,Sparse}, {0,1,2})),
// {{0,0,0}, 2},
// {{0,0,1}, 3},
// {{0,2,2}, 4},
// {{1,2,0}, 6},
// {{1,0,1}, 5},
// {{1,2,2}, 7},
// {{2,2,1}, 9},
// {{2,1,2}, 8},


                    {
                      { // A
                        // Sparse index
                        {0, 3}, // 2
                        {0, 1, 2}, // 3
                      },
                      {
                        // Sparse index
                        {0,3,6,8}, // 4 
                        {0,1,2,0,1,2,1,2}, // 6
                      },
                      {
                        // Sparse index
                        {0,1,2,3,4,5,6,7,8}, // 7
                        {0,0,2,2,0,2,2,1}, // 8
                      }
                    },
                    { 2,3,4,6,5,7,9,8}
                    )
           )

);

}
