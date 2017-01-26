////////////////////////////////////////////////////////
//// Sample time checking code, using macro (get-time).
//// Also showing Unix fork().
//// $>g++ time-fork1.cpp
//// $>./a.out
////////////////////////////////////////////////////////

#include <iostream>
#include <unistd.h>   //for fork()
#include <sys/wait.h> //for wait()
#include <sys/time.h> //for macro GET_TIME(double)
using namespace std;

//macro (in-line expansion) for GET_TIME(double); needs <sys/time.h>
#define GET_TIME(now)\
{ struct timeval t; gettimeofday(&t, NULL);\
  now = t.tv_sec + t.tv_usec/1000000.0; }


int main(int argc, char* argv[])
{
  int i=0;
  int pid;
  int status;
  double start, stop; //for time checking
  
  GET_TIME(start); //time checking starts
   
  pid = fork();
  cout<<"---11111"<<endl;
  
  pid = fork();
  cout<<"---22222"<<endl;
  
  cout<<"---Hello"<<endl;
  
  GET_TIME(stop); //time checking ends
  cout<<"--run time: "<<stop - start<<" sec."<<endl;

  pid = wait(&status);
  cout<<"Child process pid="<<pid<<" exited, Status="<<status<<endl;

  return 0;
}//main

  
