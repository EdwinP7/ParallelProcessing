#include <iostream>
using namespace std;
#define MAX 500

int array1[MAX];
void compute(int thread_id, int thread_count);

int main(void){
	int thread_count = 2;
	int thread_ids[2] = {1,2};
	for(int i = 0; i < thread_count; i++){
		cout << "Getting portion of: " << thread_ids[i] << endl;
		compute(thread_ids[i], thread_count);
	}

	return 0;
}

void compute(int thread_id, int thread_count){
	int index_start;
	int index_end;
	int val = MAX/thread_count;
	int start_index = (thread_id - 1) * val;
	int end_index = start_index + val - 1;
	cout << "start: " << start_index << endl;
	cout << "end: " << end_index << endl;

}