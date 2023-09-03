#include <stdio.h>
#include <omp.h>

int main(){
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    int n;
    int scalar;

    printf("Enter the size of the vector: ");
    scanf("%d", &n);

    printf("Enter the scalar to add: ");
    scanf("%d", &scalar);

    int vector[n] = {0};
    for(int i=0; i<n; i++){
        vector[i] = i;
    }

    double stime = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0; i<n; i++){
        vector[i] += scalar;
    }

    double etime = omp_get_wtime();
    double time = etime - stime;

    printf("Resulting vector: \n");
    for(int i=0; i<n; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
    printf("The time taken is %f ", time);

    return 0;
}