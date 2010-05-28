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


double vecNorm(double *vec,int n){
	int i;
	double local_norm = 0;

	for(i=0;i<n;i++){
		local_norm+= (vec[i]*vec[i]);
	}
	return sqrt(local_norm);
}

double scalarProd(double *a,double *b,int n){
	int i;
	double scalar =0.0;

	for(i=0;i<n;i++){
		scalar +=a[i]*b[i];
	}

	return scalar;
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
	//int col = row;
	int col = atoi(argv[2]);

	if(row < col){
		printf("Can not create an orthogonal base with such values. \n");
		exit(-1);
	}		

	int l,k,i,j,ttime;

	v = alloc_matrix(row, col);
	q = alloc_matrix(row, col);

	// initializes v with random values
	srand(time(NULL));
	init(v, row, col);

	// compute
	ttime=timer();
	temp_norm = vecNorm(v[1],col);
	for(k=0;k<col;k++)
		q[1][k] = v[1][k]/temp_norm;

	for(i=1;i<row;i++){	
		{
#pragma omp parallel for private(k,sigma)
			for(j=i;j<row;j++){
				{
					sigma = scalarProd(q[i-1],v[j],col);
					for(k=0;k<col;k++){
						v[j][k] -= sigma*q[i-1][k]; 
					}	
				}
			}
		}
		temp_norm = vecNorm(v[i],col);
		for(k=0;k<col;k++)
			q[i][k] = v[i][k]/temp_norm;
	}

	ttime=timer()-ttime;
	printf("Time: %f \n",ttime/1000000.0);
	//printf("Check orthogonality: %e \n",scalarProd(q[col/2],  q[col/3], row));

}
