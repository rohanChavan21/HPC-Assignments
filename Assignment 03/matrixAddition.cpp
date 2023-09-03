#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_SIZE 2000

void matrixAddition(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE], int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int matrixSizes[] = {250, 500, 750, 1000, 2000};
    int threadCounts[] = {1, 2, 4, 8};

    for (int m = 0; m < 5; m++) {
        int size = matrixSizes[m];
        int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];
        double startTime, endTime;

        // Initialize matrices A and B with random values
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
            }
        }

        printf("Matrix Size: %dx%d\n", size, size);

        // Measure execution time for 1 thread
        omp_set_num_threads(1);
        startTime = omp_get_wtime();
        matrixAddition(A, B, C, size);
        endTime = omp_get_wtime();
        double elapsedTime1Thread = endTime - startTime;
        printf("Execution Time (1 Thread): %f seconds\n", elapsedTime1Thread);

        for (int t = 0; t < 4; t++) {
            int numThreads = threadCounts[t];
            
            // Set the number of threads
            omp_set_num_threads(numThreads);

            // Measure execution time for multiple threads
            startTime = omp_get_wtime();
            matrixAddition(A, B, C, size);
            endTime = omp_get_wtime();
            double elapsedTimeNThreads = endTime - startTime;
            printf("Execution Time (%d Threads): %f seconds\n", numThreads, elapsedTimeNThreads);

            // Calculate and print speedup
            double speedup = elapsedTime1Thread / elapsedTimeNThreads;
            printf("Speedup: %f\n", speedup);
        }

        printf("\n");
    }

    return 0;
}
