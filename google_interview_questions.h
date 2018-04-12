#pragma once
#include "structures.h"

/***********************************************MERGE K-SORTED LISTS********************************************************************/
//The List and Inner Index Tracker Class
template <typename T>
class Tracker{
public:
    Tracker(){};
    Tracker(T value, int list_index,int index){
        this->value      = value;
        this->list_index = list_index;
        this->index      = index;
    }

    bool operator>(const T& other){ return this->value > other->value;}

public:
    T value;
    int list_index;
    int index;
};

template <typename T>
std::vector<Tracker<T>> create_container(std::vector<std::vector<T>> lists){
    std::vector<Tracker<T>> container;
    for(int i = 0; i < lists.size(); i++){
        Tracker<T> newTracker(lists[i][0], i, 0);
        container.push_back(newTracker);
    }
    return container;
}

template <typename T>
std::vector<T> merge_lists(std::vector<std::vector<T>> lists){
    std::vector<T> merged;
    std::vector<Tracker<T>> container = create_container(lists);
    std::priority_queue<Tracker<T>, std::vector<T>, std::greater<T>> pq;

    for(unsigned int i = 0; i < lists.size(); i++){
        pq.push(container[i]);
    }

    while(pq.top()){
        Tracker<T> curr = pq.top();//Get Minimum Value From Min-Heap
        pq.pop();//Pop min element
        merged.push_back(curr.value);//Put It to Merged List
        //If popped element's list still contains elements , push next item to Min-Heap
        if ((curr.index + 1) < lists[curr.list_index].size()){
            container[curr.list_index].value = lists[curr.list_index][curr.index + 1];//Update Value
            container[curr.list_index].index++;//Update Inner List Index
            pq.push(container[curr.list_index]);//Push it to Min Heap
        }
    }
    return merged;
}
/***********************************************MERGE K-SORTED LISTS********************************************************************/
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
/*************************************************KNIGHTS_TOUR**************************************************************************/
#ifndef CHESS_EDGE
#define CHESS_EDGE 5
#endif

bool isInMap(int row, int col) {
	return row < CHESS_EDGE && col < CHESS_EDGE && row >= 0 && col >= 0;
}

bool isNotVisited(int row, int col, int matrix[CHESS_EDGE][CHESS_EDGE]) {
	return matrix[row][col] == -1;
}

bool isAvailable(int row, int col, int matrix[CHESS_EDGE][CHESS_EDGE]) {
	return isInMap(row, col) && isNotVisited(row, col, matrix);
}

bool knights_tour(int matrix[CHESS_EDGE][CHESS_EDGE], int row, int col, int step, int row_ch[CHESS_EDGE], int col_ch[CHESS_EDGE]) {
	if (step == (CHESS_EDGE * CHESS_EDGE)) {
		return true;
	}
	for (int i = 0; i < 8; i++) {
		int next_row = row + row_ch[i];
		int next_col = col + col_ch[i];

		if (isAvailable(next_row, next_col, matrix)) {

			matrix[next_row][next_col] = step;
			if (knights_tour(matrix, next_row, next_col, step + 1, row_ch, col_ch) == true) {
				return true;
			}
			else {
				matrix[next_row][next_col] = -1;
			}
		}
	}
	
	
	return false;

}
/*************************************************KNIGHTS_TOUR**************************************************************************/

/****************************************TREATINING_BISHOP*******************************/
int count_threatining_bishop(int chess_board[CHESS_SIZE][CHESS_SIZE]){
	//Scan Board 2 Crossed Diagonally
	int row        = 0;
	int col        = 0;
	int pair_count = 0;
	//Bottom-Left & Top-Right Diagonals
	for(int i = 0; i < CHESS_SIZE; i++){
		int diagonal_count = 0;
		std::pair<int, int> d_pos(row + i, col);
		while(isInRange(d_pos)){
			if(chess_board[d_pos.first][d_pos.second] == 1){
				diagonal_count += 1;
			}
			d_pos.first  -= 1;
			d_pos.second += 1;
		}
		if(diagonal_count >= 1){
			pair_count += (diagonal_count - 1);
		}
	}

	row = CHESS_SIZE - 1;
	col = 0;
	for(int i = 1; i < CHESS_SIZE; i++){
        int diagonal_count = 0;
        std::pair<int, int> d_pos(row, col + i);
        while(isInRange(d_pos)){
	    if(chess_board[d_pos.first][d_pos.second] == 1){
                diagonal_count += 1;
            }
            d_pos.first  -= 1;
            d_pos.second += 1;
        }
        if(diagonal_count >= 1){
            pair_count += (diagonal_count - 1);
        }
    }

	row = 0;
	col = CHESS_SIZE - 1;

	//Bottom-Right & Top-Left Diagonals
	for(int i = 0; i < CHESS_SIZE; i++){
        int diagonal_count = 0;
        std::pair<int, int> d_pos(row, col - i);
        while(isInRange(d_pos)){
            if(chess_board[d_pos.first][d_pos.second] == 1){
                diagonal_count += 1;
            }
            d_pos.first  += 1;
            d_pos.second += 1;
        }
        if(diagonal_count >= 1){
            pair_count += (diagonal_count - 1);
        }
    }

	col = 0;

    for(int i = 1; i < CHESS_SIZE; i++){
        int diagonal_count = 0;
        std::pair<int, int> d_pos(row + i, col);
        while(isInRange(d_pos)){
            if(chess_board[d_pos.first][d_pos.second] == 1){
                diagonal_count += 1;
            }
            d_pos.first  += 1;
            d_pos.second += 1;
        }
        if(diagonal_count >= 1){
            pair_count += (diagonal_count - 1);
        }
    }
	
	return pair_count;
}
/****************************************TREATINING_BISHOP*******************************/
/*************************************************LRU-LFU-CACHE*************************************************************************/
/*
  LRU CACHE
  Double Linked List and Hashing Applied

  Double Linked List : Deque
  Hash Map           : Unordered_Map
  from STL
  O(1) time space add and get
*/

class Cache {
public:
	virtual void set(int key, int value);
	virtual int get(int key);
	virtual void print_content();
};

class LRUCache : public Cache {
public:
	LRUCache(int max_size) {
		this->max_size = max_size;
	}

	~LRUCache() {
		delete this;
	}

	void set(int key, int value);
	int get(int key);
	void print_content();
	

private:
	std::unordered_map<int, int> map;
	std::deque<int> q;
	int size = 0;
	int max_size;
};

void LRUCache::set(int key, int value) {
	//Add directly
	if (this->size < this->max_size) {
		this->map[key] = value;//Add To Hash Map
		this->q.push_front(key);//Add To Front
		this->size++;//Increase Page Size
	}
	//Delete LRU and Add Element
	else if (this->size == this->max_size) {
		//Delete LRU Element
		int lru_element = this->q.back();
		this->q.pop_back(); //Delete From Linked List
		map.erase(lru_element); //Delete From Hast Map

		//Add New Element
		this->map[key] = value;//Add to Hash Map
		this->q.push_front(key);//Add To Front
	}
}

int LRUCache::get(int key) {
	if (map.count(key)) {
		return map[key];
	}
	return 0;
}

void LRUCache::print_content() {
	std::cout << "LRU : ";
	for (int i : this->q) {
		std::cout << this->map[i] << " ";
	}
	std::cout << std::endl;
}

/*
(Not Finished Need to Update)
LFU CACHE
Double Linked List and Hashing Applied

Double Linked List : Deque
Hash Map           : Unordered_Map
from STL
O(1) time space add and get
*/

class LFUCache : public Cache {
public:
	LFUCache(int max_size) {
		this->max_size = max_size;
	}

	~LFUCache() {
		delete this;
	}

	void set(int key, int value);
	int get(int key);
	void print_content();


private:
	std::unordered_map<int, int> map;
	std::deque<int> q;
	int size = 0;
	int max_size;
};

void LFUCache::set(int key, int value) {
	//Add directly
	if (this->size < this->max_size) {
		this->map[key] = value;//Add To Hash Map
		this->q.push_back(key);//Add To Front
		this->size++;//Increase Page Size
	}
	//Delete LFU and Add Element
	else if (this->size == this->max_size) {
		//Delete LFU Element
		int lfu_element = this->q.front();
		this->q.pop_front(); //Delete From Linked List
		map.erase(lfu_element); //Delete From Hast Map

								//Add New Element
		this->map[key] = value;//Add to Hash Map
		this->q.push_front(key);//Add To Front
	}
}

int LFUCache::get(int key) {
	if (map.count(key)) {
		return map[key];
	}
	return 0;
}

void LFUCache::print_content() {
	std::cout << "LFU : ";
	for (int i : this->q) {
		std::cout << this->map[i] << " ";
	}
	std::cout << std::endl;
}

/*************************************************LRU-LFU-CACHE*************************************************************************/

/***********************************************REVERSED_LINKED_LIST********************************************************************/
Node * reverse_it_in_place(Node * head) {
	Node * first  = head;
	Node * second = head->next;

	if (!second) {
		return first;
	}

	Node * third  = head->next->next;

	if (!third) {
		second->next = first;
		first->next = NULL;
		return second;
	}
	else {
		first->next = NULL;
		
		while (third->next) {
			second->next = first;
			first = second;
			second = third;
			third = third->next;
		}
		
		third->next = second;
		second->next = first;
	}

	return third;
}
/***********************************************REVERSED_LINKED_LIST********************************************************************/
