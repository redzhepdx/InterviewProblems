#include "utils.h"

int main(){
	int num_gears;
	std::vector<ll> gear_positions(num_gears);

	std::cin >> num_gears;

	int x_signature = 1;
	float diff = 0;
	
	for(int i = 0; i < num_gears; ++i){
		std::cin >> gear_positions[i];
		if(i >= 1){
			x_signature *= -1;
			diff = (gear_positions[i] - gear_positions[i - 1]) - diff;
		}
	}

	if(x_signature == -1 && diff > 0){
		std::cout << "[" << 2 * diff << ", 3]" << std::endl;
	}
	else if(x_signature == 1 && diff < 0){
		std::cout << "[" << -diff << ", 1" << std::endl;
	}
	else{
		std::cout << "[-1, -1]" << std::endl;
	}

	std::cout << "X signature : " << x_signature << std::endl;
	std::cout << "Diff : " << diff << std::endl;
	std::cout << "x = 2 * ( " << x_signature << " * x + " << diff << " )" << std::endl;

	return 0;
}
