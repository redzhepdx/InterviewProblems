#include "utils.h"

int main(){
	long long n;
	std::cin >> n;
	
	long long total = (n * (n + 1)) / 2;
	
	for(int i = 0; i < n - 1; ++i){
		long long current_num;
		std::cin >> current_num;
		total -= current_num;	
	}

	std::cout << total << std::endl;
	
	return 0;
}
