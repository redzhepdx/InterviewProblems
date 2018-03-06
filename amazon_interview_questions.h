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