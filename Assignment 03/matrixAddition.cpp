#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to initialize a 2D matrix with random values
void initializeMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Adjust the range as needed
        }
    }
}

// Function to perform matrix addition
void matrixAddition(int** A, int** B, int** C, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int numThreads[] = {1, 2, 4, 8}; // Vary the number of threads
    double start, end;
    
    for (int i = 0; i < sizeof(sizes) / sizeof(int); i++) {
        int size = sizes[i];
        int** A = (int**)malloc(size * sizeof(int*));
        int** B = (int**)malloc(size * sizeof(int*));
        int** C = (int**)malloc(size * sizeof(int*));

        for (int j = 0; j < size; j++) {
            A[j] = (int*)malloc(size * sizeof(int));
            B[j] = (int*)malloc(size * sizeof(int));
            C[j] = (int*)malloc(size * sizeof(int));
        }

        // Initialize matrices A and B
        initializeMatrix(A, size, size);
        initializeMatrix(B, size, size);

        for (int t = 0; t < sizeof(numThreads) / sizeof(int); t++) {
            int threads = numThreads[t];
            omp_set_num_threads(threads);

            start = omp_get_wtime();

            // Perform matrix addition in parallel
            matrixAddition(A, B, C, size, size);

            end = omp_get_wtime();

            printf("Matrix Size: %d, Threads: %d, Execution Time: %f seconds\n", size, threads, end - start);
        }

        // Free memory
        for (int j = 0; j < size; j++) {
            free(A[j]);
            free(B[j]);
            free(C[j]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
