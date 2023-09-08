#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int x, y;
        #pragma omp task shared(x)
        x = fibonacci(n - 1);
        #pragma omp task shared(y)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n; // Fibonacci number to compute
    int result;
    int numThreads; // Number of threads to use

    printf("Enter the Fibonacci number to compute: ");
    scanf("%d", &n);

    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);

    omp_set_num_threads(numThreads); // Set the number of threads
    double stime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }
    double etime = omp_get_wtime();
    double time = etime - stime;

    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time taken is %f", time);
    return 0;
}
