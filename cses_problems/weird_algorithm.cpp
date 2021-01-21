#include "utils.h"

int main(){
	ll x;
	std::cin >> x;
	
	while(x != 1){
		std::cout << x << " ";
		x = (x % 2 == 1) ? x * 3 + 1 : x / 2;
	}
	std::cout << 1;
	
	return 0;
}
