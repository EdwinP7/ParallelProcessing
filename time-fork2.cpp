////////////////////////////////////////////////////////
//// Sample time checking code2, using macro (get-time).
//// Also showing Unix fork().
//// $>g++ time-fork2.cpp
//// $>./a.out
////////////////////////////////////////////////////////

#include <iostream>
#include <unistd.h>   //for fork()
#include <sys/wait.h> //for wait()
#include <sys/time.h> //for macro GET_TIME(double)
#include <cstdlib>    //for exit(0)
using namespace std;

//macro (in-line expansion) for GET_TIME(double); needs <sys/time.h>
#define GET_TIME(now)\
{ struct timeval t; gettimeofday(&t, NULL);\
  now = t.tv_sec + t.tv_usec/1000000.0; }


int main(int argc, char* argv[])
{
  int i;
  int pid;
  int status;
  double start, stop; //for time checking
  
  GET_TIME(start); //time checking starts
   
  for(i=1; i<=2; i++)
  { pid = fork();
    if (pid==0 && i==1) //child process 1
    { 
      cout<<"Child1---11111"<<endl;
      cout<<"Child1---Hello"<<endl;
      exit(0);
    }
    else if (pid==0 && i==2) //child process 2
    {
      cout<<"Child2---22222"<<endl;
      cout<<"Child2---Hello"<<endl;
      exit(0);
    }
  }//for_i

  cout<<"Hello"<<endl;

  for(i=1; i<=2; i++)
  { pid = wait(&status);
    cout<<"Child process pid="<<pid<<" exited, Status="<<status<<endl;
  }

  GET_TIME(stop); //time checking ends
  cout<<"--run time: "<<stop - start<<" sec."<<endl;

  return 0;
}//main

  
