/*
  Memoized DP - Problem : https://www.hackerrank.com/challenges/coin-change/problem
*/

#include <bits/stdc++.h>

using namespace std;


long mem_coin_dp(long n, vector<long > c, int start, unordered_map<string, long> &memo){
    if(n < 0){
        return 0;
    }
    else if(n == 0){
        return 1;
    }
    if (start >= c.size()){
        return 0;
    }
    string current = to_string(n) + ", a, " + to_string(start);
    if(memo[current]){
        return memo[current];
    }
    memo[current] = mem_coin_dp(n - c[start], c, start, memo) + mem_coin_dp(n, c, start+1, memo);
    return memo[current];
}

long getWays(long n, vector < long > c){
    unordered_map<string, long> memo;
    return mem_coin_dp(n, c, 0, memo);
}


int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    long ways = getWays(n, c);
    std::cout << ways << std::endl;
    return 0;
}
