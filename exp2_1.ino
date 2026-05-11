#include<stdio.h> 
int main() 
{ 
    int n,i,time=0,remain,quantum; 
    int burst[10],remain_bt[10]; 
    int waiting[10],turnaround[10]; 
    printf("Enter number of processes: "); 
    scanf("%d",&n); 
    remain=n; 
    for(i=0;i<n;i++) 
 
12 
 
    { 
        printf("Enter burst time for processP%d: ",i+1); 
        scanf("%d",&burst[i]); 
        remain_bt[i]=burst[i]; 
    } 
    printf("Enter time quantum:"); 
    scanf("%d",&quantum); 
    while(remain>0) 
    { 
        for(i=0;i<n;i++) 
        { 
            if(remain_bt[i]>0) 
            { 
                if(remain_bt[i]>quantum) 
                { 
                    time+=quantum; 
                    remain_bt[i]-=quantum; 
                } 
                else 
                { 
                    time+=remain_bt[i]; 
                    waiting[i]=time-burst[i]; 
                    turnaround[i]=time; 
                    remain_bt[i]=0; 
                    remain--; 
                } 
            } 
        } 
    } 
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n"); 
    for(i=0;i<n;i++) 
    { 
        printf("P%d\t%d\t\t%d\t\t%d\n",i+1,burst[i],waiting[i],turnaround[i]); 
    } 
    return 0; 
} 
 
