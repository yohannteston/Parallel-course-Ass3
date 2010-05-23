#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

double **V,**Q;

double vecNorm(double *,int );
double scalarProd(double *,double *,int);

int timer(void)
{
	struct timeval tv;
	gettimeofday(&tv, (struct timezone*)0);
	return (tv.tv_sec*1000000+tv.tv_usec);
}

int main(int argc, char *argv[]) {
   int n,i,j,k;
	double ttime;
   double t,sigma,temp_norm,norm;

   n = atoi(argv[1]);
  
   //Allocate and fill vectors
   V = (double **)malloc(n*sizeof(double *));
   Q = (double **)malloc(n*sizeof(double *));
   for(i=0;i<n;i++){
      V[i] = (double *)malloc(n*sizeof(double));
      Q[i] = (double *)malloc(n*sizeof(double));
      }

	srand(time(NULL));

  for (i = 0; i<n; i++)
	  for(j=0;j<n;j++)
		  V[i][j] = rand();// % 5 + 1;
    
	ttime=timer();
   for(i=0;i<n;i++){
	   
	   temp_norm = vecNorm(V[i],n);
	   for (k=0; k<n; k++)
		   Q[i][k] = V[i][k]/temp_norm;

		#pragma omp parallel for private(temp_norm, k, j, sigma)
      for(j=i+1;j<n;j++){
			 sigma = scalarProd(Q[i],V[j],n);
			 for(k=0;k<n;k++)
				V[j][k] -=sigma*Q[i][k];
			 
	  }
   }

	ttime=timer()-ttime;
   printf("Time: %f\n",ttime/1000000.0);
	//printf("Check orthogonality: %e \n",scalarProd(Q[n/2], Q[n/3], n));
	
   return 0;
   
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
