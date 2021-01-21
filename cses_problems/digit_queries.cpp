#include "utils.h"

int main(){
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
	
	int query_count; 
	ll digit_index;
	std::cin >> query_count;

	for(int i = 0; i < query_count; ++i){
		std::cin >> digit_index;
		ll lower_bound = 1;
		ll digit_count = 1;
		ll total_digits = 9 * lower_bound;

		while(total_digits < digit_index){
			++digit_count;
			lower_bound = lower_bound * 10;
			total_digits += lower_bound * digit_count * 9;
		}

		total_digits -= (lower_bound * digit_count * 9);

		ll num_digits_after_lb = digit_index - total_digits;
		ll numbers = (ll)(num_digits_after_lb / digit_count);
		ll remaining_digits = num_digits_after_lb % digit_count;		
		
		if(remaining_digits > 0){
			// remaining-th digit of the number
			ll current_number = lower_bound + numbers;
			std::string current_number_str = std::to_string(current_number);
			std::cout << current_number_str[remaining_digits - 1] << std::endl;
		}
		else{
			ll current_number = lower_bound + numbers - 1;
			std::string str_res = std::to_string(current_number);
			std::cout << str_res[str_res.size() - 1] << std::endl;
		}
	}	

	return 0;
}
