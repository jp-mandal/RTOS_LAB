#include<stdio.h> 
#include<sys/types.h> 
#include<unistd.h> 
int main(){ 
    int retval; 
    retval=fork(); 
    if(retval<0) 
    { 
        printf("fork() has failed\n"); 
    } 
    else if(retval==0) 
    { 
        printf("Child Process\n"); 
        printf("Child Process id is %d\n",getpid()); 
        sleep(20); 
    } 
    else 
    { 
        printf("Parent Process\n"); 
        printf("Parent Process id is %d\n",getpid()); 
        sleep(100); 
    } 
    return 0; 
}
