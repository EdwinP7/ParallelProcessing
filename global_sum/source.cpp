/* 
* Edwin Perea
* Dr. Park - CSCI 176 Prog2
* This program is an implementation of the global sum
* problem, where an array of size 50000000 is split
* among several threads and each thread comoutes a 
* partial sum. It is an example of parallel processing to 
* showcase the time difference between a serial program vs parallel
*/

#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
using namespace std;
#define MAX 500000000
#define BILLION 1000000000L //used for nanosecond

pthread_mutex_t c_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sum_lock = PTHREAD_MUTEX_INITIALIZER;
int thread_count;
int my_array[MAX];
float global_sum;

void* compute(void* rank);

int main(int argc, char* argv[]){

	long thread_id;
	uint64_t diff;
	struct timespec start, end; //for time

	for(int i = 0; i < MAX; i++){
		my_array[i] = i+1;
	}
	cout << size_t(my_array) << endl;
	thread_count = atoi(argv[1]);
	pthread_t myThreads[thread_count];

	clock_gettime(CLOCK_MONOTONIC, &start); //start time
	for(thread_id = 0; thread_id < thread_count; thread_id++){	
		pthread_create(&myThreads[thread_id], NULL, compute, (void*)thread_id);
	}
    
    
    //Wait for threads
    for(thread_id = 0; thread_id < thread_count; thread_id++)
    	pthread_join(myThreads[thread_id], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end); //end time
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
    cout << "Final sum: " << global_sum << endl;
    return 0;
}

void* compute(void* rank){
	int my_id = long(rank); // typecast (void*) to long
	int partition_size, start_index, end_index; // init partial_sum only to 0
	float partial_sum = 0;
	partition_size = MAX/thread_count; // how many values each thread will compute
	start_index = my_id * partition_size; // start index uses thread's id
	end_index = start_index + partition_size - 1; // minus one to make up for index starting at 0
	
	// computation of partial sum
	for(int i = start_index; i <= end_index; i++){
		partial_sum += my_array[i];
	}

	// lock for global sum computation
	pthread_mutex_lock(&sum_lock);
	global_sum += partial_sum;
	pthread_mutex_unlock(&sum_lock);

	// lock for cout
	pthread_mutex_lock(&c_lock);
	cout << "Hello from thread_" << my_id << " Start: " << start_index << " End: " << end_index << endl;
	cout << "My sum: " << partial_sum << endl;
	pthread_mutex_unlock(&c_lock);
}