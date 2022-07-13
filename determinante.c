#include <stdio.h>
#include <string.h>

int numberInversion(int *, int);
void permuta(int *, int (*)[], int);
float determinante(float (*)[], int);
int mf(int);

int main(){

	int N = 4;
	
	float A[4][4] = {
		{1,2,4.5,-1},
		{4,5,-3,11},
		{-15,7,8,9},
		{5,12,45,67}
	};
	
	float d;
	d = determinante(A,N);
	printf("%f\n",d);
	
	return 0;
}

float determinante(float (*A)[], int n){
	
	float det = 0.0;
	int v[n];
	for (int i=0;i<n;i++) v[i]=i;
	
	int lp[mf(n)][n];
	permuta(v, lp, n);

	
	float prod;
	int sign;
	for (int j=0;j<mf(n);j++){
		prod=1.0;
		sign = numberInversion(lp[j], n);
		for (int i=0;i<n;i++){
			prod *= *((*A)+i*n+lp[j][i]);
		}
		det += sign*prod;
	}
	
	return det;
}

int mf(int n){
	int f = 1;
	for (int i=n;i>1;i--)f*=i;
	return f;
}

// Heap's Algorithm
void permuta(int *A, int (*lp)[], int N){

	int vaux;
	int count;
	int c[N];
	for (int i=0;i<N;i++) c[i]=0;
	
	count = 0;
	for (int i=count;i<N+count;i++){
		(*lp)[i] = A[i];
	}
	
	
	int i;
	i = 1;
	while (i<N){
		if (c[i]<i){
			if ((i%2)==0){
				vaux = A[0];
				A[0] = A[i];
				A[i] = vaux;
			}
			else{
				vaux = A[i];
				A[i] = A[c[i]];
				A[c[i]] = vaux;
			}
			count += N;
			for (int i=count;i<N+count;i++){
				(*lp)[i] = A[i%count];
			}
			c[i]+=1;
			i = 1;
		}
		else{
			c[i] = 0;
			i += 1;		
		}
	}
}

int numberInversion(int *A, int n){

	int s = 0;
	int v[2] = {1,-1};
	
	for (int i = 0; i < n; i++){
		for (int j = i; j < n; j++){
			if (A[i] > A[j]){
				s+=1;
			}
		}
	}
	return v[s%2];
}
