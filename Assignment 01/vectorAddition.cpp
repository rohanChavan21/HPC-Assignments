#include<omp.h>
#include<pthread.h>
#include<stdio.h>

int main(){
    int N = 1000;
    int arr[1000];
    for(int i=0; i<N; i++){
        arr[i] = 10;
    }

    int brr[1000];
    for(int i=0; i<N; i++){
        brr[i] = 20;
    }

    int crr[1000] = {0};
    double stime = omp_get_wtime();
    for(int i=0; i<N; i++){
        crr[i] = brr[i] + arr[i];
        printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
    }

    for(int i=0; i<N; i++){
        printf("%d ", crr[i]);
    }

    double etime = omp_get_wtime();
    double time = etime - stime;
    printf("Time taken is %f\n", time);

    return 0;
}