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