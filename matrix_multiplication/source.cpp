/**
	Edwin Perea
	CSCI 176, Dr. Park

	Parallel program for computing matrix multiplication
	using pthreads.
	Main  function takes args from command line and creates
	threads which carry out the matrix multiplication in a 
	task parallel format.

	To compile and run in Linux terminal:
	$>g++ source.cpp -pthread
	$>./a.out [thread_count] [l] [m] [n]

*/

#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
using namespace std;
#define BILLION 1000000000L

pthread_mutex_t c_lock = PTHREAD_MUTEX_INITIALIZER;



int thread_c, l, m, n;
double **matrix_a, **matrix_b, **matrix_c;


double** allocDynArray(int rows, int cols);
void freeDynArrays();
void* matrixMult(void* rank);
void initAB();

int main(int argc, char* argv[]){


	thread_c = atoi(argv[1]);
	l = atoi(argv[2]);
	m = atoi(argv[3]);
	n = atoi(argv[4]);

	cout << "L=" << l << ", m=" << m << ", n=" << n << endl;
	uint64_t diff;
	struct timespec start, end;
	pthread_t my_threads[thread_c];
	long thread_id;

	//allocate arrays with new
	matrix_a = allocDynArray(l, m);
	matrix_b = allocDynArray(m, n);
	matrix_c = allocDynArray(l, n);
	initAB();

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_create(&my_threads[thread_id], NULL, matrixMult, (void*)thread_id);

	for(thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_join(my_threads[thread_id], NULL);

	clock_gettime(CLOCK_MONOTONIC, &end); //end time
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	
	// Print first 20 x first 10
	cout << "C: First 20, First 10" << "\n"; 
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			cout << matrix_c[i][j] << " ";
		}
	cout << "\n";
	}
	cout << "\n";

	cout << "C: Last 20, Last 10" << "\n"; 
	//Print last 20 x last 10
	for(int i = l-20; i < l; i++){
		for(int j = m-10; j < m; j++){
			cout << matrix_c[i][j] << " ";
		}
	cout << "\n";
	}


	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff );


	//free mem
	freeDynArrays();
	
	return 0;
}

/**
	This function allocates the space for the dynamic
	2d arrays using 'new' based on l,m,n
*/
double** allocDynArray(int rows, int cols){
	double** matrix = new double*[rows];
	for(int i = 0; i < rows; i++)
		matrix[i] = new double[cols];

	return matrix;
}

/**
	This function fills up both matrices a and
	b: Aij = i+j and Bij = i+j+1
*/	
void initAB(){
	for(int i = 0; i < l; i++){
		for(int j = 0; j < m; j++){
			matrix_a[i][j] = i+j;
		}
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			matrix_b[i][j] = i+j+1;
		}
	}
}

/**
	Frees up the memory for each of the dynamic 2d 
	arrays
*/
void freeDynArrays(){
	for(int i = 0; i < l; i++){
		delete [] matrix_a[i];
		delete [] matrix_c[i];
	}
	delete [] matrix_a;
	delete [] matrix_c;
	for(int i = 0; i < m; i++)
		delete [] matrix_b[i];
	delete [] matrix_b;
}

/**
	Function takes the thread_id to calculate
	how many rows and the section that thread
	will calculate
	Second portion each thread does the summation:
	Starting from each col of row my_first_i -> my_last_i 
	of matrix_a * each row k of col j of matrix_b
	and assigns that to the final matrix_c
*/
void* matrixMult(void* rank){

	long my_rank = (long) rank;
	int my_first_i, my_last_i, my_count;
	int quot = l / thread_c;
	int rem = l % thread_c;
	double my_sum;
	
	if(my_rank < rem){
		my_count = quot + 1;
		my_first_i = my_rank * my_count;
	}
	else{
		my_count = quot;
		my_first_i = my_rank * my_count + rem;
	}
	my_last_i = my_first_i + my_count - 1;

	pthread_mutex_lock(&c_lock);
	cout << "Thread_: " << my_rank << ": " << my_first_i << " ~ " << my_last_i << ", step: " << quot << "\n";
	pthread_mutex_unlock(&c_lock);

	for(int i = my_first_i; i <= my_last_i; i++){
		for(int j = 0; j < n; j++){
			my_sum = 0.0;
			for(int k = 0; k < m; k++){
				my_sum = my_sum + matrix_a[i][k] * matrix_b[k][j];
			}
			matrix_c[i][j] = my_sum;	
		}	
	} 
}