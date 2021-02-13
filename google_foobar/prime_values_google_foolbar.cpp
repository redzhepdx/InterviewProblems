#include "utils.h"

constexpr long long max_boundary_limit = 1000000000;

ll next_prime(ll prev_value){

	bool found = false;
	ll target = prev_value + 2;

	while(!found){
		ll target_sqrt = (ll)std::sqrt(target);
		bool isPrime = true;
		
		for(ll value = 3; value < target_sqrt + 1; value += 2){
			if(target % value == 0){
				isPrime = false;
				break;
			}
		}

		if(isPrime)
			found = true;
		else
			target += 2;
	}
	
	return target;
}

std::pair<std::string, ll> iterative_no_memory_solution(ll query_index, std::pair<std::string, ll> current_solution){
	std::string output = current_solution.first; // "23571113171923293137414347";
	ll prev_prime = current_solution.second; // 47;
	
	while(query_index > (output.length() - 5)){
		ll nxt_prime = next_prime(prev_prime);

		output += std::to_string(nxt_prime);

		prev_prime = nxt_prime;
	}
	
	return std::make_pair(output, prev_prime);
}

std::pair<std::string, ll> approx_bound_solution(ll query_index, ll gap = 5, ll min_start = 150){
	ll target_max_number = std::max((ll)(query_index * 2.2), min_start);
	ll last_prime = 2;
	
	std::vector<bool> primeTable(target_max_number, true);

	primeTable[0] = false;
	primeTable[1] = false;

	std::string output = "";
	
	for(ll value = 2; value < target_max_number; ++value){
		if(primeTable[value]){
			output += std::to_string(value);
			last_prime = value;

			for(ll factor = value + value; factor < target_max_number; factor+=value){
				primeTable[factor] = false;
			}
		}
	}

	return std::make_pair(output, last_prime);
}

int main(){
	ll query_index;
	std::cin >> query_index;
	
	std::pair<std::string, ll> result;

	auto t1 = std::chrono::high_resolution_clock::now();
	if(query_index > max_boundary_limit){
		result = approx_bound_solution(query_index);
		result = iterative_no_memory_solution(query_index, result);
	}
	else{
		result = approx_bound_solution(query_index);	
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	ll last_prime = result.second;
	std::string output_str = result.first;

	// std::cout << output_str << std::endl;
	std::cout << "Time : " << duration << std::endl;
	std::cout << "Last Prime : " << last_prime << std::endl;
	std::cout << "Solution : " << output_str.substr(query_index, 5) << std::endl;
	
	return 0;
}

