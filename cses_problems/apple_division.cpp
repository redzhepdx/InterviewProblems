#include "utils.h"

ll seperate_apples_dp(ll sum_total, ll sum_first, std::vector<ll> apples, int index){
	ll diff = std::abs(sum_total - sum_first);
	// Base Cases I : Equality	
	if(diff == 0){
		return diff;
	}
	
	// Base Case II : Growing second group
	if(sum_first > sum_total){
		return diff;
	}
	
	// Base Case II : No more apples
	if(index == apples.size()){
		return diff;
	}

	ll min_select = seperate_apples_dp(sum_total - apples[index], sum_first + apples[index], apples, index + 1);
	ll min_discard = seperate_apples_dp(sum_total, sum_first, apples, index + 1);

	return std::min(min_select, min_discard);
}

int main(){

	ll num_apples, apple_weight, total=0;
	std::cin >> num_apples;
	std::vector<ll> apples;

	for(int idx = 0; idx < num_apples; ++idx){
		std::cin >> apple_weight;
		apples.push_back(apple_weight);
		total += apple_weight;
	}
	
	ll min_diff = seperate_apples_dp(total, 0, apples, 0);
	std::cout << min_diff << std::endl;

	return 0;
}
