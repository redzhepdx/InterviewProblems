#include "utils.h"

int main(){
	std::vector<std::string> gray_codes;
	gray_codes.push_back("0");
	gray_codes.push_back("1");
	
	ll n;
	std::cin >> n;

	ll total_gray_codes = power(2, n);
	
	for(int n_i = 2; n_i < total_gray_codes; n_i *= 2){
		size_t current_len = gray_codes.size();

		// Reverse prefix 1
		for(int code_idx = current_len - 1; code_idx >= 0; --code_idx){
			gray_codes.push_back("1" + gray_codes[code_idx]);
		}

		// Order prefix 1
		for(int code_idx = 0; code_idx < current_len; ++code_idx){
		    gray_codes[code_idx] = "0" + gray_codes[code_idx];
		}
	}

	for(auto &s : gray_codes){
		std::cout << s << std::endl;
	}
	
	return 0;
}
