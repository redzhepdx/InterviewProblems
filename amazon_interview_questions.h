#pragma once
#include "structures.h"
/*************************************************AMAZON QUESTIONS**********************************************************************/

/**************************************FIND_MAXIMUM_SUM_OF_ANY_CONTIGOUS_SUBARRAY*******************************************************/
int find_max_subarray(std::vector<int> list) {

	int global_max	= 0;
	int local_max	= 0;

	for (unsigned int i = 0; i < list.size(); i++) {
		local_max	= std::max(list[i], list[i] + local_max);
		global_max	= (global_max < local_max) ? local_max : global_max;
	}

	return global_max;
}

/**************************************FIND_MAXIMUM_SUM_OF_ANY_CONTIGOUS_SUBARRAY*******************************************************/

/*************************************************EXPRESSION_TREE_RESULT****************************************************************/


int ExpressionTree::getResultOfTree(exp_node * node) {
	int result = 0;
	int left_val, right_val;

	if (node->isOperation()) {
		return node->value;
	}
	else {
		left_val  = this->getResultOfTree(node->left);
		right_val = this->getResultOfTree(node->right);
	}

	return this->computeSubTree(node, left_val, right_val);
}

int ExpressionTree::computeSubTree(exp_node *node, int left_value, int right_value) {

	switch (node->expression)
	{
	
	case '*':
		return left_value * right_value;
		break;
	
	case '+':
		return left_value + right_value;
		break;
	
	case '-':
		return left_value - right_value;
		break;
	
	case '/':
		return left_value / right_value;
		break;

	default:
		break;
	}
	return 0;
}
/*************************************************EXPRESSION_TREE_RESULT****************************************************************/

/************************************************SPIRAL_TRAVERSING_MATRIX***************************************************************/
#ifndef SPIRAL_MATRIX_COL
#define SPIRAL_MATRIX_COL 8
#endif

#ifndef SPIRAL_MATRIX_ROW
#define SPIRAL_MATRIX_ROW 7
#endif

void spiral_traverse_matrix(int matrix[SPIRAL_MATRIX_ROW][SPIRAL_MATRIX_COL]) {
	int step = 0;
	int curr_row = 0;
	int curr_col = 0;
	//matrix[curr_row][curr_col] = 0;
	while (step < (SPIRAL_MATRIX_COL * SPIRAL_MATRIX_ROW - 1)) {
		//Go Left As Much As You Can
		while (curr_col < SPIRAL_MATRIX_COL - 1 && matrix[curr_row][curr_col] != 0) {
			std::cout << matrix[curr_row][curr_col] << " ";
			matrix[curr_row][curr_col] = 0;
			curr_col++;
			step++;
			if (matrix[curr_row][curr_col] == 0) {
				curr_col--;
				curr_row++;
				break;
			}
		}
		//Go Down As Much As You Can
		while (curr_row < SPIRAL_MATRIX_ROW - 1 && matrix[curr_row][curr_col] != 0) {
			std::cout << matrix[curr_row][curr_col] << " ";
			matrix[curr_row][curr_col] = 0;
			curr_row++;
			step++;
			if (matrix[curr_row][curr_col] == 0) {
				curr_row--;
				curr_col--;
				break;
			}
		}


		//Go Righ As Much As You Can
		while (curr_col > 0 && matrix[curr_row][curr_col] != 0) {
			std::cout << matrix[curr_row][curr_col] << " ";
			matrix[curr_row][curr_col] = 0;
			curr_col--;
			step++;
			if (matrix[curr_row][curr_col] == 0) {
				curr_col++;
				curr_row--;
				break;
			}
		}
		//Go Top As Much As You Can
		while (curr_row > 0 && matrix[curr_row][curr_col] != 0) {
			std::cout << matrix[curr_row][curr_col] << " ";
			matrix[curr_row][curr_col] = 0;
			curr_row--;
			step++;
			if (matrix[curr_row][curr_col] == 0) {
				curr_row++;
				curr_col++;
				break;
			}
		}

	}
}


/************************************************SPIRAL_TRAVERSING_MATRIX***************************************************************/
/************************************************FIND_NUM_IN_MULT_MATRIX****************************************************************/
int find_number_in_mult_matrix(int N, int X) {
	int limit = (X / 2 < N) ? X / 2 : N;

	if (X < N) {
		limit = (X / 2 < N) ? N : X / 2;
	}

	int count = 0;

	for (int i = 1; i <= limit; i++) {
		if (X % i == 0 && X / i <= limit && i <= X / i) {
			if ((i*i) != X) {
				count += 2;
			}
			else {
				count++;
			}
		}
	}

	return count;
}
/************************************************FIND_NUM_IN_MULT_MATRIX****************************************************************/
