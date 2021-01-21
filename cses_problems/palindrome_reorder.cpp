#include "utils.h"

int main(){
	std::string input;
	std::cin >> input;

	std::unordered_map<char, int> map;	

	ll num_even = 0, num_odd = 0;

	for(unsigned int idx = 0; idx < input.size(); ++idx){
		char cc = input[idx];
		if(map[cc]){
			if(map[cc] % 2 == 0){
				num_even -= 1;
				num_odd += 1;
			}
			else{
				num_even += 1;
				num_odd -= 1;
			}
			map[cc] += 1;
		}
		else{
			map[cc] = 1;
			num_odd += 1;
		}
	}

	if(num_odd > 1){
		// 2 or more character repetitions that have odd length
		std::cout << "NO SOLUTION" << std::endl;
	}
	else{
		std::string output_string = "";
		if(num_odd == 1){
			for(auto& cc : map){
				// Odd found, put it into the middle
				if(cc.second % 2 == 1){
					std::string odd_string(cc.second, cc.first);
					output_string.insert(output_string.size() / 2, odd_string);
				}
				else{
					// Split in a half and put them at the beginning and end
					std::string first_half(cc.second / 2, cc.first);
					std::string second_half(cc.second / 2, cc.first);
					output_string = first_half + output_string + second_half;
				}
			}
		}
		else{
			// All even
			for(auto& cc : map){
				// Split in a half and put them at the beginning and end
				std::string first_half(cc.second / 2, cc.first);
				std::string second_half(cc.second / 2, cc.first);
				output_string = first_half + output_string + second_half;
			}
		}
		std::cout << output_string << std::endl;
	}

	return 0;
}
