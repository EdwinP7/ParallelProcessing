#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <time.h>
using namespace std;
#define MAX 100

int fibo_i(int n);
int fibo_r(int n);

int main(int argc, char *argv[]){
	
	int pid, status, i, num, num1, num2;
	clock_t time_i, time_r;
	if(argc != 2){
		cout << "Invalid arguement entered in command-line. Please enter an integer after the call to program.\n";
		return 0;
	}
	num = atoi(argv[1]);
	cout << "Fibonacci sequence on: " << num << endl;
	int p1[2], p2[2], p3[2], p4[2];
	int err1 = pipe(p1);
	int err2 = pipe(p2);
	int err3 = pipe(p3);
	int err4 = pipe(p4);

	for(i = 0; i < 3; i++){
		pid = fork();
		if(pid == 0 && i == 0){
			write(p1[1], &num, sizeof(int));
			write(p3[1], &num, sizeof(int));
			read(p2[0], &time_i, sizeof(time_i));
			read(p4[0], &time_r, sizeof(time_r));
			exit(0);
    	}
    	else if(pid == 0 && i == 1){
    		read(p1[0], &num1, sizeof(int));
    		cout << "\nChild 2 reads: " << num1 << endl;
    		time_i = clock(); 
    		fibo_i(num1);
    		time_i = clock() - time_i;
    		write(p2[1], &time_i, sizeof(time_i));
    		exit(0);
    	}
    	else if(pid == 0 && i == 2){
    		read(p3[0], &num2, sizeof(int));
    		time_r = clock();
    		cout << "\n" << fibo_r(num2) << endl;
    		time_r = clock() - time_r;
    		cout << "Took: " << time_r << endl;
    		write(p4[1], &time_r, sizeof(time_r));
    		exit(0);
    	}
	}

    for(i = 0; i <= 3; i++){
		pid = wait(&status);
		cout << "Child (pid=" << pid << ") exited, status=" << status << endl;

	}
	cout << "Fibonacci Recursive took: " << time_r/float(CLOCKS_PER_SEC) << "s" << endl;
	cout << "Fibonacci Iterative took: " << time_i/float(CLOCKS_PER_SEC) << "s" << endl;

	
	return 0;	
}


int fibo_i(int n){
	
}


int fibo_r(int n){
	if(n == 1 || n == 2){
		return 1;
	}
	return (fibo_r(n-1) + fibo_r(n-2));
}







/*
int main(){
	int pid, status, i;
	int p1[2], p2[2];
	int response, response2;
	char s[MAX];

	int err1 = pipe(p1);
	int err2 = pipe(p2);
	cout << a << b << endl;
	for(i = 0; i < 3; i++){
		pid = fork();
		if(pid == 0 && i == 1){
			//close(p1[0]);
			//close(p2[1]);
			cout << "Menu: \n";
			cout << "-------- \n";
			cout << "1. Display Hello " << endl;
			cout << "2. Display Bye " << endl;
			cout << "-------- \n";
			cout << "Choice (1 - 2)?\n";
			cin >> response;

			write(p1[1], &response, sizeof(int));
			read(p2[0], s, MAX);

			cout << s << endl;
			//close(p1[1]);
			//close(p2[0]);
			exit(0);
		}
		else if(pid == 0 && i == 2){
			//close(p1[1]);
			//close(p2[0]);
			read(p1[0], &response2, sizeof(int));
			switch(response2){
				case 1 : strcpy(s, "Hello\n");
						 break;
				case 2 : strcpy(s, "Bye\n");
						 break;
				default: strcpy(s, "Try option 1 or 2.\n");
						 break;
			} /*switch*/
						 /*
			write(p2[1], s, MAX);
			//close(p1[0]);
			//close(p2[1]);
			exit(0);
		} 
	} 

	for(i = 0; i <= 2; i++){
		pid = wait(&status);
		cout << "Child (pid=" << pid << ") exited, status=" << status << endl;
	}
	return 0;
} */