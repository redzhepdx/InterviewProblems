/*
 Problem : https://www.hackerrank.com/challenges/maximum-element/problem
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class max_stack {
    public:
        max_stack(void);
        void push_element(long long int x);
        long long int pop_element();
        void print_max();
    public:
        std::vector<long long int> stack;
        long long int max_val = -10000;
        std::vector<long long int> last_maxes;
};

max_stack::max_stack(void){
    
}

void max_stack::push_element(long long int x){   
    this->stack.push_back(x); //push the value end of array
    
    if(x >= this->max_val){ //if current value is bigger than last max_value
        this->last_maxes.push_back(this->max_val);//store last max value if new max value popped it will be new max value
        this->max_val = x; //set the current value as the max value
    }
}


long long int max_stack::pop_element(){
    long long int val = this->stack.back(); //get last added element from array
    this->stack.pop_back(); // pop it from stack
    if(val == this->max_val){ //if popped value equals to the max value 
        long long int last_max = this->last_maxes.back(); //get last max value
        this->last_maxes.pop_back(); //Delete it from last maxes
        this->max_val = last_max; //set new max value to last max value before this element added
    }
    
    return val;
}

void max_stack::print_max(){
    std::cout << this->max_val << std::endl;//print current last value
}

int main() {
    long int query_count;
    std::cin >> query_count;
    max_stack *m_stack = new max_stack();
    for(long int i = 0; i < query_count; i++){
        int op;
        std::cin >> op;
        switch(op){
            case 1:
                long long int value;
                std::cin >> value;
                m_stack->push_element(value);
                break;
            case 2:
                m_stack->pop_element();
                break;
            case 3:
                m_stack->print_max();
                break;
        }
    }
    
    return 0;
}
