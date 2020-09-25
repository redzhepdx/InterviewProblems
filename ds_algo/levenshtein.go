package main

import (
	"fmt"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func levenshtein_distance(token1 []rune, token2 []rune) int{
	/*
		Implementation of levenshtein distance algorithm
		@param token1 : first string
		@param token2 : second string
    	*/
	// Matrix Implementation

	first_str_len := len(token1)
    	second_str_len := len(token2)

	// Matrix Creation
	dist_matrix := make([][]int, first_str_len + 1)
	for i := range dist_matrix {
		dist_matrix[i] = make([]int, second_str_len + 1)
		dist_matrix[i][0] = i
	}
	for i := 1; i <= second_str_len; i++ {
		dist_matrix[0][i] = i
	}

	// Distance Calculation using full matrix
	for i := 1; i <= first_str_len; i++ {
		for j:= 1; j <= second_str_len; j++ {
			if token1[i - 1] == token2[j - 1]{
				dist_matrix[i][j] = dist_matrix[i-1][j-1]
			} else {
				dist_matrix[i][j] = min(min(dist_matrix[i-1][j], dist_matrix[i][j-1]), dist_matrix[i-1][j-1]) + 1
			}
		}
	}

	return dist_matrix[first_str_len][second_str_len]
}

func opt_levenshtein_distance(token1 []rune, token2 []rune) int {
	/*
		Implementation of levenshtein distance algorithm
		@param token1 : first string
		@param token2 : second string
	*/
	first_str_len := len(token1)
	second_str_len := len(token2)

	col_array_first := make([]int, first_str_len+1)
	col_array_second := make([]int, first_str_len+1)

	for i := 0; i < first_str_len+1; i++ {
		col_array_first[i] = i
	}

	for idx := 0; idx < second_str_len; idx++ {
		// Increment the first value of the second array, reflected version of addition/removal for an empty string prefix
		col_array_second[0] = col_array_first[0] + 1

		for idy := 0; idy < first_str_len; idy++ {
			if token1[idy] == token2[idx] {
				// No penalty if characters are the same, get the value from diagonal
				col_array_second[idy+1] = col_array_first[idy]
			} else {
				// Penalty Rate is the same for addition, removal or change
				col_array_second[idy+1] = min(min(col_array_second[idy], col_array_first[idy+1]), col_array_first[idy]) + 1
			}
		}
		// Switch arrays
		copy(col_array_first, col_array_second)
	}

	distance := col_array_first[first_str_len]

	return distance
}

func limited_opt_levenshtein_distance(token1 []rune, token2 []rune, maxDist int) int {
	/*
		Implementation of levenshtein distance algorithm
		@param token1 : first string
		@param token2 : second string
		@param maxDist : threshold value to stop distance measurement
	*/
	first_str_len := len(token1)
	second_str_len := len(token2)

	col_array_first := make([]int, first_str_len+1)
	col_array_second := make([]int, first_str_len+1)

	for i := 0; i < first_str_len+1; i++ {
		col_array_first[i] = i
	}

	for idx := 0; idx < second_str_len; idx++ {
		// Increment the first value of the second array, reflected version of addition/removal for an empty string prefix
		col_array_second[0] = col_array_first[0] + 1

		// Track optimal distance
		current_min_diff := maxDist * maxDist

		for idy := 0; idy < first_str_len; idy++ {
			if token1[idy] == token2[idx] {
				// No penalty if characters are the same, get the value from diagonal
				col_array_second[idy+1] = col_array_first[idy]
			} else {
				// Penalty Rate is the same for addition or removal
				col_array_second[idy+1] = min(min(col_array_second[idy], col_array_first[idy+1]), col_array_first[idy]) + 1
			}
			current_min_diff = min(col_array_second[idy+1], current_min_diff)
		}

		if current_min_diff > maxDist {
			return maxDist + 1
		}

		// Switch arrays
		copy(col_array_first, col_array_second)
	}

	distance := col_array_first[first_str_len]

	return distance
}

func main() {
	const first_string = "House"
	const second_string = "Mouse" 

	fmt.Println("First String : ", first_string)
	fmt.Println("Second String : ", second_string)

	first_rune := []rune(first_string)
	second_rune := []rune(second_string)
	mtr_dist := levenshtein_distance(first_rune, second_rune)
	distance := opt_levenshtein_distance(first_rune, second_rune)
	fmt.Println("--------------------")
	limited_distance := limited_opt_levenshtein_distance(first_rune, second_rune, 2)

	fmt.Println("Matrix Distance : ", mtr_dist)
	fmt.Println("Levenshtein Distance : ", distance)
	fmt.Println("Limited Levenshtein Distance : ", limited_distance)
}
