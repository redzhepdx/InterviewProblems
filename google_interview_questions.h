#pragma once
#include "structures.h"


/***************************************************R-G-B SORTING***********************************************************************/
std::vector<char> organizeArray(std::vector<char> rgbList) {
	std::vector<char> organizedArray;
	Stack* stack_r = new Stack();
	Stack* stack_g = new Stack();
	Stack* stack_b = new Stack();

	for (unsigned int i = 0; i < rgbList.size(); i++) {
		switch (rgbList[i])
		{
		case 'R':
			stack_r->push(new Node('R'));
			break;
		case 'G':
			stack_g->push(new Node('G'));
			break;
		case 'B':
			stack_b->push(new Node('B'));
			break;
		default:
			break;
		}
	}

	stack_g->merge(stack_b);
	stack_r->merge(stack_g);

	for (Node * n = stack_r->head->next; n->next != NULL; n = n->next) {
		//std::cout << n->data << " ";
		organizedArray.push_back(n->data);
	}
	std::cout << "Done " << std::endl;
	getchar();
	return organizedArray;
}

int getNonRepeatingElem(int elem_num , int n) {

	std::unordered_map<int, int> num_repeating_count;

	for (int i = 0; i < elem_num; i++) {
		int number;
		std::cin >> number;

		if (!num_repeating_count.count(number)) {
			num_repeating_count[number] = 1;
		}
		else if (num_repeating_count[number] < n ) {
			num_repeating_count[number]++;
		}
		
		if(num_repeating_count[number] == n) {
			num_repeating_count.erase(number);
		}
	}

	std::cout << "non repeating : "<<  num_repeating_count.begin()->first << std::endl;

	return num_repeating_count.begin()->first;
}
/***************************************************R-G-B SORTING***********************************************************************/

/**********************************************INVERSE ORDER PROBLEM********************************************************************/
int merge(std::vector<int>& list, std::vector<int>& temp, int left, int mid, int right) {
	int start_l = left; //Start of First Part (0)
	int start_r = mid; // Start of Second Part (mid + 1)
	int start_k = left; // Result Array Starts from Left (0)

	int inversion_count = 0;
	//Merge Left and Right Part
	while (start_l <= (mid - 1) && start_r <= right) {
		if (list[start_l] <= list[start_r]) {
			temp[start_k++] = list[start_l++];
		}
		else {
			temp[start_k++] = list[start_r++];
			//If list[left] is bigger than list[j] , and two parts are sorted,
			//it means all left to mid all element bigger than list[j],
			//inversion = mid - left
			inversion_count += mid - start_l;
		}
	}

	//CLEAR REMAININGS OF LEFT OR RIGHT PARTS
	while (start_l <= (mid - 1)) {
		temp[start_k++] = list[start_l++];
	}

	while (start_r <= right) {
		temp[start_k++] = list[start_r++];
	}

	//Update main array with merged sorted temp array
	for (int i = left; i <= right; i++) {
		list[i] = temp[i];
	}

	return inversion_count;
}

int merge_sort_with_inversions(std::vector<int>& list, std::vector<int>& temp, int left, int right) {
	
	int mid, inversion_count = 0;

	if (left < right) {
		mid = (left + right) / 2;
		//Recur left - mid part
		inversion_count = merge_sort_with_inversions(list, temp, left, mid);
		//Recur mid + 1 - right part
		inversion_count += merge_sort_with_inversions(list, temp, mid + 1, right);
		//Merge Parts
		inversion_count += merge(list, temp, left, mid + 1, right);
	}

	return inversion_count;
}


int count_out_of_orders(std::vector<int>& list) {
	std::vector<int> temp(list.size());
	int counter = merge_sort_with_inversions(list, temp, 0, list.size() - 1);
	return counter;
}

/**********************************************INVERSE ORDER PROBLEM********************************************************************/


/**********************************************DYNAMIC_SUDOKU_SOLVER********************************************************************/
#ifndef SUDOKU_SIZE
#define SUDOKU_SIZE 9
#endif

#ifndef EMPTY_CELL
#define EMPTY_CELL 0
#endif

bool findNextEmptyCell(int matrix[SUDOKU_SIZE][SUDOKU_SIZE], int& _row, int& _col) {
	bool found = false;
	for (int row = 0; row < SUDOKU_SIZE; row++) {
		for (int col = 0; col < SUDOKU_SIZE; col++) {
			if (matrix[row][col] == EMPTY_CELL) {
				_row = row;
				_col = col;
				return true;
			}
		}
	}
	return false;
}

bool isUsedInCol(int matrix[SUDOKU_SIZE][SUDOKU_SIZE], int _col,  int value) {
	for (int row = 0; row < SUDOKU_SIZE; row++) {
		if (matrix[row][_col] == value) {
			return true;
		}
	}
	return false;
}

bool isUsedInRow(int matrix[SUDOKU_SIZE][SUDOKU_SIZE], int _row, int value) {
	for (int col = 0; col < SUDOKU_SIZE; col++) {
		if (matrix[_row][col] == value) {
			return true;
		}
	}
	return false;
}

bool isUsedInCell(int matrix[SUDOKU_SIZE][SUDOKU_SIZE], int _row, int _col, int value) {
	for (int row = 0; row < std::sqrt(SUDOKU_SIZE); row++) {
		for (int col = 0; col < std::sqrt(SUDOKU_SIZE); col++) {
			//_row - (_row % std::sqrt(SUDOKU_SIZE)) and _col - (_col % std::sqrt(SUDOKU_SIZE)): cell starting position computation
			//Example : if position is (5,5), this position's cell starting position = (5 - 5 % 3, 5 - 5 % 3) = (3 , 3) 
			int r_row = (_row - (_row % (int)std::sqrt(SUDOKU_SIZE))) + row;
			int c_col = (_col - (_col % (int)std::sqrt(SUDOKU_SIZE))) + col;
			if (matrix[r_row][c_col] == value) {
				return true;
			}
		}
	}
	return false;
}

bool isSafe(int matrix[SUDOKU_SIZE][SUDOKU_SIZE], int _row, int _col, int value) {
	if (!isUsedInRow(matrix, _row, value) && !isUsedInCol(matrix, _col, value) && !isUsedInCell(matrix, _row, _col, value)) {
		return true;
	}
	return false;
}

bool SolveSudoku(int (&matrix)[SUDOKU_SIZE][SUDOKU_SIZE]) {

	int row, col;
	//If there isn't empty cell it means sudoku solved
	if (!findNextEmptyCell(matrix, row, col)) {
		return true;
	}



	//Find Available Number for Cell and Recurse for next Empty cell
	for (int value = 1; value <= SUDOKU_SIZE; value++) {
		//If Value is ok for this position
		if (isSafe(matrix, row, col, value)) {
			matrix[row][col] = value;
			//Look for next empty
			if (SolveSudoku(matrix)) {
				return true;
			}
			//If this value isn't good for next values, make it empty and look other possible values(Backtracking Part)
			matrix[row][col] = EMPTY_CELL;
		}
	}

	return false;
}

void showMatrix(int matrix[SUDOKU_SIZE][SUDOKU_SIZE]) {
	for (int row = 0; row < SUDOKU_SIZE; row++) {
		for (int col = 0; col < SUDOKU_SIZE; col++) {
			std::cout << matrix[row][col] << " ";
		}
		std::cout << std::endl;
	}
}


/**********************************************DYNAMIC_SUDOKU_SOLVER********************************************************************/

/*************************************************GRAPH_COLORING************************************************************************/
int findMaxColorCount(ColorNode *& root) {

	std::queue<ColorNode*> queue;
	queue.push(root);
	int max_color = 1;

	while (queue.size() != 0) {

		ColorNode * node					   = queue.front();
		node->isVisited						   = true; //Mark it as visited
		node->isInQueue						   = false; //Clear Queue Check
		node->color							   = 1;
		queue.pop();

		//If current color exists, increment color
		while (node->not_avaiable_colors.count(node->color)) {
			node->color++;
		}

		node->not_avaiable_colors[node->color] = true;

		for (auto& n_node : node->neighbours) {
			n_node->not_avaiable_colors[node->color] = true;
			if (!n_node->isVisited && !n_node->isInQueue) {
				queue.push(n_node);
				n_node->isInQueue = true;
			}
		}
		
		if (node->color > max_color) {
			max_color = node->color;
		}
	}

	return max_color;
}
/*************************************************GRAPH_COLORING************************************************************************/
/*************************************************EFFICIENT_POW*************************************************************************/
int efficient_pow(int x, int y, std::unordered_map<std::string, int> &memo) {
	int sol = 1;
	std::string memo_state = std::to_string(x) + "," + std::to_string(y);
	if (!memo.count(memo_state)) {
		if (y == 0) {
			sol = 1;
		}
		if (y == 1) {
			sol = x;
		}
		else if (y == 2) {
			sol = x * x;
		}
		else {
			sol = efficient_pow(x, y - (y / 2), memo) * efficient_pow(x, y / 2, memo);
		}
	}
	else {
		return memo[memo_state];
	}
	memo[memo_state] = sol;
	return memo[memo_state];
}

uint64_t efficient_pow_normal(uint64_t x, uint64_t y) {
	if (y == 0) {
		return 1;
	}
	if (y == 1) {
		return x;
	}
	if (y == 2) {
		return x*x;
	}
	return x * efficient_pow_normal(x, y - 1);
}

uint64_t efficient_pow_iterative(uint64_t base, uint64_t power) {
	uint64_t res = 1;
	
	while (power > 0) {
		if (power % 2 == 1) {
			res *= base;
		}
		base *= base;
		power /= 2;
	}
	return res;
}

uint64_t normal_pow(uint64_t x, uint64_t y) {
	uint64_t sol = 1;
	for (uint64_t i = 0; i < y; i++) {
		sol *= x;
	}
	return sol;
}
/*************************************************EFFICIENT_POW*************************************************************************/