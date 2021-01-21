#include "utils.h"

int main(){
	
	long long input;
	std::cin >> input;
	
	if(input < 4){
		std::cout << "NO SOLUTION" << std::endl;
		return 1;
	}

	long long counter_even;
	long long counter_odd;
	
	if(input % 2 == 0){
		counter_even = input;
		counter_odd = input - 1;
	}
	else{
		counter_even = input - 1;
		counter_odd = input;
	}
		
	// Odd reverse order
	while(counter_odd > 0){
		std::cout << counter_odd << " ";
		counter_odd -= 2;
	}

	// Even reverse order
	while(counter_even > 0){
		std::cout << counter_even << " ";
		counter_even -= 2;
	}	

	return 0;
}
