#include<stdio.h> 
int main() 
{ 
    int n,i,j; 
    int burst[10],priority[10],process[10]; 
    int waiting[10],turnaround[10]; 
    int temp; 
    printf("Enter number of processes: "); 
    scanf("%d",&n); 
    for(i=0;i<n;i++) 
    { 
        process[i]=i+1; 
        printf("Enter burst time for P%d: ",i+1); 
        scanf("%d",&burst[i]); 
        printf("Enter priority for P%d: ",i+1); 
        scanf("%d",&priority[i]); 
    } 
    for(i=0;i<n;i++) 
    { 
        for(j=i+1;j<n;j++) 
        { 
            if(priority[i]>priority[j]) 
            { 
                temp=priority[i]; 
                priority[i]=priority[j]; 
                priority[j]=temp; 
                temp=burst[i]; 
                burst[i]=burst[j]; 
                burst[j]=temp; 
                temp=process[i]; 
                process[i]=process[j]; 
                process[j]=temp; 
            } 
        } 
    } 
 
15 
 
    waiting[0]=0; 
    for(i=1;i<n;i++) 
    { 
        waiting[i]=waiting[i-1]+burst[i-1]; 
    } 
    for(i=0;i<n;i++) 
    { 
        turnaround[i]=waiting[i]+burst[i]; 
    } 
    printf("\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n"); 
    for(i=0;i<n;i++) 
    { 
        
printf("P%d\t%d\t%d\t\t%d\t%d\n",process[i],burst[i],priority[i],waiting[i],turnaround[i]); 
    } 
    return 0; 
} 
