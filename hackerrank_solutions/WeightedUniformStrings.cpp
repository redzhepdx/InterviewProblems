/*
 Problem : https://www.hackerrank.com/challenges/weighted-uniform-string/problem
*/
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void uniform_substring_map(std::string s, std::unordered_map<int, bool>& sub_weights){
    int index = 0;
    int uniform_len = 0;
    int sub_w = 0;
    while(index < s.length()){
         
         sub_w += (s[index + uniform_len] - 'a' + 1);
             
         if(!sub_weights[sub_w]){
            sub_weights[sub_w] = true;  
         }
         uniform_len++;
         if(s[index] != s[index + uniform_len]){
             index += uniform_len;
             uniform_len = 0;
             sub_w = 0;
         }
    }
}

int main(){
    string s;
    cin >> s;
    std::unordered_map<int, bool> sub_weights;
    
    uniform_substring_map(s, sub_weights);
    int n;
    cin >> n;
    for(int a0 = 0; a0 < n; a0++){
        int x;
        cin >> x;
        if(sub_weights[x]){
            std::cout << "Yes" << std::endl;
        }
        else{
            std::cout << "No" << std::endl;
        }
    }
    return 0;
}
