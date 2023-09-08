#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int vectorSize = 200;
    vector<int> vectorA(vectorSize, 1); // Initialize a vector of size 200 with all elements as 1

    int numThreads;
    cout << "Enter the number of threads: ";
    cin >> numThreads;
    omp_set_num_threads(numThreads);

    double start_time, end_time;

    // Using STATIC schedule with nowait
    cout << "Using STATIC Schedule with nowait:\n";
    for (int chunkSize = 1; chunkSize <= 100; chunkSize += 10) {
        start_time = omp_get_wtime();

        #pragma omp parallel shared(vectorA) num_threads(numThreads)
        {
            #pragma omp for schedule(static, chunkSize) nowait
            for (int i = 0; i < vectorSize; i++) {
                vectorA[i] += 1; // Scalar addition
            }
        }

        end_time = omp_get_wtime();
        cout << "Chunk Size: " << chunkSize << " Time taken: " << end_time - start_time << " seconds\n";
    }

    // Using DYNAMIC schedule with nowait
    cout << "Using DYNAMIC Schedule with nowait:\n";
    for (int chunkSize = 1; chunkSize <= 100; chunkSize += 10) {
        start_time = omp_get_wtime();

        #pragma omp parallel shared(vectorA) num_threads(numThreads)
        {
            #pragma omp for schedule(dynamic, chunkSize) nowait
            for (int i = 0; i < vectorSize; i++) {
                vectorA[i] += 1; // Scalar addition
            }
        }

        end_time = omp_get_wtime();
        cout << "Chunk Size: " << chunkSize << " Time taken: " << end_time - start_time << " seconds\n";
    }

    return 0;
}
