#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_PER_BLOCK 16

__global__ void set(int *A, int N)
{
    int idx = threadIdx.x + blockIdx.x * blockDim.x;    	//index saved
    A[idx] = idx;                                       	//A[1] = 1, A[2] = 2, ..., A[N] = N
}

int main(void)
{
    const int N = 128;                                  	//number of steps
    int size =  N * sizeof(int);                        	//to clean up code

    int *d_A;                                           	//device array
    int *h_A;                                           	//host array

    h_A = (int*) malloc(size);                          	//allocate memory to host array
    cudaMalloc((void **) &d_A, size);                   	//allocate memory to device array

    set<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_A, N);  	//launch set kernel on GPU

    cudaMemcpy(h_A, d_A, size, cudaMemcpyDeviceToHost); 	//copy device array to host array

    for(int i = 0; i <= N; i++)
    {
	printf("%d ", h_A[i]);                               	//print host array

	if(i%16 == 0 && i != 0 || i == N)
	{
	    printf("\n");
	}
    }

    free(h_A);                                          	//free host array
    cudaFree(d_A);                                      	//free device arrray

    return 0;
}
