#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Thread %d of %d: Hello!\n", thread_num, num_threads);
    }
	
	
	return 0;
}