#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

int timer(void)
{
	struct timeval tv;
	gettimeofday(&tv, (struct timezone*)0);
	return (tv.tv_sec*1000000+tv.tv_usec);
}


double** alloc_matrix(int row, int col){
	int i;
	double** ptr = (double**)malloc(row*sizeof(double*));
	for(i=0;i<row;i++)
		ptr[i] = (double*)malloc(col*sizeof(double));
	return ptr;
}

void init(double** array, int row, int col){
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			array[i][j] = (double)rand();
}

double scalar_product(double** q, int i,  double** v, int j, int row){
	int k;
	double sum = 0.0;
	for(k=0;k<row;k++)
		sum+= q[k][i] * v[k][j];
	return sum;
}

double norm(double** v, int i, int row){
	return sqrt(scalar_product(v,i,v,i,row));
}


int main(int argc, char** argv){
	if(argc != 3){
		printf("Usage: ./gram_schmidt vector_length number_of_vectors\n");
		exit(EXIT_FAILURE);
	}

	double** v;
	double **q;
	double temp_norm, sigma;

	int row = atoi(argv[1]);
	int col = row;
	//int col = atoi(argv[2]);

	int k,i,j,ttime;

	v = alloc_matrix(row, col);
	q = alloc_matrix(row, col);

	// initializes v with random values
	srand(time(NULL));
	init(v, row, col);

	// compute
	ttime=timer();

#pragma omp parallel
	{
#pragma omp single
<<<<<<< HEAD
      {
	for(i=0;i<col;i++){
#pragma omp task private(j, sigma, k, temp_norm) firstprivate(i)
	  {
	    temp_norm = norm(v,i,row);
	    for (k=0; k<row; k++)
	      q[k][i] = v[k][i]/temp_norm;
	    for(j=i+1;j<col;j++){
	      sigma = scalar_product(q,i, v, j,row);
	      for(k=0;k<row;k++)
		v[k][j] -=sigma*q[k][i];
	    }
	  }
	}
	ttime=timer()-ttime;
	printf("Time: %f \n",ttime/1000000.0);
	//printf("Check orthogonality: %e \n",scalar_product(q,col/2,  q,col/3, row));

}
