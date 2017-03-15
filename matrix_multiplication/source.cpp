/**
	Edwin Perea
	CSCI 176, Dr. Park

	Parallel program for computing matrix multiplication
	using pthreads
	Main  function takes args

	To compile and run in Linux terminal:
	$>g++ -o source.cpp source
	$>./source [num_threads] [a_rows] [a_cols_b_rows] [b_c_cols]


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


	

	/*
	for(int thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_create(&my_threads[thread_id], NULL, compute, (void*)thread_id);

	for(thread_id = 0; thread_id < thread_c; thread_id++)
		pthread_join(my_threads[thread_id]);

	cout << thread_c << "\n";
	*/
	return 0;
}

int** init2dArray(int rows, int cols, int add){
	int** matrix = new int*[rows];
	for(int i = 0; i < rows; i++)
		matrix[i] = new int[cols];

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			matrix[i][j] = i+j+add;

	return matrix;
}



void free2dArray(int** arr){
	for(int i = 0; i < n; i++)
		delete [] arr[i];
	delete [] arr;

}