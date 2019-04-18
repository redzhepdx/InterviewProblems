/*
 Problems : 
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int xorand(int min_1, int min_2){
    return (((min_1 & min_2) ^ (min_1 | min_2)) & (min_1 ^ min_2));
}

int main() {
    int n;
    std::cin >> n;
    int max_xor = -999999999;
    std::vector<int> v;
    std::vector<int> s;
    int val;
    
    int a;
    for(int i = 0 ; i < n; i++){
        std::cin >> a;
        v.push_back(a);
    }
    
    for(int i = 0; i < n; i++){
        while(s.size() != 0){
            int val = xorand(s.back(), v[i]);
            max_xor = (max_xor < val) ? val : max_xor;
            if(v[i] < s.back()){
                s.pop_back();
            }
            else{
                break;
            }
        }
        s.push_back(v[i]);       
    }
    
    std::cout << max_xor << std::endl;
    return 0;
}
