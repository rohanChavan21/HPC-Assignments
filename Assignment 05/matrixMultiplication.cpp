#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    int numThreads, matrixSize;

    cout << "Enter the number of threads: ";
    cin >> numThreads;

    cout << "Enter the size of the square matrices (N x N): ";
    cin >> matrixSize;

    srand(time(nullptr)); // Initialize random number generator

    vector<vector<double>> matrixA(matrixSize, vector<double>(matrixSize));
    vector<vector<double>> matrixB(matrixSize, vector<double>(matrixSize));
    vector<vector<double>> matrixC(matrixSize, vector<double>(matrixSize));

    // Initialize matrices with random values
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixA[i][j] = rand() % 100 + 1; // Initialize with random values (1-100)
            matrixB[i][j] = rand() % 100 + 1;
            matrixC[i][j] = 0.0; // Initialize result matrix to 0
        }
    }

    // Set the number of threads
    omp_set_num_threads(numThreads);

    // Parallel section for matrix multiplication
    #pragma omp parallel for shared(matrixA, matrixB, matrixC)
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // Print the resulting matrix C
    cout << "Resulting Matrix:" << endl;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << matrixC[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
