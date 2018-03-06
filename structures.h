#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <cstring>
#include <string.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <stack>
#include <queue>
#include <ctime>

std::vector<std::vector<int>> generateZeroMatrix(int rows, int cols) {
	std::vector<std::vector<int>> matrix(rows);
	for (int i = 0; i < rows; i++) {
		matrix[i].resize(cols);
	}
	return matrix;
}

//Find nth fibonacci number
int fib(int n) {
	if (n == 0) {
		return 0;
	}

	if (n == 1 || n == 2) {
		return 1;
	}

	return fib(n - 1) + fib(n - 2);
}

//Memoiozation Wins!!! O(N) time , O(N) Memory
int memo_fib(int n, std::unordered_map<int, int> &memo) {
	if (n == 0) {
		return 0;
	}
	
	if (n == 1 || n == 2) {
		memo[n] = 1;
		return 1;
	}

	if (memo[n]) {
		return memo[n];
	}

	memo[n] = memo_fib(n - 1, memo) + memo_fib(n - 2, memo);
	
	return memo[n];
}

/*Faster Than Recursion, Constant Memory Usage, O(N) time , O(1) Memory*/
uint64_t iterative_fib(uint64_t n) {
	uint64_t t1 = 1;
	uint64_t t2 = 1;
	
	for (uint64_t i = 2; i <= n; i++) {
		uint64_t temp = t2;
		t2 = t1 + t2;
		t1 = temp;
	}

	return t2;
}
/*********************************END OF FIBONACCI*************************************************/

/*COIN CHANGE PROBLEM SOLUTION*/
long mem_coin_dp(long n, std::vector<long > c, unsigned int start, std::unordered_map<std::string, long> &memo) {
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		return 1;
	}
	if (start >= c.size()) {
		return 0;
	}
	std::string current = std::to_string(n) + ", a, " + std::to_string(start);
	if (memo[current]) {
		return memo[current];
	}
	memo[current] = mem_coin_dp(n - c[start], c, start, memo) + mem_coin_dp(n, c, start + 1, memo);
	return memo[current];
}

/*
@param1 n : long target value
@param2 c : possible value array
*/

long getWays(long n, std::vector < long > c) {
	std::unordered_map<std::string, long> memo;
	return mem_coin_dp(n, c, 0, memo);
}

/*********************************END OF COIN CHANGE*************************************************/

/**********************************************MAX STACK********************************************************************/

class MaxStack {
public:
	MaxStack();
	void push(int value);
	int pop();
	int getMax();
	int peek();

private:
	int max;
	std::stack<int> stack;
};

MaxStack::MaxStack() {}

void MaxStack::push(int value) {
	if (this->stack.empty()) {
		this->stack.push(value);
	}
	else {
		if (value < this->max) {
			this->stack.push(value);
		}
		else {
			this->stack.push(this->max + value);
			this->max = value;
		}
	}
}

int MaxStack::pop() {
	if (this->stack.empty()) {
		return -1;
	}
	int popped = this->stack.top();

	//It means you are picking max element
	if (popped > this->max) {
		int ret = popped - this->max;
		this->stack.pop();
		this->max = ret;
		return ret;
	}

	this->stack.pop();
	return popped;
}

int MaxStack::getMax() {
	return this->max;
}

int MaxStack::peek() {
	return this->stack.top();
}

/****************************************************MAX STACK**************************************************************************/

/**********************************************DOUBLE LINKLIST STACK********************************************************************/
class Node {
public:
	Node(char data) {
		this->data = data;
	}

	Node() {}

public:
	Node* next;
	Node* back;
	char data = 'X';
};

class Stack {
public:
	Node* top;
	Node* head;

	Stack();
	bool isEmpty();
	void push(Node* node);
	Node* pop();
	void merge(Stack* other);
};

Stack::Stack() {
	this->head = new Node();
	this->top = new Node();
}

bool Stack::isEmpty() {
	if (this->head->next == NULL) {
		return true;
	}
	return false;
}

void Stack::push(Node* node) {
	if (this->isEmpty()) {
		this->head->next = node;
		node->back = this->head;
		this->top = node;
	}
	else {
		this->top->next = node;
		node->back = this->top;
		this->top = node;
	}

}

Node* Stack::pop() {
	Node* last_top = this->top;
	Node* new_top = this->top->back;

	new_top->next = NULL;
	this->top = new_top;

	return last_top;
}

void Stack::merge(Stack* other) {
	this->top->next = other->head->next;
	this->top = other->top;
}


/**********************************************DOUBLE LINKLIST STACK********************************************************************/

/**********************************************EXPRESSION_TREE_N_NODE*******************************************************************/
class exp_node {
public:
	exp_node(int _value) {
		this->value = _value;
		this->expression = '#';
	}

	exp_node(char _expression) {
		this->expression = _expression;
	}

	bool isOperation() {
		return this->expression == '#';
	}

	~exp_node() {
		delete this;
	}

public:
	exp_node * left;
	exp_node * right;
	int value;
	char expression;
};

class ExpressionTree {
public:
	ExpressionTree(exp_node * root) {
		this->root = root;
	}

	~ExpressionTree() {
		delete this;
	}

	int getResultOfTree(exp_node *node);
	int computeSubTree(exp_node *node, int left_value, int right_value);

public:
	exp_node * root;
};

/**********************************************EXPRESSION_TREE_N_NODE*******************************************************************/

/***************************************************COLOR_NODE**************************************************************************/
class ColorNode {
public:
	ColorNode(std::string name){
		this->name = name;
		this->color = 0;
		this->isVisited = false;
		this->isInQueue = false;
	}

	~ColorNode(){
		delete this;
	}

	void setCurrentColorToNeighbours();

public:
	int color;
	bool isVisited;
	bool isInQueue;
	std::string name;
	std::vector<ColorNode*> neighbours;
	std::unordered_map<int, bool> not_avaiable_colors;
};

void ColorNode::setCurrentColorToNeighbours() {
	for (auto& node : this->neighbours) {
		node->not_avaiable_colors[this->color] = true;
	}
}


/***************************************************COLOR_NODE**************************************************************************/
