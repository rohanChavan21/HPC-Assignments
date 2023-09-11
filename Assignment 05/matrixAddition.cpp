#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Function to generate a random lower triangular matrix
void generateLowerTriangularMatrix(vector<vector<int>>& mat, int size) {
    mat.resize(size);
    for (int i = 0; i < size; ++i) {
        mat[i].resize(size, 0);
        for (int j = 0; j <= i; ++j) {
            mat[i][j] = rand() % 10; // Fill with random values (change as needed)
        }
    }
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& mat, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int size, numThreads;

    cout << "Enter the size of the matrix: ";
    cin >> size;

    cout << "Enter the number of threads: ";
    cin >> numThreads;

    vector<vector<int>> matrix1, matrix2, result;

    double stime = omp_get_wtime();
    generateLowerTriangularMatrix(matrix1, size);
    generateLowerTriangularMatrix(matrix2, size);
    result.resize(size, vector<int>(size, 0));

    // Set the number of threads
    omp_set_num_threads(numThreads);

    // Parallel computation of the sum
    #pragma omp parallel for shared(matrix1, matrix2, result) schedule(static)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j <= i; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    double etime = omp_get_wtime();

    // Print the matrices and result
    cout << "Matrix 1:" << endl;
    printMatrix(matrix1, size);

    cout << "Matrix 2:" << endl;
    printMatrix(matrix2, size);

    cout << "Result:" << endl;
    printMatrix(result, size);
    double time = etime - stime;
    cout<<"Time Taken is "<<time<<endl;

    return 0;
}
