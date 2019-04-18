/*
 Problem : https://www.hackerrank.com/challenges/find-the-running-median/problem
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

float get_median(std::priority_queue<int , std::vector<int> > &maxHeap, 
                 std::priority_queue<int , std::vector<int>, std::greater<int>> &minHeap){
    if(maxHeap.size() == minHeap.size())
    {
        return ((float)maxHeap.top() + (float)minHeap.top()) / 2.0;   
    }
    else {
        return (float)maxHeap.top();
    }
}

void add_value(std::priority_queue<int , std::vector<int> > &maxHeap, 
               std::priority_queue<int , std::vector<int>, std::greater<int>> &minHeap,
               int value){
    if(maxHeap.size() == 0){
        maxHeap.push(value);
    }
    else if(maxHeap.size() == minHeap.size()){
        if(value < minHeap.top()){
            maxHeap.push(value);
        }
        else{
            int top_min = minHeap.top();
            minHeap.pop();
            minHeap.push(value);
            maxHeap.push(top_min);
        }
    }
    else{
        if(value > maxHeap.top()){
            minHeap.push(value);
        }
        else{
            int top_max = maxHeap.top();
            maxHeap.pop();
            minHeap.push(top_max);
            maxHeap.push(value);
        }
    }
}
    

using namespace std;
int main() {
    float median;
    int n;
    std::priority_queue<int, std::vector<int> > maxHeap;
    std::priority_queue<int, std::vector<int> , std::greater<int> > minHeap;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        int val;
        std::cin >> val;
        add_value(maxHeap, minHeap, val);
        float median = get_median(maxHeap, minHeap);
        std::cout << (float)median << std::endl;
    }
    
    return 0;
}
