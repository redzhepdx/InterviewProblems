#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Find All Paths Between Two Nodes - NP-Hard
*/

typedef struct STACK{
	
		int *adjWordIndexes;
		int n;
	
}STACK;


typedef struct Connection{
	
	int *words;
	
	int n;
	
}Connection;

void control(int i,int j,int **mtr);

int findIndex(char str[],char **words,int wordNum);

int cmpStrings(char str1[],char str2[]);

void initStack(STACK *stack , int wordNum);

void push(STACK *stack,int adjIndex);

void pop(STACK *stack);

void findAllPaths(int firstStringIndex,int destinationStringIndex,char **words,int **graphMatrix,int wordNum,STACK *stack);

int isContains(STACK *stack,int wantToSearch);


Connection *connections;

int main() {
	
	FILE *fp;
	
	char **words;
	
	int i =0,wordNum,j,difference;
		
	STACK stack;
	
	fp=fopen("word.txt","r+");
	
	fseek(fp,0,SEEK_SET);
	
	
	words=(char**)malloc(2500*sizeof(char*));
	
	for(i=0;i<2500;i++){
		words[i]=(char*)malloc(5*sizeof(char));
	}
	
	i=0;
	
	while(!feof(fp)){
		
		fscanf(fp,"%s",words[i]);
		
		i++;		
		
	}
	
	wordNum=i;
	stack.n=0;

	int **graphMatrix;
	
	graphMatrix = (int**)malloc(wordNum*sizeof(int*));
	
	for(i=0;i<wordNum;i++){
		
		graphMatrix[i]=(int*)malloc(wordNum*sizeof(int));
		
	}
	
	connections = (Connection*)malloc(wordNum * sizeof(Connection));
	
	//GRAF MATRİX
	for(i=0;i<wordNum;i++){	
		int sayi = 0;
		for(j=0;j<wordNum;j++){
			
			graphMatrix[i][j] = cmpStrings(words[i],words[j]);
			if(graphMatrix[i][j] == 1){
				sayi ++;
			}
		}
		connections[i].words = (int*) malloc(sayi * sizeof(int));
		connections[i].n = sayi;
		sayi = 0;
		for(j=0;j<wordNum;j++){
			if(graphMatrix[i][j]){
				connections[i].words[sayi++] = j;
			}
		}
	}

	
	char str[5],str2[5];
	printf("Enter first word : ");
	scanf("%s",str);
	
	printf("Enter second word : ");
	int a = findIndex(str,words,wordNum);
	
	scanf("%s",str2);
	int b = findIndex(str2,words,wordNum);
	
	control(a,b,graphMatrix);
	
	printf("\n");
	
	findAllPaths(a,b,words,graphMatrix,wordNum,&stack);
	
	fclose(fp);
	return 0;
}


	int cmpStrings(char str1[],char str2[]){
		
		int i;
		int difference=0;
		
		for(i=0;i<5;i++){
		
			if(str1[i]!=str2[i]){
			
				difference++;
				
			}
		
		}
		
		if(difference != 1){
			return 0;
		}else{
			return 1;
		}
		
		return 0;	
	}

	int findIndex(char str[],char **words,int wordNum){
		int i,yer;
		for(i=0;i<wordNum;i++){
			if(strncmp(str,words[i],5)==0){
				yer = i;
			}
		}
		return yer;
		
	}

	void control(int i,int j,int **mtr){
		
		if(mtr[i][j]!=0){
			printf("There is a connection between words");
		}
		else{
			printf("There is not connection between words");
		}
		
	}
	
	void push(STACK *stack,int adjIndex){
			
		if(stack->n++)
			stack->adjWordIndexes = (int*)realloc(stack->adjWordIndexes, stack->n * sizeof(int));
		else
			stack->adjWordIndexes = (int*)malloc(sizeof(int));
		
		stack->adjWordIndexes[stack->n - 1] = adjIndex;
	
	}
	
	void pop(STACK *stack){
		
		stack->adjWordIndexes = (int*)realloc(stack->adjWordIndexes, --(stack->n) * sizeof(int));
	}
	
	void findAllPaths(int firstStringIndex,int destinationStringIndex,char **words,int **graphMatrix,int wordNum,STACK *stack){

		int i,debug;
	
		if(firstStringIndex == destinationStringIndex){
			
			for(i=0;i<stack->n;i++){
				
				printf("%s->",words[stack->adjWordIndexes[i]]);			
				
			}
			printf("%s",words[destinationStringIndex]);
			
			printf("\n\n");
			
			fflush(stdin);
			getchar();
		}
		else{
			for(i=0;i<connections[firstStringIndex].n;i++){
				
				if(!isContains(stack,connections[firstStringIndex].words[i]) ){
					
			        push(stack,firstStringIndex);
			
					findAllPaths(connections[firstStringIndex].words[i],destinationStringIndex,words,graphMatrix,wordNum,stack);
					
					pop(stack);	
					
				}
				
			}
			
		}
			
	}
	
	int isContains(STACK *stack,int wantToSearch){
		int i,x;
		for(i=0;i<stack->n;i++){
			if(stack->adjWordIndexes[i] == wantToSearch ){
			  return 1; 	
			}
			
		}
		
		return 0;
	}
	
	void printStack(STACK *stack,char **words){
		int i;
		for(i=0;i<stack->n;i++){
			printf("%s->",words[stack->adjWordIndexes[i]]);
		}
		
	}
