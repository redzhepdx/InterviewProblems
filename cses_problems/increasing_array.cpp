#include "utils.h"

int main(){
	long long n;
	std::cin >> n;
	long long total_moves = 0;
	long long current;
	long long next;

	std::cin >> current;

	for(int i = 1; i < n; ++i){
		std::cin >> next;
		if(current > next){
			total_moves += (current - next);
		}
		else{
			current = next;
		}
	}

	std::cout << total_moves << std::endl;
	return 0;
}
