/*
 Implementation of round robin process scheduling algorithm
*/
#include<stdio.h>
#include<stdlib.h>
#define ELEM_NUM 100

//Proses struct
typedef struct Process
{	
	int ProcessId;
	int CpuBurstTime;
	int ArrivalTime;
}Process;

//Scheduler Struct
typedef struct Scheduler
{
	int ProcessId;
	int startTime;
	int stopTime;
}Scheduler;

//Queue struct
typedef struct Queue
{
	Process *processes;
	int count;
	int front;
	int rear;
}Queue;

void initQueue(Queue *q);
void enqueue(Queue *q , Process p);
Process dequeue(Queue *q);
int isEmpty(Queue *q);
float CalculateTotalWaitingTime(Scheduler *scheduler , int schedulerCount , int processNum);
float CalculateFirstWaitingTime(Scheduler *scheduler , int processCount , Process *processArray );

int main()
{
	int processNum , timeQuantum ;
	int i , j;
	int schedulerNum = 0;
	FILE *fp;

	Queue *queue;
	
	Scheduler *scheduler;
	
	Process *processArray;
	
	printf("Enter the process num : ");
	scanf("%d",&processNum);
	
	printf("Time Quantum  : ");
	scanf("%d",&timeQuantum);
	
	queue = (Queue*)malloc(sizeof(Queue));
	
	scheduler = (Scheduler*)malloc(ELEM_NUM*sizeof(Scheduler));
	
	processArray = (Process*)malloc(processNum*sizeof(Process));
	
	initQueue(queue);
	
	fp = fopen("anyText.txt","w");
	if(fp == NULL){
		return -1;
	}
	
	//Adding processes to queue in the beginning
	for(i = 0 ; i < processNum ; i++)
	{
		printf("%d.Process CpuBurstTime : ",i+1);
		scanf("%d",&processArray[i].CpuBurstTime);
		processArray[i].ProcessId = i+1;
		processArray[i].ArrivalTime = i*timeQuantum;
		enqueue(queue,processArray[i]);
	} 
	
	while(queue->count > 0){
		
		Process temp_process = dequeue(queue);

		if(schedulerNum>0){
			scheduler[schedulerNum].startTime = scheduler[schedulerNum-1].stopTime;
		}
		else{
			scheduler[schedulerNum].startTime = 0;
		}
		
		scheduler[schedulerNum].ProcessId = temp_process.ProcessId;
		
		if(temp_process.CpuBurstTime > timeQuantum){
			
			scheduler[schedulerNum].stopTime = scheduler[schedulerNum].startTime +timeQuantum;
			
			temp_process.CpuBurstTime -= timeQuantum;
				
			enqueue(queue,temp_process);
		}
		else{

			scheduler[schedulerNum].stopTime = scheduler[schedulerNum].startTime + temp_process.CpuBurstTime;
			temp_process.CpuBurstTime = 0;
		}
	
		schedulerNum++;		
		
	}
	
	fprintf(fp,"%s","Process ID\t   StartTime\t   EndTime\n\t");
	for(i = 0 ; i< schedulerNum;i++){
		fprintf(fp,"%d\t\t%d\t\t%d\n\t",scheduler[i].ProcessId,scheduler[i].startTime,scheduler[i].stopTime);
	}
	fprintf(fp,"%s","\n");
	float totalWaitingTime = CalculateTotalWaitingTime(scheduler , schedulerNum , processNum);
	float firstWaitingTime = CalculateFirstWaitingTime(scheduler , processNum , processArray);
	
	float averageWaitingTime = (totalWaitingTime + firstWaitingTime ) / processNum;
	
	fprintf(fp,"%s\t%f","Average Waiting Time : ",averageWaitingTime);
	fclose(fp);
	return 0;
}

//Stores every process's the waiting times for given arrival time
float CalculateFirstWaitingTime(Scheduler *scheduler , int processCount , Process *processArray ){
	int i;
	float firstWaitingTotalTime=0;
	
	for(i = 0 ;i<processCount ; i++){
		firstWaitingTotalTime += scheduler[i].startTime - processArray[i].ArrivalTime; 
	}
	
	return firstWaitingTotalTime;
}

//Calculates total waiting time with process scheduling order
float CalculateTotalWaitingTime(Scheduler *scheduler , int schedulerCount , int processNum){
	
	int i,j,k;
	float totalWaitingTime = 0;
	float averageWaitingTime;
	
	for(i = 0 ; i<processNum ;i++)
	{
		k=i;
		while(k < schedulerCount){
			
			for(j = k+1 ; j < schedulerCount+1;j++){
			
				if(scheduler[k].ProcessId == scheduler[j].ProcessId){
					totalWaitingTime += (scheduler[j].startTime - scheduler[k].stopTime);
					k=j;
				}else if(j==schedulerCount){
					k+=schedulerCount;
				}		
			}
		}
	}
	
	return totalWaitingTime;	
}


void initQueue(Queue *q){
	q->count = 0;
	q->front = 0;
	q->rear = 0;
	q->processes = (Process*)malloc(ELEM_NUM*sizeof(Process));
}

void enqueue(Queue *q , Process p){
	
	q->processes[q->rear] = p;
	q->rear = (++q->rear) % ELEM_NUM;
	q->count++;	
	
}

Process dequeue(Queue *q){
	
	Process item;
	
	if(!isEmpty(q)){
		item = q->processes[q->front];
		q->front = (++q->front) % ELEM_NUM;
		q->count--;	
	}
	return item;
}

int isEmpty(Queue *q){

	return q->count == 0;
}
