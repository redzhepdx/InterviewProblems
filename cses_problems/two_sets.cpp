#include "utils.h"

int main(){
	ll n;
	std::cin >> n;

	if(n % 4 == 3){
		std::cout << "YES" << std::endl;
		std::cout << (ll)(n / 2) + 1 << std::endl;
		std::cout << "1 2 ";
		for(ll x = 4; x < n; x += 4){
			std::cout << x << " " << x + 3 << " ";
		}
		std::cout << std::endl;
		
		std::cout << (ll)(n / 2) << std::endl;
		std::cout << "3 ";
		for(ll y = 5; y < n; y += 4){
			std::cout << y << " " << y + 1 << " ";
		}
		std::cout << std::endl;
	}
	else if(n % 4 == 0){
		std::cout << "YES" << std::endl;
		
		std::cout << n / 2 << std::endl;
		for(ll x = 1; x  < (n / 2); x += 2){
			std::cout << x << " " << n - x + 1 << " ";
		}
		std::cout << std::endl;
		
		std::cout << n / 2 << std::endl;
		for(ll y = 2; y <= (n / 2); y += 2){
			std::cout << y << " " << n - y + 1 << " ";
		}
		std::cout << std::endl;
	}
	else{
		std::cout << "NO" << std::endl;
	}

	return 0;
}
