#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cfloat>

using namespace std;

float** matrixGenarator();
void sequentialMultiplication(int,float,float);
int sizeOfTheMatrix(int,int);
int mean();
int std();
int sampleSize();
float multiply(int);
void runMultiply();

int main() {

    int intial_matrix_size=200;
    int steps = 200;
    int n;
    for(int i=0; i<=steps; ++i){
        n = sizeOfTheMatrix(intial_matrix_size, i);
       multiply(n);
    }
    cout<< "final matrix size : "<<n;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++i){}
    }

    return 0;
}

/*
 * Function which take two matrices as arguments and calculate its product sequentially. rowCount=columnCount=n
 */
void sequentialMultiplication(int n,float** matrixA, float** matrixB){

    for(int i=0; i<n ;++i){
        for(int j=0; j<n; ++j){
            for(int k=0; k<n; ++k){
                matrixA[i][k]*matrixB[k][j];

            }
        }

    }


}

/*Return a nxn matrix filled with random values.seed the generator with the system time then output a single random number,
 which should be different each time we run the program*/
float** matrixGenarator(int n){

        //Initializing a nxn matrix
        float** matrix = new float*[n];
        for(int i = 0; i < n; ++i)
            matrix[i] = new float[n];

        //filling random values to matrix
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                //randomizing seed
                srand((unsigned)time(0));
                //This will generate a number from 0.0 to FLOAT_MAX:
                float randomNumber = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/FLT_MAX));

                matrix[i][j] = randomNumber;

        }

    }

}

void runMultiply(int matrixSize){

    int sampleSize = 50;
    float sum_of_execution_times = 0;
    for(int i=0; i<sampleSize; ++i){
         sum_of_execution_times = sum_of_execution_times + multiply(matrixSize);

    }
}


float multiply(int matrixSize){
    float** matrixA= matrixGenarator(matrixSize);
    float** matrixB= matrixGenarator(matrixSize);

    clock_t tStart = clock();

    sequentialMultiplication(matrixSize,matrixA,matrixB);

    float execution_time = (float)(clock() - tStart)/CLOCKS_PER_SEC;

    return execution_time;

}


int sizeOfTheMatrix(int n, int i)
{
    return n+ 9*i;
}
