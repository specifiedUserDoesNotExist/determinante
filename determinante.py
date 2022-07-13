# Heap's Algorithm
def permuta(A, lp):
	
	n = len(A)
	
	c = [0 for i in range(n)]
	aux = [A[i] for i in range(n)]
	
	lp.append(aux)

	i = 1
	while i < n:
		if c[i] < i:
			if i%2 == 0:
				A[0], A[i] = A[i], A[0]
			else:
				A[c[i]], A[i] = A[i], A[c[i]]
			aux = [A[i] for i in range(n)]		
			lp.append(aux)
			c[i] = c[i] + 1
			i = 1
		else:
			c[i] = 0
			i = i + 1

def numberInversions(A):
	
	s = 0
	for i in range(len(A)):
		for j in range(i,len(A)):
			if A[i] > A[j]: s = s +1

	return s%2
	
def determinant(A):

	det = 0

	l = [i for i in range(len(A))]
	lp = []
	
	permuta(l, lp)

	for _ in lp:
		prod = 1
		sign = numberInversions(_)
		for i,j in enumerate(_):
			prod = prod * A[i][j]
		det = det + ((-1)**sign)*prod
	
	return det


def main()
	matrix = [
		[1,2,4.5,-1],
		[4,5,-3,11],
		[-15,7,8,9],
		[5,12,45,67]
	]

	print(determinant(matrix))
	
	return



