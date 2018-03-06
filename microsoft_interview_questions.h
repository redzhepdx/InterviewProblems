#pragma once
#include "structures.h"
/*******************************************MICROSOFT_QUESTIONS******************************************/
/********************************************FIND_WORD_IN_MATRIX*****************************************/
/*CONTAINS BUG CHECK FOR PROBLEM*/
#ifndef CHAR_MTR_COL
#define CHAR_MTR_COL 5
#endif

#ifndef CHAR_MTR_ROW
#define CHAR_MTR_ROW 5
#endif

bool findWordInMatrix(char matrix[CHAR_MTR_ROW][CHAR_MTR_COL], std::string word) {
	std::unordered_map<char, int> word_characters;

	for (int i = 0; i < word.size(); i++) {
		word_characters[word[i]] = i;
	}
	bool found = false;

	for (int row = 0; row < CHAR_MTR_ROW; row++) {
		for (int col = 0; col < CHAR_MTR_COL; col++) {
			//String in char found
			if (word_characters.count(matrix[row][col])) {
				int found_char_index = word_characters[matrix[row][col]];
				
				int curr_row = row - 1;
				int curr_col = col - 1;

				int left_char_index = (word_characters[matrix[row][col]] != 0) ? word_characters[matrix[row][col]] - 1: 0;
				int right_char_index =
					(word_characters[matrix[row][col]] != word.size() + 1) ? word_characters[matrix[row][col]] + 1: word.size() - 1;
				
				//Check Horizontally
				
				//Check Left Part
				while (left_char_index > 0 && curr_col > 0 && matrix[row][curr_col] == word[left_char_index] ) {
					left_char_index--;
					curr_col--;
				}

				curr_col = col + 1;
				

				//Check Right Part
				while (right_char_index < word.size() && curr_col < CHAR_MTR_COL  && matrix[row][curr_col] == word[right_char_index]) {
					right_char_index++;
					curr_col++;
				}

				if (right_char_index == word.size() - 1 && left_char_index == 0) {
					found = true;
					break;
				}

				left_char_index = (word_characters[matrix[row][col]] != 0) ? word_characters[matrix[row][col]] - 1 : 0;
				right_char_index =
					(word_characters[matrix[row][col]] != word.size() + 1) ? word_characters[matrix[row][col]] + 1 : word.size() - 1;
				
				//Check Vertically
				//Check Left Part
				while (left_char_index > 0 && curr_row > 0 && matrix[curr_row][col] == word[left_char_index]) {
					left_char_index--;
					curr_row--;
				}

				curr_row = row + 1;

				//Check Right Part
				while (right_char_index < word.size() && curr_row < CHAR_MTR_ROW  && matrix[curr_row][col] == word[right_char_index]) {
					right_char_index++;
					curr_row ++;
				}

				if (right_char_index == word.size() - 1 && left_char_index == 0) {
					found = true;
					break;
				}

				col = curr_col;
			}
		}
		if (found) {
			break;
		}
	}

	return found;
}
/********************************************FIND_WORD_IN_MATRIX*****************************************/