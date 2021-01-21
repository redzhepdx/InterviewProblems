#include "utils.h"

int main(){
	int test;
	long long y, x;
	std::cin >> test;
	for(int i = 0; i < test; ++i){
		std::cin >> y >> x;
		if(y > x){
			if( y % 2 == 0){
				std::cout << y * y - x + 1 << std::endl;
			}else{
				std::cout << ((y - 1) *  (y - 1) + 1) + x - 1 << std::endl;
			}
		}
		else{
			if( x % 2 == 0){
				std::cout << x * x - (x - 1) - (x - y) << std::endl;
			}
			else{
				std::cout << ((x - 1) * (x - 1) + 1) + (x - 1) + (x - y) << std::endl;
			}
		}
	}
	return 0;
}
