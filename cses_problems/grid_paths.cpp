#include "utils.h"

std::vector<std::vector<bool>> visited(7, std::vector<bool>(7, false));
std::string pattern;

bool isPositionValid(int pos_row, int pos_col){
	return pos_row >= 0 && pos_row < 7 && pos_col >= 0 && pos_col < 7 && !visited[pos_row][pos_col];
}

int dfs(int row, int col, int move_count){
	if(row == 6 && col == 0){
		if(move_count == 48){
			return 1;
		}
		return 0;
	}

	if(move_count > 48){
		return 0;
	}

	visited[row][col] = true;
	int answer = 0;

	if(pattern[move_count] == '?' || pattern[move_count] == 'R'){
		if(col < 6 && !visited[row][col + 1]){
			if(!(!isPositionValid(row, col + 2) && isPositionValid(row + 1, col + 1) && isPositionValid(row - 1, col + 1))){
				answer += dfs(row, col + 1, move_count + 1);
			}
		}
	}

	if(pattern[move_count] == '?' || pattern[move_count] == 'D'){
		if(row < 6 && !visited[row + 1][col]){
			if(!(!isPositionValid(row + 2, col) && isPositionValid(row + 1, col + 1) && isPositionValid(row + 1, col - 1))){
				answer += dfs(row + 1, col, move_count + 1);
			}
		}
	}
	
	if(pattern[move_count] == '?' || pattern[move_count] == 'L'){
		if(col > 0 && !visited[row][col - 1]){
			if(!(!isPositionValid(row, col - 2) && isPositionValid(row + 1, col - 1) && isPositionValid(row - 1, col - 1))){
				answer += dfs(row, col - 1, move_count + 1);
			}
		}
	}

	if(pattern[move_count] == '?' || pattern[move_count] == 'U'){
		if(row > 0 && !visited[row - 1][col]){
			if(!(!isPositionValid(row - 2, col) && isPositionValid(row - 1, col + 1) && isPositionValid(row - 1, col - 1))){
				answer += dfs(row - 1, col, move_count + 1);
			}
		}
	}

	visited[row][col] = false;

	return answer;
}

int main(){
	std::cin >> pattern;
	
	int answer = dfs(0, 0, 0);
	
	std::cout << answer << std::endl;
	return 0;
}
