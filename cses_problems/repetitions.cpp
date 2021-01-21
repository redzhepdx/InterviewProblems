#include "utils.h"

int main(){
	std::string input;
	std::cin >> input;

	long long prev = 1;
	long long current = 1;

	for (int i = 1; i < input.size(); ++i) {
		// std::cout << input[i - 1] << " " << input[i] << " " << current << std::endl;
		// getchar();
        if(input[i] == input[i-1]){
			++current;
		}
		else{
			if (prev < current){
				prev = current;
			}
			current = 1;
		}
    }

	prev = std::max(prev, current);
	

	std::cout << prev << std::endl;

	return 0;
}
