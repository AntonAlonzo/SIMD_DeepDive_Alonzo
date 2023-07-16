/*

	Author:		Alonzo, Jose Anton S.
	Section:	CEPARCO S11
	Process:
				Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Initialize data

	Parameters:
		n		:	number of elements in the vector
		vector	:	vector to reset

*/
void initialize_data(size_t n, double* vector)
{
	for (int i = 0; i < n; i++)
		vector[i] = (double)i;
}

/*
	Set all elements of a vector to 0

	Parameters:
		n		:	number of elements in the vector
		vector	:	vector to reset

*/
void reset_vector(size_t n, double* vector)
{
	for (int i = 0; i < n; i++)
		vector[i] = 0.0f;
}

/*
	Displays output vector and checks for errors based on process specification

	Parameters:
		n		:	number of elements in the vector
		h_out	:	output vector (Y)
		h_in	:	input vector (X)

*/
void display_results(size_t n, double* h_out, double* h_in)
{
	size_t err_count = 0;

	printf("OUTPUT = [ ");

	for (int i = 0; i < n; i++) {
		if (!(i < 3 || i > n - 4)) /* to avoid out-of-bounds error */

			if (h_out[i] != h_in[i - 3] + h_in[i - 2] + h_in[i - 1] + h_in[i] + h_in[i + 1] + h_in[i + 2] + h_in[i + 3])
				err_count++;

		if (i > 2 && i < 8) /* print first 5 non-zero values */
			printf(" %f ,", h_out[i]);

	};

	printf(" ... ] \n");
	printf("ERROR COUNT = %zu \n\n", err_count);
}

/*
	C Function for the specified vector operation

	Parameters:
		n		:	number of elements in the vector
		h_out	:	output vector (Y)
		h_in	:	input vector (X)
		
*/
void C_stencil(size_t n, double* h_out, double* h_in)
{
	for (int i = 0; i < n; i++) {

		if (!(i < 3 || i > n - 4)) /* to avoid out-of-bounds error */

			h_out[i] = h_in[i - 3] + h_in[i - 2] + h_in[i - 1] + h_in[i] + h_in[i + 1] + h_in[i + 2] + h_in[i + 3];

	}
}

/* Assembly function calls*/
extern void x86_stencil(size_t n, double* d_out, double* d_in);
extern void SIMD_stencil(size_t n, double* d_out, double* d_in);

int main() 
{
	/* Initialization of variables */

	const size_t VECTOR_SIZE = 1<<28;							/* EDIT HERE: number of elements */
	const size_t VECTOR_BYTES = VECTOR_SIZE * sizeof(double);	/* byte size of vector*/
	const int iter = 30;										/* number of runs */
	double* X;
	double* Y;													/* vectors */

	int i;														/* incrementer */

	clock_t start, end;											/* timer */
	double time_total = 0;										/* total runtime taken */
	double time_taken, time_ave;								/* one runtime, average runtime */
	

	/* Allocate vector memory */
	X = (double*)malloc(VECTOR_BYTES);
	Y = (double*)malloc(VECTOR_BYTES);

	printf("\n= = = = = = = = = = 1D STENCIL : START OF PROGRAM = = = = = = = = = =\n\n");
	printf("VECTOR SIZE = %zu \n", VECTOR_SIZE);

	printf("\n= = = = = = = = = = PART 1 : C VERSION = = = = = = = = = =\n\n");

	/* initialize data */
	initialize_data(VECTOR_SIZE, X); // Input: [0, 1, 2, ... VECTOR_SIZE - 1]
	reset_vector(VECTOR_SIZE, Y);

	/* flush kernel */
	C_stencil(VECTOR_SIZE, Y, X);

	/* run kernel n times */
	for (i = 0; i < iter; i++)
	{
		reset_vector(VECTOR_SIZE, Y);

		start = clock();
		C_stencil(VECTOR_SIZE, Y, X);
		end = clock();

		time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;
		time_total += time_taken;
	}

	time_ave = time_total / iter;
	printf("AVERAGE RUNTIME = %f ms\n", time_ave);
	display_results(VECTOR_SIZE, Y, X);

	printf("\n= = = = = = = = = = PART 2 : x86-64 VERSION = = = = = = = = = =\n\n");

	reset_vector(VECTOR_SIZE, Y);

	// flush kernel
	x86_stencil(VECTOR_SIZE, Y, X);

	// run kernel n times 
	for (i = 0; i < iter; i++)
	{
		reset_vector(VECTOR_SIZE, Y);

		start = clock();
		x86_stencil(VECTOR_SIZE, Y, X);
		end = clock();

		time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;
		time_total += time_taken;
	}

	time_ave = time_total / iter;
	printf("AVERAGE RUNTIME = %f ms\n",  time_ave);
	display_results(VECTOR_SIZE, Y, X);

	printf("\n= = = = = = = = = = PART 3 : SIMD VERSION = = = = = = = = = =\n\n");
	
	reset_vector(VECTOR_SIZE, Y);

	// flush kernel
	SIMD_stencil(VECTOR_SIZE, Y, X);

	// run kernel n times 
	for (i = 0; i < iter; i++)
	{
		reset_vector(VECTOR_SIZE, Y);

		start = clock();
		SIMD_stencil(VECTOR_SIZE, Y, X);
		end = clock();

		time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;
		time_total += time_taken;
	}

	time_ave = time_total / iter;
	printf("AVERAGE RUNTIME = %f ms\n", time_ave);
	display_results(VECTOR_SIZE, Y, X);
	
	printf("\n= = = = = = = = = = END OF PROGRAM = = = = = = = = = =\n\n");

	/* deallocate vector memory */
	free(X);
	free(Y);

	return 0;
}