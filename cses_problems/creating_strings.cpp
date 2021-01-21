#include "utils.h"

int main(){
	std::string input;
	std::cin >> input;
	
	std::sort(input.begin(), input.end());
	
	std::vector<std::string> permutations;
	permutations.push_back(input);
	while(generate_next_permutation(input)){
		permutations.push_back(input);
	}
	
	std::cout << permutations.size() << std::endl;
	for(auto& perm : permutations){
		std::cout << perm << std::endl;
	}
 
	return 0;
}
