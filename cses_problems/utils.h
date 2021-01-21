#ifndef __UTILITY__
#define __UTILITY__

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <functional>
#include <numeric>
#include <climits>

#define ll long long
#define OVERFLOW_MOD 1000000007

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const std::pair<T1, T2>& p) const
    { 
        auto hash1 = std::hash<T1>{}(p.first); 
        auto hash2 = std::hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

template<class T>
void print_array(std::vector<T> array){
	for(T elem : array){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

ll power(ll base, ll top){
    ll result = 1;
    while(top > 0){
        if(top % 2 == 1){
            result = ((result % OVERFLOW_MOD) * (base % OVERFLOW_MOD)) % OVERFLOW_MOD;
        }
        base = ((base % OVERFLOW_MOD) * (base % OVERFLOW_MOD)) % OVERFLOW_MOD;
        top /= 2;
    }
    return result;
}

bool generate_next_permutation(std::string& str){
    ll last = str.size() - 1;

    // Get the first drop's indexx
    while(str[last] <= str[last - 1]){
        // Last Permutation
        if(last == 1){
            return false;
        }
        --last;
    }

    ll first_drop = last - 1;

    last = str.size() - 1;
    // Get the last element's index which is higher than first drop
    while(str[last] <= str[first_drop]){
        --last;
    }

    ll higher_last = last;

    // Swap
    std::swap(str[first_drop], str[higher_last]);

    // Reverse after first_drop, remaining lowest -> remaining highest
    std::reverse(str.begin() + first_drop + 1, str.end());
    return true;
}

#endif //__UTILITY__
