#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdlib.h> 
int main() 
{ 
    pid_t pid1, pid2; 
    printf("Parent Process Started\n"); 
    printf("Parent PID: %d\n\n", getpid()); 
    pid1 = fork(); 
 
    if (pid1 < 0) 
    { 
        printf("First fork failed\n"); 
        exit(1); 
    } 
    if (pid1 == 0) 
    { 
        printf("=== First Child ===\n"); 
        printf("Child1 PID  : %d\n", getpid()); 
        printf("Parent PID  : %d\n", getppid()); 
 
4 
 
        for (int i = 0; i < 5; i++) 
        { 
            printf("Child1 Running : %d\n", i); 
            sleep(1); 
        } 
        printf("Child1 Finished\n\n"); 
        exit(0); } 
    pid2 = fork(); 
    if (pid2 < 0) 
    { 
        printf("Second fork failed\n"); 
        exit(1); 
    if (pid2 == 0) 
    { 
        printf("=== Second Child ===\n"); 
        printf("Child2 PID  : %d\n", getpid()); 
        printf("Parent PID  : %d\n", getppid()); 
        for (int i = 0; i < 5; i++) 
        { 
            printf("Child2 Running : %d\n", i); 
            sleep(1); 
        } 
        printf("Child2 Finished\n\n"); 
        exit(0); 
    } 
    printf("=== Parent Process ===\n"); 
    printf("Waiting for children to finish...\n"); 
    wait(NULL); // Wait for one child 
    wait(NULL); // Wait for second child 
    printf("Both children finished\n"); 
    return 0; 
}
