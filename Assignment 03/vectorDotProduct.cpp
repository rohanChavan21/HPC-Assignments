#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n; // Number of elements in the vectors
    int num_threads;

    printf("Enter the number of elements in the vectors: ");
    scanf("%d", &n);


    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);


    int vector1[n];
    int vector2[n];

    // Initialize vectors with random values
    for (int i = 0; i < n; i++) {
        vector1[i] = rand() % 100;
        vector2[i] = rand() % 100;
    }
    // printf("First vector is: \n");
    // for(int i=0; i<n; i++){
    //     printf("%d ", vector1[i]);
    // }
    // printf("\n");
    
    // printf("Second vector is: \n");
    // for(int i=0; i<n; i++){
    //     printf("%d ", vector2[i]);
    // }

    printf("\n");

    int min_scalar_product = 0;
    double stime = omp_get_wtime();
    #pragma omp parallel for num_threads(num_threads) reduction(min:min_scalar_product)
    for (int i = 0; i < n; i++) {
        min_scalar_product += vector1[i] * vector2[i];
    }

    double etime = omp_get_wtime();
    double time = etime - stime;

    printf("Minimum Scalar Product: %d\n", min_scalar_product);
    printf("Time taken is %f", time);

    return 0;
}
