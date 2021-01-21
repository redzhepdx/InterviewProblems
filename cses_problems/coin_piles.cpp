#include "utils.h"

bool check_piles_dp(ll a, ll b, std::unordered_map<std::pair<ll, ll>, bool, hash_pair> memo){
	// Good failure to understand the problem
	std::pair<ll, ll> current(a, b);

	if(memo[current]){
		return memo[current];
	}
	
	if(a < 0 || b < 0){
		return false;
	}

	if((a != 0 || b != 0) && (a * b) == 0)
		return false;

	if(a < (b / 2)){
		return false;
	}
	
	if(b < (a / 2)){
		return false;
	}
	
	if(a == 0 && b == 0){
		return true;
	}

	bool res_left = check_piles_dp(a - 2, b - 1, memo);
	memo[std::pair<ll, ll>(a - 2, b - 1)] = res_left;
	memo[std::pair<ll, ll>(b - 1, a - 2)] = res_left;

	if(res_left){
		return res_left;
	}
	bool res_right = check_piles_dp(a - 1, b - 2, memo);
	memo[std::pair<ll, ll>(a - 1, b - 2)] = res_right;
	memo[std::pair<ll, ll>(b - 2, a - 1)] = res_right;
	
	memo[current] = res_left || res_right;

	return memo[current];
}

int main(){
	ll number_of_tests, a, b;
	std::cin >> number_of_tests;
	std::unordered_map<std::pair<ll, ll>, bool, hash_pair> memo;

	for(ll test=0; test < number_of_tests; ++test){
		std::cin >> a >> b;
		if((a + b) % 3 == 0){
			if(std::min(a, b) >= std::abs(a - b)){
				std::cout << "YES" << std::endl;
			}
			else{
				std::cout << "NO" << std::endl;
			}
		}
		else{
			std::cout << "NO" << std::endl;
		}
		// check_piles_dp(a, b, memo) ? std::cout << "YES" << std::endl : std::cout << "NO" << std::endl;
	}
	
	return 0;
}
