#include "utils.h"

int main(){
	int num_queens = 8;
	ll total_combinations = 0;
	std::vector<std::string> rows(num_queens);

	for(int row = 0; row  < num_queens; ++row){
		std::cin >> rows[row];
	}

	std::vector<int> positions(num_queens, 0);
	std::iota(positions.begin(), positions.end(), 0);
	
	bool valid = true;

	// Check all positional permutations
	while(std::next_permutation(positions.begin(), positions.end())){
		// check current positioning is valid
		valid = true;
		for(int queen_idx = 0; queen_idx < num_queens - 1; ++queen_idx){
			
			// check queen is on reserved spot	
			if(rows[queen_idx][positions[queen_idx]] == '*'){
				valid = false;
				break;
			}
			
			// Other Queens
			for(int other_q_index = queen_idx + 1; other_q_index < num_queens; ++other_q_index){
				
				// reserved spot check
				if(rows[other_q_index][positions[other_q_index]] == '*'){
					valid = false;
					break;
				}
				
				// Diagonal threatening 
				if( ((queen_idx + positions[queen_idx]) == (positions[other_q_index] + other_q_index)) || 
					((queen_idx + positions[other_q_index]) == (other_q_index + positions[queen_idx])) ){
					valid = false;
					break;
				}
			}

			if(!valid){
				break;
			}
		}

		if(valid){
			total_combinations += 1;
		}
	}
	
	std::cout << total_combinations << std::endl;

	return 0;
}
