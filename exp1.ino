#include<stdio.h> 
#include<sys/types.h> 
#include<unistd.h> 
#include<sys/wait.h> 
int main() 
{ 
int retval; 
retval=fork(); 
if(retval<0) 
 { 
        printf("child process not created");  } 
if(retval==0) 
 { 
        printf("child process id is %d \n" ,getpid()); 
  } 
else { 
 
2 
 
        wait(NULL); 
        printf("parent process id %d\n",getpid()); 
        sleep(50);  } 
        return 0;   
} 
