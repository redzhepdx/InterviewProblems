#include<iostream>
#include<vector>
#include<unordered_set>
#include<limits>
#include<algorithm>


int number_of_ways(std::vector<int> numbers, int target){
    // Time O(n.k) Space O(n)
    std::vector<int> dp(target + 1, 0);

    dp[0] = 1;
    for(int current_sum = 1; current_sum <= target; ++current_sum){
        for(auto num : numbers){
            if (current_sum - num >= 0){        
                dp[current_sum] += dp[current_sum - num];
            }
        }
    }

    return dp.back();
}

int minimum_possible_coin_count(std::vector<int> numbers, int target){
    // Time O(n.k) Space O(n) k : numbers n : target value

    std::vector<int> dp(target + 1, INT32_MAX);
    dp[0] = 0;
    
    for(int current_sum = 1; current_sum <= target; ++current_sum){
        for(auto num: numbers){
            if(current_sum - num >= 0){
                dp[current_sum] = std::min(dp[current_sum], dp[current_sum - num] + 1);
            }
        }
    }

    return dp.back();
}

int all_the_distinct_ways(std::vector<int> numbers, int target){
    // Time O(n.k) Space O(n.k) k : numbers n : target value
    std::vector<std::vector<int>> dp(target + 1, std::vector<int>(numbers.size(), 0));

    for(unsigned int i = 0; i < numbers.size(); ++i){
        dp[0][i] = 1;
    }
    
    for(int current_sum = 1; current_sum <= target; ++current_sum){
        for(unsigned int num_idx = 0; num_idx < numbers.size(); ++num_idx){
            int previous_sum = current_sum - numbers[num_idx];
            
            // Number of ways that contain numbers[num_idx]
            int previous_total_ways = (previous_sum >= 0) ? dp[previous_sum][num_idx] : 0;

            // Number of ways that don't contain numbers[num_idx]
            int num_ways_witout = (num_idx > 0) ? dp[current_sum][num_idx - 1] : 0;
            
            dp[current_sum][num_idx] = previous_total_ways + num_ways_witout;
        }
    }
    return dp[target][numbers.size() - 1];
}

int main(){
    std::vector<int> numbers = {1, 2, 4};
    int target = 7;

    std::cout << "Number of ways : " << number_of_ways(numbers, target) << "\n";
    std::cout << "Minimum possible coin count : " << minimum_possible_coin_count(numbers, target) << "\n";
    std::cout << "All distinct ways : " << all_the_distinct_ways(numbers, target) << "\n";

    return 0;
}