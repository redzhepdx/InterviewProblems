#include "utils.h"

int main(){
	ll n;
	std::cin >> n;
	
	ll total_trailing_zeros = 0;	
	
	while(n >= 5){
		total_trailing_zeros += (ll)(n / 5);
		n /= 5;
	}
	
	std::cout << total_trailing_zeros << std::endl;

	return 0;
}
