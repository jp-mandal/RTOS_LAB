#include<stdio.h> 
#include<unistd.h> 
int main() 
{ 
    int pid1,pid2; 
    pid1=fork(); 
    if(pid1==0||(pid2=fork())==0) 
    { 
        printf("Child Process\n"); 
        printf("PID = %d\n",getpid()); 
 
10 
 
    } 
    else 
    { 
        printf("Parent Process\n"); 
        printf("PID = %d\n",getpid()); 
    } 
    return 0; 
}
