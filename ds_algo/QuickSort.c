/*
 Performance Analysis of Quick Sort Algorithm on Three Different Initializations
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000
#define SHORT_SIZE 16


//PIVOT SELECTION STPYLE
enum pivotAddressStyle{
	FirstAddress,RandomAddress,MedianAddress	
};

//ARRAYS CAN CONTAIN SIXTEEN OR MORE ELEMENTS
enum arrayElementNum{SIXTEEN,MORE};

enum arrayElementNum elemNum;
enum pivotAddressStyle pivotA;

void QuickSort(int *A,int left,int right);//QUICK-SORT
int Partition(int *A,int left , int right);//PARTITION 
void swap(int *a,int *b);//SWAPPING A -> B ,B->A
int FindMedian(int *A,int a,int b,int c);//FINDS MEDIAN FOR GIVEN ARRAY(BETWEEN FIRST LAST AND MIDDLE ELEMENTS)
int selectPivot(int *A,int left,int right);//PIVOT SELECTION

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	
	clock_t begin ,end;//TIME
	double time_spent;
	int i,selection,selectionRS,arrayType;
	
	int *array;
	int size;
	
	begin = clock();
	int x = 1000000;

	printf("1 - 16 Elements\n");
	printf("2 - 10 Thousands Elements\n");
	printf("3 - 100 Thousands Elements\n");
	printf("4 - 1 Million Elements\n");
	printf("Choice : ");
	scanf("%d",&arrayType);	
	
	switch(arrayType)
	{
		case 1:
			elemNum = SIXTEEN;
			size = 16;
			array = (int*)malloc(size*sizeof(int));
			break;
			
		case 2:
			elemNum = MORE;
			size=SIZE;
			array = (int*)malloc(size*sizeof(int));
			break;
			
		case 3:
			elemNum = MORE;
			size=10*SIZE;
			array = (int*)malloc(size*sizeof(int));
			break;
			
		case 4:
			elemNum = MORE;
			size=100*SIZE;
			array = (int*)malloc(size*sizeof(int));
			break;		
		default:
			break;
	}
	
	printf("1-Sorted Array \n");
	printf("2-Random Array \n");
	printf("Choice : ");
	scanf("%d",&selectionRS);
	
	switch(selectionRS){
		
		case 1:
			
			for(i = 0;i < size ; i++){
				array[i]=i+1;
			}
			break;
			
		case 2:
			for(i = 0;i < size ; i++){
				array[i]=rand()%size+1;
			}
			break;

		default :
			break;	
	}
	
	if(elemNum == SHORT_SIZE ){
		
		for(i = 0;i < size ; i++){
			printf("%d\t",array[i]);	
		}
		
	}

	printf("\n1-Pivot is the first element of array \n");
	printf("2-Pivot is random element \n");
	printf("3-Pivot is median element \n");
	printf("Seciminizi giriniz : ");
	
	scanf("%d",&selection);
	
	switch(selection){
		
		case 1:
			pivotA = FirstAddress;
			break;
		
		case 2:
			pivotA = RandomAddress;
			break;
			
		case 3:
			pivotA = MedianAddress;
			break;
		
		default:
			break;
	}
	
	//SORT PROCESS
	QuickSort(array,0,size-1);
	
	if(elemNum == 16){
		
		for(i = 0;i < size ; i++){
			printf("%d\t",array[i]);	
		}
		
	}
	
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("\ntime : %f",time_spent);
	return 0;
}

void QuickSort(int *A,int left,int right){
	
	int address_of_pivot;
	int i;
	
	//IF ELEMENT NUMBER SELECTED SIXTEEN THEN SHOW STEP BY STEP WHOLE PROCESS
	if(elemNum == SIXTEEN){
		for(i = 0;i < 16 ; i++){
			printf("%d\t",A[i]);	
		}
		printf("\n");
	}
			
	
	if(left<right){
		
		address_of_pivot = Partition(A,left,right);
		
		QuickSort(A,left,address_of_pivot-1);
		QuickSort(A,address_of_pivot+1,right);
		
		
	}
	
}

int Partition(int *A,int left , int right){
	
	int i, j,pivot;
	pivot = selectPivot(A,left,right);
	
	i=left; j = right+1;
	
	do{
		do{
			
			++i;
		
		}while((i<j) && A[i]<=pivot);
		
		do{
		
			j--;
		
		}while(A[j]>pivot);
		
		swap(&A[i],&A[j]);
	
	}while(i<j);
	
	swap(&A[i],&A[j]);
	swap(&A[j],&A[left]);
	
	return j;
}

void swap(int *a,int *b){
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

int selectPivot(int *A,int left,int right){
	int selection,i;
	int pivot,random,medium;
		
	if(pivotA == FirstAddress){
		
		pivot = A[left];
		return pivot;
	
	}
	else if(pivotA == RandomAddress){
		
		random = rand()%(right-left+1)+left;
		swap(&A[left],&A[random]);
		pivot = A[left];
	
		return pivot;
		
	}
	else if(pivotA == MedianAddress){
		medium = FindMedian(A,left,(right+left)/2,right);
		if(left != medium)
			swap(&A[left],&A[medium]);	
		pivot = A[left];

		return pivot;			
	}
	
}
int FindMedian(int *A,int a,int b,int c){
	
	if((A[a]>A[b] && A[a]<A[c] ) || (A[a]>A[c] && A[a]<A[b]))
		return a;
	else if((A[b]>A[a] && A[b]<A[c]) || (A[b]>A[c] && A[b]<A[a])) 
		return b;
	else if((A[c]>A[a] && A[c]<A[b]) || (A[c]>A[b] && A[c]<A[a]))
		return c;
	
}
