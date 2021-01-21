#include "utils.h"

int main(){
	long long n;
	std::cin >> n;
	for(long long i = 1; i <= n; ++i){
		long long two_by_three = 2 * (i - 1) * (i - 2);
		long long three_by_two = 2 * (i - 2) * (i - 1);
		long long total = (i * i) * (i * i - 1) / 2;
		std::cout << total - (two_by_three + three_by_two) << std::endl;
	}
	return 0;
}
