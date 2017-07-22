#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <cfloat>

using namespace std;

float** matrixGenarator(int);
void sequentialMultiplication(int,float**,float**, float**);
int sizeOfTheMatrix(int,int);
float mean(int, float*);
float standardDeviation(int, float, float*);
float correctSampleSizeCalculator(float,float, float, float);
float multiply(int);
void runMultiply(int,int);

int main() {

    int matrix_size=200;
    int sample_size = 50;
    for(int i=0; i<10; ++i){
        matrix_size = sizeOfTheMatrix(matrix_size,i);
       runMultiply(matrix_size,sample_size);
    }
    cout<< "final matrix size : "<<matrix_size;


    return 0;
}

/*
 * Function which take two matrices as arguments and calculate its product sequentially. rowCount=columnCount=n
 */
void sequentialMultiplication(int n,float** matrixA, float** matrixB, float** matrixC){

    for(int i=0; i<n ;++i){
        for(int j=0; j<n; ++j){
            matrixC[i][j]=0;
            for(int k=0; k<n; ++k){
                matrixC[i][j] += matrixA[i][k]*matrixB[k][j];

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
            return matrix;
    }

}

void runMultiply(int matrixSize, int sampleSize){

    float execution_time = 0;
    float mean_val = 0,standardDeviation_val=0,r_value=5,z_value=1.960,correctSampleSize=0;
    float* execution_time_array = new float[sampleSize]();
    for(int i=0; i<sampleSize; ++i){
      execution_time = multiply(matrixSize);
        execution_time_array[i] = execution_time;
    }
    mean_val = mean(sampleSize, execution_time_array);
    standardDeviation_val = standardDeviation(sampleSize,mean_val,execution_time_array);
    correctSampleSize = correctSampleSizeCalculator(z_value,r_value, standardDeviation_val, mean_val);

    cout<< "correct sample size : "<<correctSampleSize<<"for matrix size :"<<matrixSize<<endl;
}


float multiply(int matrixSize){
    float** matrixA = matrixGenarator(matrixSize);
    float** matrixB = matrixGenarator(matrixSize);
    float** matrixC = matrixGenarator(matrixSize);

    clock_t tStart = clock();

    sequentialMultiplication(matrixSize,matrixA,matrixB,matrixC);

    float execution_time = (float)(clock() - tStart)/CLOCKS_PER_SEC;

    return execution_time;

}

float correctSampleSizeCalculator(float z_value,float r_value,float std,float mean){

    float n = (100*z_value*std)/(r_value*mean);
    return pow(n,2);

}

int sizeOfTheMatrix(int n,int i)
{
    return n+ 200*i;
}

float mean(int sampleSize, float* ExecutionTimeArray){
    float totalExecutionTime = 0;
    for(int i=0;i<sampleSize;++i){
        totalExecutionTime += ExecutionTimeArray[i];
    }

    return totalExecutionTime/sampleSize;
}

float standardDeviation(int sampleSize, float mean, float* ExecutionTimeArray){
    float deviation = 0;
    float std;
    for(int i=0;i<sampleSize;++i){
        deviation += pow(mean - ExecutionTimeArray[i],2)/sampleSize;
    }
    return sqrt(deviation);
}
