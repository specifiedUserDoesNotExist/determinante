#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberInversion(int *, int, int);
void permuta(int *, int [], int);
float determinante(float [], int);
int factorial(int);
void readFile(char [], float [], int);

int main(int argc, char *argv[]){

	int sizeMatrix = strtol(argv[1], NULL, 10);
	float matrix[sizeMatrix*sizeMatrix];
	
	readFile(argv[2], matrix, sizeMatrix);
	
	float d;
	d = determinante(matrix, sizeMatrix);
	printf("%f\n",d);
	
	return 0;
}

float determinante(float matrix[], int n){
	
	float det = 0.0;
	int v[n];
	for (int i=0;i<n;i++) v[i]=i;
	
	int permutation[factorial(n)*n];
	permuta(v, permutation, n);

	
	float prod;
	int sign;
	for (int j=0;j<factorial(n);j++){
		prod=1.0;
		sign = numberInversion(permutation, n, j*n);
		for (int i=0;i<n;i++){
			prod *= matrix[i*n+permutation[n*j+i]];
		}
		det += sign*prod;
	}
	
	return det;
}

int factorial(int n){
	int f = 1;
	for (int i=n;i>1;i--)f*=i;
	return f;
}

// Heap's Algorithm
void permuta(int *A, int permutation[], int N){

	int vaux;
	int count;
	int c[N];
	for (int i=0;i<N;i++) c[i]=0;
	
	count = 0;
	for (int i=count;i<N+count;i++){
		permutation[i] = A[i];
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
				permutation[i] = A[i%count];
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

int numberInversion(int lista[], int n, int init){

	int s = 0;
	int v[2] = {1,-1};
	
	for (int i = init; i < init+n; i++){
		for (int j = i; j < init+n; j++){
			if (lista[i] > lista[j]){
				s+=1;
			}
		}
	}
	return v[s%2];
}

void 
readFile(
	char file[],
	float matrix[], 
	int sizeMatrix)
{
	
	int sizeLine = 30;
	
	FILE *fp;
	
	fp = fopen(file,"r");
	
	char str[sizeLine];
	char sep[2]=",";
	char *token;

	int count=0;
	
	while( fgets (str, sizeLine, fp)!=NULL ) {
		token = strtok(str, sep);
		while ( token != NULL ){
			matrix[count++] = strtod(token, NULL);
			token = strtok(NULL, sep);
		}
	}
	fclose(fp);
}
