/*
 Problem : https://www.hackerrank.com/challenges/jesse-and-cookies/problem
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

void print_pq(std::priority_queue<int, std::vector<int>, std::greater<int> >& pq){
    std::cout<< "Priority Queue Status" << std::endl;
    std::vector<int> vec(pq.size());
    std::copy(&(pq.top()), &(pq.top()) + pq.size(), &vec[0]);
    for(int i = 0; i < vec.size(); i++){
        std::cout<< vec[i] << " ";
    }
    std::cout<<std::endl;
}

int main() {
    std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
    int n, min_sweatness;
    std::cin >> n >> min_sweatness;
    for(int i = 0;i < n; i++){
        int elem;
        std::cin >> elem;
        pq.push(elem);
    }
    
    int op_count = 0;
    if(pq.top() < min_sweatness){
        int p1 = pq.top();
        pq.pop();
        int p2 = pq.top();
        pq.pop();
        int serial_sweatness = p1 + 2 * p2;
        pq.push(serial_sweatness);
        if(pq.top() < min_sweatness){
            //print_pq(pq);
            op_count++;
            while(pq.size() > 1 && pq.top() < min_sweatness){
                p1 = pq.top();
                pq.pop();
                p2 = pq.top();
                pq.pop();
                serial_sweatness = p1 + 2 * p2;
                pq.push(serial_sweatness);
                //print_pq(pq);
                op_count++;
            }
        }
        else{
            op_count++;
        }
    }
  
    
    if(pq.size() <= 1){
        if(pq.size() == 1 && pq.top() >= min_sweatness){
            std::cout << op_count << std::endl;
        }
        else{
            std::cout << -1 << std::endl;
        }
    }
    else{
        std::cout << op_count << std::endl;
    }
    
    return 0;
}
