#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

int main() {
    int num_samples;
    int num_threads;

    cout << "Enter the number of samples: ";
    cin >> num_samples;

    if (num_samples <= 0) {
        cout << "Invalid number of samples. Please use a positive value." << endl;
        return 1; // Exit with an error code
    }

    cout << "Enter the number of threads: ";
    cin >> num_threads;

    if (num_threads <= 0) {
        cout << "Invalid number of threads. Please use a positive value." << endl;
        return 1; // Exit with an error code
    }

    double x, y;
    int num_inside = 0;

    // Set the number of threads for parallel regions
    omp_set_num_threads(num_threads);
    double stime = omp_get_wtime();
    #pragma omp parallel private(x, y) reduction(+:num_inside)
    {
        unsigned int seed = static_cast<unsigned int>(time(NULL)) + omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < num_samples; i++) {
            x = static_cast<double>(rand()) / RAND_MAX;
            y = static_cast<double>(rand()) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                num_inside++; // Point is inside the quarter-circle
            }
        }
    }
    double etime = omp_get_wtime();
    double timeTaken = etime - stime;
    double pi_estimate = 4.0 * static_cast<double>(num_inside) / num_samples;
    cout << "Estimated value of Pi: " << pi_estimate << endl;
    cout <<"Time taken is "<<timeTaken<<endl;


    return 0;
}
