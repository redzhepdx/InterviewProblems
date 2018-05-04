#pragma once
#include "structures.h"
/*******************************************MICROSOFT_QUESTIONS*******************************************************/
/********************************************FIND_WORD_IN_MATRIX******************************************************/
#ifndef CHAR_MTR_COL
#define CHAR_MTR_COL 5
#endif

#ifndef CHAR_MTR_ROW
#define CHAR_MTR_ROW 5
#endif

//Dý
bool isInMatrix(int row, int col) {
	return row >= 0 && col >= 0 && row < CHAR_MTR_ROW && col <= CHAR_MTR_COL;
}

//First Char Found Check Directions
bool scanForWord(char matrix[CHAR_MTR_ROW][CHAR_MTR_COL], std::string word, int row, int col) {
	for (int n_row = -1; n_row <= 1; n_row++) {
		for (int n_col = -1; n_col <= 1; n_col++) {
			//Just Look 4 Directions
			if ((n_row == 0 || n_col == 0 ) && (n_row != n_col)) {

				int cur_row = row + n_row;
				int cur_col = col + n_col;
				int i = 1;
				//Check Untill Then End Of String
				for (i = 1; i < word.size(); i++) {
					if (isInMatrix(cur_row, cur_col)) {
						if (word[i] == matrix[cur_row][cur_col]) {
							cur_row += n_row;
							cur_col += n_col;
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}

				if (i == word.size()) {
					return true;
				}
			}
		}
	}

	return false;
}

bool findWordInMatrix(char matrix[CHAR_MTR_ROW][CHAR_MTR_COL], std::string word) {
	for (int row = 0; row < CHAR_MTR_ROW; row++) {
		for (int col = 0; col < CHAR_MTR_COL; col++) {
			//Head Char Found
			if (matrix[row][col] == word[0]) {
				if (scanForWord(matrix, word, row, col))
					return true;
			}
		}
	}

	return false;
}
/********************************************FIND_WORD_IN_MATRIX******************************************************/
/***************************************LONGEST_INCREASING_SUBSEQUENCE************************************************/
/*
SAMPLE : 
[0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
length: 6
subset : [0, 2, 6, 9, 11, 15]
*/

template<typename T>
int find_longest_increasing_subsequence_length(std::vector<T> list) {
	
	int length = 1;
	std::vector<T> tail(list.size());

	if (list.size() == 0) {
		return 0;
	}

	//Atleast it will contain one element in every sub sequence
	tail[0] = list[0];

	for (int i = 1; i < list.size(); i++) {
		//New Smallest value
		if (list[i] <= tail[0]) {
			tail[0] = list[i];
		}
		else if (list[i] > tail[length - 1]) {
			//Largest Sequence Size and end of this sequence
			//extend sequence length
			tail[length] = list[i];
			length++;
		}
		else {
			//if it is member of any sub sequence , add it and delete upper bound , for the track more long sequence
			tail[find_upper_bound(tail, 0, length - 1, list[i])] = list[i];
		}
	}
	return length;
}
/***************************************LONGEST_INCREASING_SUBSEQUENCE************************************************/


/**************************************FIND_ISLAND_COUNT_IN_MATRIX****************************************************/

bool isInIsland(int row, int col) {
	return row >= 0 && col >= 0 && row < MTR_SIZE && col < MTR_SIZE;
}

void capture_island(int(&matrix)[MTR_SIZE][MTR_SIZE], int row, int col) {
	matrix[row][col] = 0;
	for (int n_x = -1; n_x <= 1; n_x++) {
		for (int n_y = -1; n_y <= 1; n_y++) {
			int next_x = row + n_x;
			int next_y = col + n_y;
			if (isInIsland(next_x, next_y) && matrix[next_x][next_y] && (n_x != 0 || n_y != 0)) {
				capture_island(matrix, next_x, next_y);
			}	
		}
	}
}

int count_islands(int (&matrix)[MTR_SIZE][MTR_SIZE]) {
	int island_count = 0;
	for (int i = 0; i < MTR_SIZE; i++) {
		for (int j = 0; j < MTR_SIZE; j++) {
			if (matrix[i][j]) {
				capture_island(matrix, i, j);
				island_count++;
				//print_matrix(matrix);
				//getchar();
			}
		}
	}
	return island_count;
}
/*********************************************************************************************************************/
/********************************************LONGEST CONSECUTIVE SEQUENCE*********************************************/
template <typename T>
int findMaxConsSequence(std::vector<T> list){
    int max = 0;
    std::unordered_map<T, bool> hashT;
    for(int i = 0; i < list.size(); i++){
        hashT[list[i]] = true;
    }

    for(int i = 0; i < list.size(); i++){
        //If we couldn't see this element before
        if(!hashT.count(list[i] - 1)) {
            //Pick it as start of sequence and look next values after this
            int index = list[i];
            while(hashT.count(index + 1)){
                index += 1;
            }
            int size = index - list[i] + 1;
            max = (max < size) ? size : max;
        }
    }
    return max;
}
/**********************************************LONGEST CONSECUTIVE SEQUENCE****************************************/
/***********************************************COIN_COLLECTING_IN_GRID********************************************/
/*
You are given a 2-d matrix where each cell represents number of coins in that cell. Assuming we start at matrix[0][0], and can only move right or down, find the maximum number of coins you can collect by the bottom right corner.

For example, in this matrix

0 3 1 1
2 0 0 4
1 5 3 1
The most we can collect is 0 + 2 + 1 + 5 + 3 + 1 = 12 coins.
*/

int mostCollectableCoinCount(std::vector<std::vector<int>> matrix ) {
	std::vector<std::vector<int>> value_matrix(matrix.size(), std::vector<int>(matrix[0].size(), 0));
	int max_val;
	value_matrix[0][0] = matrix[0][0];

	for (int row = 1; row < matrix.size(); row++) {
		value_matrix[row][0] += value_matrix[row - 1][0] + matrix[row][0];
	}

	for (int col = 1; col < matrix[0].size(); col++) {
		value_matrix[0][col] += value_matrix[0][col - 1] + matrix[0][col];
	}
	

	for (int row = 1; row < matrix.size(); row++) {
		for (int col = 1; col < matrix[row].size(); col++) {
			int max_top  = value_matrix[row - 1][col] + matrix[row][col];
			int max_left = value_matrix[row][col - 1] + matrix[row][col];
			value_matrix[row][col] = (max_top > max_left) ? max_top : max_left;
		}
	}
	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix[row].size(); col++) {
			std::cout << value_matrix[row][col] << " ";
		}
		std::cout << std::endl;
	}

	return value_matrix[matrix.size() - 1][matrix[0].size() - 1];

}

/***********************************************COIN_COLLECTING_IN_GRID********************************************/

