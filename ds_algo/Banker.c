/*
  Implementation of Banker deadlock prevention algorithm
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum {
SAFE,
UNSAFE
}State;

int main() {
	
	State state ;//process's deadlock state
	int process_num , resources_num , exec;//Process number , resources number and executable for current state
	int** max ;
	int** allocated ;
	int** need;
	int* max_res ;
	int* available ;
	int* running ;
	int* totalAllocation;
	int i , j , k , runningCount = 0;
	
	printf("Process Number : ");
	scanf("%d",&process_num);
	
	running = (int*)malloc(process_num * sizeof(int));
	
	for(i = 0 ; i < process_num ; i++){

		running[i] = 1;
		runningCount++;

	}
	
	printf("Resources number : ");
	scanf("%d" , &resources_num);
	
	max_res = (int*)malloc(resources_num * sizeof(int));
	available = (int*)malloc(resources_num * sizeof(int));
	totalAllocation = (int*)malloc(resources_num * sizeof(int));
	
	printf("Maximum resources number : ");
	
	for(i = 0 ; i < resources_num ; i++){
		totalAllocation[i] = 0;
		scanf("%d",&max_res[i]);

	}
	
	allocated = (int**)malloc(process_num * sizeof(int*));
	max = (int**)malloc(process_num * sizeof(int*));
	need = (int**)malloc(process_num * sizeof(int*));

	for(i = 0 ; i < process_num ; i++){

		allocated[i] = (int*)malloc(resources_num * sizeof(int));
		max[i] = (int*)malloc(resources_num * sizeof(int));
		need[i] = (int*)malloc(resources_num * sizeof(int));
		
	}
	
	printf("Required Resources\n");

	for(i = 0 ; i < process_num ; i++){
		
		for(j = 0 ; j < resources_num ; j++ ){
		
			printf("Allocation[%d][%d] : ",i,j);
			scanf("%d",&allocated[i][j]);
		
		}

	}
	
	printf("Total Required Resources \n");
	
	for(i = 0 ; i < process_num ; i++){
		
		for(j = 0 ; j < resources_num ; j++ ){
		
			printf("Maximum[%d][%d] : ",i,j);
			scanf("%d",&max[i][j]);
		
		}

	}
	
	/*Calculate amount for every process
	SOURCE - GIVEN AS AN INSTANT = NEEDED
	*/
	for(i = 0 ; i < process_num ; i++){
		
		for(j = 0 ; j < resources_num ; j++ ){
		
			need[i][j] = max[i][j] - allocated[i][j];
			totalAllocation[j] += allocated[i][j];
			
		}

	}
	
	//CALCULATİNG AVAILABLE RESOURCES AMOUNT
	//TOTAL - (NEEDED FROM EVERY RESOURCES) = AVAILABLE AMOUNT
	for(i = 0 ; i < resources_num ; i++){
		available[i] = max_res[i] - totalAllocation[i];
	}
	
	
	/*In the beginning every process executable
	If deadlock occurs , program finish itself
	if avaible amount bigger than needed amount process takes these resources
	If available amount is not enough for any process , deadlock occurs
	*/
	while(runningCount != 0){
		
		state = UNSAFE;
		
		for(i = 0 ; i < process_num ; i++){
		
			if(running[i]){
			
				exec = 1;
			
				for(j = 0 ; j < resources_num ; j++){
		
					if(available[j] < need[i][j]){
		
						exec = 0;
						break;	
		
					}
					
				}
				if(exec){
		
					printf("%d.PROCESS WORKING \n",i+1);
					
					running[i] = 0;
					
					runningCount--;
					
					state = SAFE;
					
					for(k = 0 ; k < resources_num ; k++){
						
						available[k]+=allocated[i][k];
						
					}
					break;
				}
			}	
		}	
		if(state == UNSAFE){
			
			printf("\nNOT SAFE!!\n");
			//break;
			
		}else{
			
			printf("\nSAFE\n");
			printf("\nAVAIBLE RESOURCES AMOUNT :  ");
			
			for(i = 0 ; i < resources_num ; i++){
				
				printf("%d  ",available[i]);
			
			}
			printf("\n\n");
		}
	}
	
	free(max);
	free(allocated);
	free(available);
	free(max_res);
	free(need);
	free(running);
	free(totalAllocation);

	return 0;
}
