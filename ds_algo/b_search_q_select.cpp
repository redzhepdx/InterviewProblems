/*
B-Search for shifted array and QuickSelect Algorithm C++(Non Recursive)
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

#define internal static
#define swap(x,y) {int temp = x ; x = y ; y = temp;}
#define ELEM_NUM 5
#define MAX 10
#define KEY 1
#define INDEX 2

using namespace std;

internal int Partition(int *list, int left, int right , int pivotIndex) {

	int pivotValue = list[pivotIndex];
	
	swap(list[pivotIndex], list[right]);

	int storeIndex = left;

	for (register int index = left; index <= right; index++) {

		if (list[index] < pivotValue) {
		
			swap(list[storeIndex], list[index]);
			
			storeIndex++;
			
		}

	}

	swap(list[right], list[storeIndex]);

	return storeIndex;
}

internal int QuickSelect(int *list) {

	int pivotIndex;
	
	int left = 0, right = ELEM_NUM - 1;


	while (1) {

		if (left == right)
			return list[left];

		pivotIndex = floor(rand() % (right - left + 1)) + left;
		
		pivotIndex = Partition(list, left, right, pivotIndex);

		if (pivotIndex == INDEX) {

			return list[INDEX];
	
		}
		else if (INDEX < pivotIndex) {
			right = pivotIndex - 1;
		}
		else {
			left = pivotIndex + 1;
		}
	}
}

internal int BinarySearchShiftedArray(int *list) {
	int mid;
	int left = 0, right = ELEM_NUM - 1;

	while (1) {
		mid = (left + right) / 2;

		if (left > right) {
			return -1;
		}

		if (list[mid] == KEY) {
			return mid;
		}

		(list[left] <= list[mid]) ? ((list[left] <= KEY && list[mid] >= KEY) ? right = mid - 1 : left = mid + 1) :
									((list[mid] <= KEY && list[right] >= KEY) ? left = mid + 1 : right = mid - 1);
	}

}

internal void printArray(int *a) {
	for (register int i = 0; i < ELEM_NUM; i++) {
		cout << a[i] << "\t";
	}
	cout << endl;
}

void Search(int * list , int(*SearchType)(int *)) {

	int n = SearchType(list);

	if (SearchType == QuickSelect) {
		cout << INDEX << ". smallest element : " << n << endl;
	}
	else {
		cout << "Key Present in : " << n << endl;
	}
}


void ShiftArray(int *list, int shiftCount) {
	for (register int i = 0; i < shiftCount; i++)
	{
		int temp = list[0];
		
		for (register int j = 0; j < (ELEM_NUM - 1); j++)
		{
			list[j] = list[j + 1];
		}

		list[ELEM_NUM - 1] = temp;
	}
}

int main() {
	srand(time(NULL));

	int *array = (int*)malloc(ELEM_NUM*sizeof(int));

	for (register int i = 0; i < ELEM_NUM; i++) {
		
		array[i] = i;
	}

	printArray(array);
	ShiftArray(array, 3);
	printArray(array);

	Search(array, &BinarySearchShiftedArray);

	getchar();
}
