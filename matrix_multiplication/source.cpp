/**
	Edwin Perea
	CSCI 176, Dr. Park

	Parallel program for computing matrix multiplication
	using pthreads
	Main  function takes args

	To compile and run in Linux terminal:
	$>g++ -o source.cpp source
	$>./source [thread_count] [l] [m] [n]

*/

#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int thread_c, l, m, n;
int **matrix_a, **matrix_b, **matrix_c;


int** init2dArray(int rows, int cols, int add);
void free2dArray(int** arr);


int main(int argc, char* argv[]){

	l = atoi(argv[1]);
	m = atoi(argv[2]);
	n = atoi(argv[3]);
	thread_c = atoi(argv[1]);

	pthread_t my_threads[thread_c];

	matrix_a = init2dArray(l, m, 1);
	matrix_b = init2dArray(m, n, 0);

	for(int i = 0; i < l; i++){
	cout << "| ";
		for(int j = 0; j < m; j++){
			cout << matrix_a[i][j] << " ";
		}
	cout << "|\n";
	}
	cout << endl;
	for(int i = 0; i < m; i++){
	cout << "| ";
		for(int j = 0; j < n; j++){
			cout << matrix_b[i][j] << " ";
		}
	cout << "|\n";
	}


	for(int thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_create(&my_threads[thread_id], NULL, compute, (void*)thread_id);

	for(thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_join(my_threads[thread_id]);

	cout << thread_c << "\n";

	return 0;
}

int** dec2dArray(int rows, int cols, int add){
	int** matrix = new int*[rows];
	for(int i = 0; i < rows; i++)
		matrix[i] = new int[cols];

	return matrix;
}

void initA(){
	for(int i = 0; i < l; i++)
		for(int j = 0; j < m; j++)
			matrix_a[i][j] = i+j+1;
}

void initB(){
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			matrix_b[i][j] = i+j;
}


void free2dArray(int** arr){
	for(int i = 0; i < n; i++)
		delete [] arr[i];
	delete [] arr;

}

void* matrixMult(void* rank){
	long my_rank = (long) rank;
	int quot, my_first_i, my_last_i, my_count, my_sum;
	int quot = L / thread_c;
	int rem = L % thread_c

	if(my_rank < rem){
		my_count = quot + 1;
		my_first_i = my_rank * my_count;
	}
	else{
		my_count = quot;
		my_first_i = my_rank * my_count + rem;
	}
	my_last_i = my_rank * my_count + rem;

	for(int i = my_first_i; i <= my_last_i; i++){
		my_sum = 0;
		for(int j = 0; j < n; j++)
			for(int k = 0; k < m; k++)
				my_sum += matrix_a[i][j] * matrix_b[j][i];
		matrix_c[i][j] = my_sum;
	} 




}