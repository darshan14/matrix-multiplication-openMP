#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <sys/time.h>

/*Enter Total number of matrix dimensions*/
#define N 1000
#define MAX_DIM 1000*1000

#define BLOCK_SIZE 128
#define min(x,y) (((x)<(y))?(x):(y))

int A[N][N];
int B[N][N];
int C_naive[N][N];
int C_block[N][N];
int vectorA[MAX_DIM];
int vectorB[MAX_DIM];


/*void display(int x[N][N]) {
	int i,j;
	for (i= 0; i< N; i++)
		{
			for (j= 0; j< N; j++)
			{
				printf("%d\t",x[i][j]);
			}
			printf("\n");
		}
}*/

void convert(int dim){
	#pragma omp parallel for
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			vectorA[i * dim + j] = A[i][j];
			vectorB[j * dim + i] = B[i][j];
		}
	}
}

void naiveMultiplication(int dim) {
	int i,j,k;
	struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
	
	gettimeofday(&tv1, &tz);
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
			C_naive[i][j] = 0;
            for (k = 0; k < dim; k++) {
                C_naive[i][j] += A[i][k] * B[k][j];
            }
        }
	}

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Naive Elapsed time = %f seconds.\n", elapsed);
	//display(C_naive);
}


void blockMultiplication(int dim) {
	int i,j,k,bs,ii,jj,kk,sum;
	struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
	bs = BLOCK_SIZE;
	
	convert(dim);
	
	gettimeofday(&tv1, &tz);

	#pragma omp parallel for private(i, j, k, ii, jj, kk, sum) shared(C_block) schedule(static)
	for(ii = 0; ii < dim; ii += bs)
		for(jj = 0; jj < dim; jj += bs)
			for(kk = 0; kk < dim; kk += bs)
				for(i = ii; i < min(dim, ii+bs); i++)
					for(j = jj; j < min(dim, jj+bs); j++) {
						sum = 0;
						for(k = kk; k < min(dim, kk+bs); k++)
							sum += vectorA[i * dim + k] * vectorB[j * dim + k];
						C_block[i][j] = sum;
					}
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Block Parallel Elapsed time = %f seconds.\n", elapsed);
	//display(C_block);
}


int main(int argc,char*argv[]) 
{
    int i,j;

    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
		{
           A[i][j] = rand();
		   B[i][j] = rand();
		}
		
	//omp_set_num_threads(omp_get_num_procs());
	
	for(int nThread = 1; nThread <=4; nThread++) {
		printf("Number of Threads: %d \n",nThread);
		omp_set_num_threads(nThread);

		naiveMultiplication(N);
		
		blockMultiplication(N);
		
		printf("\n");
	}
}