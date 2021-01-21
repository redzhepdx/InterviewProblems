#include "utils.h"

void solve_tower(int num_disks, int source, int intermediate, int destination){
	if(num_disks == 1){
		std::cout << source << " " << destination << std::endl;
	}
	else{
		solve_tower(num_disks - 1, source, destination, intermediate);
		std::cout << source << " " << destination << std::endl;
		solve_tower(num_disks - 1, intermediate, source, destination);
	}
}

void solve(int n){
	std::cout << power(2, n) - 1 << std::endl;
	solve_tower(n, 1, 2, 3);
}

int main(){

	int n;
	std::cin >> n;
	solve(n);

	return 0;
}
