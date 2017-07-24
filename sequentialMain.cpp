#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <sys/time.h>

using namespace std;

float** matrixGenarator(int);
void sequentialMultiplication(int,float**,float**, float**);
float mean(int, float*);
float standardDeviation(int, float, float*);
float correctSampleSizeCalculator(float,float, float, float);
float multiply(int);
void runMultiply(int,int);

int main() {

    int matrix_size=200;
    int sample_size;
    for(int i=200; i<=2000; i=i+200){
        matrix_size = i;
        if(i==200){
            //corrected sample size for n=200
            sample_size = 100;
        }
        else{
            //corrected sample size for other n values
            sample_size = 10;
        }

       runMultiply(matrix_size,sample_size);
    }
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
        //randomizing seed
        srand((unsigned)time(0));
        float randomNumber;
        for(int i=0; i<n; ++i) {
            for (int j = 0; j < n; ++j) {
                //This will generate a number from 0.0 to RAND_MAX:

                randomNumber = (float)rand() / RAND_MAX * 10;
                matrix[i][j] = randomNumber;

            }

        }

        return matrix;


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

    FILE *f = fopen("overview.txt", "a");
    fprintf(f, "%s, %d, %f, %f, %f\n", "Sequential", matrixSize, sampleSize, mean_val, standardDeviation_val);
    cout<<" for matrix size :"
        <<matrixSize<< " mean execution time : "<< mean_val <<"s"<<" std : "<<standardDeviation_val<<"s"<<endl;
}


float multiply(int matrixSize){
    float** matrixA = matrixGenarator(matrixSize);
    float** matrixB = matrixGenarator(matrixSize);
    float** matrixC = matrixGenarator(matrixSize);

    struct timeval start, end;

    //clock() reporting CPU time, instead of real time.so use following method

    gettimeofday(&start, NULL);
    sequentialMultiplication(matrixSize,matrixA,matrixB,matrixC);
    gettimeofday(&end, NULL);

    double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixC;

    return delta;

}

float correctSampleSizeCalculator(float z_value,float r_value,float std,float mean){

    float n = (100*z_value*std)/(r_value*mean);
    return pow(n,2);

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
    for(int i=0;i<sampleSize;++i){
        deviation += pow(mean - ExecutionTimeArray[i],2)/sampleSize;
    }
    return sqrt(deviation);
}
