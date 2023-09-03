#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
using namespace std;

int main(int argc, char* argv[]){
    #pragma omp parallel
        {
            printf("thread No. %d Hello World\n", omp_get_thread_num());
        }

        return 0;
}