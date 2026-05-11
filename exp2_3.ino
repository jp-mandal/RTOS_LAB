#include<stdio.h> 
int main() 
{ 
    int n,i,j; 
    int exec[10],period[10],task[10]; 
    int temp; 
    printf("Enter number of tasks: "); 
    scanf("%d",&n); 
    for(i=0;i<n;i++) 
    { 
        task[i]=i+1; 
        printf("Enter execution time for Task %d: ",i+1); 
        scanf("%d",&exec[i]); 
        printf("Enter period for Task %d: ",i+1); 
        scanf("%d",&period[i]); 
    } 
    for(i=0;i<n;i++) 
    { 
        for(j=i+1;j<n;j++) 
        { 
            if(period[i]>period[j]) 
            { 
                temp=period[i]; 
 
17 
 
                period[i]=period[j]; 
                period[j]=temp; 
                temp=exec[i]; 
                exec[i]=exec[j]; 
                exec[j]=temp; 
                temp=task[i]; 
                task[i]=task[j]; 
                task[j]=temp; 
            } 
        } 
    } 
    printf("\nTask\tExecution Time\tPeriod\tPriority\n"); 
    for(i=0;i<n;i++) 
    { 
        printf("T%d\t%d\t\t%d\t%d\n",task[i],exec[i],period[i],i+1); 
    } 
    return 0; 
} 
