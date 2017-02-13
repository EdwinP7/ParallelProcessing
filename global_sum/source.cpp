#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

int thread_count;

void *hello(void* rank);

int main(int argc, char* argv[]){

	long thread_id;

	thread_count = atoi(argv[1]);
	pthread_t myThreads[thread_count];

	for(thread_id = 0; thread_id < thread_count; thread_id++)
		pthread_create(&myThreads[thread_id], NULL, hello, (void*)thread_id);
    
    cout << "Hello from the main thread." << endl;

    //Wait for threads
    for(thread_id = 0; thread_id < thread_count; thread_id++)
    	pthread_join(myThreads[thread_id], NULL);

    return 0;
}

void* hello(void* rank){
	int my_rank = (long long) rank;

	cout << "Hello from thread_" << my_rank << " of " << thread_count << endl;
}