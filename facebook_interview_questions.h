#pragma once
#include "structures.h"


/******************************************SAME_SUB_SETS*********************************/
bool contains_same_sum(std::vector<int> list, int set_sum_1, int set_sum_2, int index) {
	if (index == list.size()) {
		return set_sum_1 == set_sum_2;
	}

	return contains_same_sum(list, set_sum_1 + list[index], set_sum_2, index + 1) ||
		contains_same_sum(list, set_sum_1, set_sum_2 + list[index], index + 1);
}
/******************************************SAME_SUB_SETS*********************************/

/**************************************COUNT_ALL_PATHS_TOP_TO_BOTTOM*********************/
#ifndef MTR_SIZE
#define MTR_SIZE 0
#endif

int count_ways(std::vector<std::vector<int>> matrix, int row, int col) {
	int res = 0;

	if (row == MTR_SIZE - 1 && col == MTR_SIZE - 1) {
		res += 1;
	}
	else if (row >= MTR_SIZE || col >= MTR_SIZE) {
		res = 0;
	}
	else {
		res = count_ways(matrix, row, col + 1);
		res += count_ways(matrix, row + 1, col);
	}

	return res;
}

/**************************************COUNT_ALL_PATHS_TOP_TO_BOTTOM*********************/

/***************************************MAX_TRIPLET_PRODUCT******************************/
int max_product(std::vector<int> list){
	int max_level_1 = INT_MIN;
	int max_level_2 = INT_MIN;
	int max_level_3 = INT_MIN;
	int min_level_1 = INT_MAX;
	int min_level_2 = INT_MAX;
	
	for(unsigned int i = 0; i < list.size(); i++){	
		//Max 3 Elements in List
		if(list[i] >= max_level_1){
			max_level_3 = max_level_2;
			max_level_2 = max_level_1;
			max_level_1 = list[i];
		}
		else if(list[i] >= max_level_2){
			max_level_3 = max_level_2;
			max_level_2 = list[i];
		}
		else if(list[i] >= max_level_3){
			max_level_3 = list[i];
		}

		if(list[i] <= min_level_1){
			min_level_2 = min_level_1;
			min_level_1 = list[i];
		}else if(list[i] <= min_level_2){
			min_level_2 = list[i];
		}
	}
	std::cout << "Max 1 : " << max_level_1 << " Max 2 : " << max_level_2 << " Max 3 : " << max_level_3 << " Min 1 : " << min_level_1 << " Min 2 : " << min_level_2 << std::endl;
	return std::max(max_level_3 * max_level_2 * max_level_1, max_level_1 * min_level_1 * min_level_2);

}
/***************************************MAX_TRIPLET_PRODUCT******************************/
