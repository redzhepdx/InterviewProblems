#include <iostream>
#include <vector>
#include <limits.h>
#include <memory>
#include <numeric>
#include <functional>
#include <cstdint>

typedef std::int32_t index;
typedef std::int32_t cost;

template <typename T>
class Node{
public:
    Node(){}

    Node(const int value, const int frequency):value(value), frequency(frequency){}

    std::unique_ptr<Node<T>> copy(){
        std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>(this->value, this->frequency); 

        if(this->left != nullptr){
            node->left = std::move(this->left->copy());
        }
        if(this->right != nullptr){
            node->right = std::move(this->right->copy());
        }
        return std::move(node);
    }

public:
    int value;
    int frequency;
    std::unique_ptr<Node<T>> left = nullptr;
    std::unique_ptr<Node<T>> right = nullptr;
};

template <typename T>
class OptimalBst {

public:
    OptimalBst(const std::vector<T> sequences, const std::vector<int> frequencies){
        this->sequences = sequences;
        
        this->frequencies = frequencies;

        this->matrix.resize(this->sequences.size(), std::vector<std::pair<cost, index>>(this->sequences.size(), std::make_pair(0, 0)));
        
        for(int i = 0; i < this->frequencies.size(); ++i) {
            matrix[i][i] = std::make_pair(this->frequencies[i], i);
        }
        this->find_optimal_bst();
    }


    void find_optimal_bst(){
        for(int level = 2; level <= this->frequencies.size(); ++level){
            for(int row = 0; row <= this->frequencies.size() - level; ++row){
                int col = row + level - 1;
                int sum = std::accumulate(this->frequencies.begin() + row, this->frequencies.begin() + col + 1, 0);
                this->matrix[row][col].first = INT_MAX;
                
                for(std::int32_t k = row; k <= col; ++k){
                    std::int32_t val = sum + ((k - 1) < row ? 0 : this->matrix[row][k - 1].first) + ((k + 1) > col ? 0 : this->matrix[k + 1][col].first);
                    if(val < this->matrix[row][col].first){
                        this->matrix[row][col] = std::make_pair(val, k);
                    }
                }
            }
        }

        this->printMatrices();

        this->root = this->constructTree(0, this->matrix[0][this->sequences.size() - 1].second, this->sequences.size() - 1);

        this->printTree(this->root, 0);
    }

    void printMatrices(void) const{
        std::cout << std::endl;
        for(int i = 0; i < this->matrix.size(); ++i){
            for(int j = 0; j < this->matrix.size(); ++j){
                std::cout << this->matrix[i][j].first << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        for(int i = 0; i < this->matrix.size(); ++i){
            for(int j = 0; j < this->matrix.size(); ++j){
                std::cout << this->matrix[i][j].second << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printTree(){
        return this->printTree(this->root, 0);
    }

    void printTree(std::unique_ptr<Node<T>>& curr, int level) const {
        std::cout << level <<  ".level : " << curr->value << std::endl;

        if(curr->left != nullptr){
            this->printTree(curr->left, level+1);
        }
        
        if(curr->right != nullptr){
            this->printTree(curr->right, level+1);
        }
    }

    std::unique_ptr<Node<T>>& search(T value){
        return this->search(value, this->root);
    }
 
    

private:
    std::unique_ptr<Node<T>>& search(T value, std::unique_ptr<Node<T>>& curr) const {
        if(curr->value == value){
            return curr;
        }
        else if (curr->value > value){
            return search(value, curr->left);
        }
        else{
            return search(value, curr->right);
        }
    }

    std::unique_ptr<Node<T>> constructTree(int left_limit, int curr_root_index, int right_limit){
        std::unique_ptr<Node<T>> curr_root = std::make_unique<Node<T>>(this->sequences[curr_root_index], this->frequencies[curr_root_index]);

        if(left_limit > right_limit){
            return std::move(nullptr);
        }
    
        curr_root->left = constructTree(left_limit, this->matrix[left_limit][curr_root_index - 1].second, curr_root_index - 1);
        if (curr_root_index + 1 <= this->sequences.size() - 1){
            curr_root->right = constructTree(curr_root_index + 1, this->matrix[curr_root_index + 1][right_limit].second, right_limit);
        }
        else{
            curr_root->right = std::move(nullptr);
        }
        return std::move(curr_root);
    }


public:
    std::unique_ptr<Node<T>> root;
    std::vector<T> sequences;
    std::vector<int> frequencies;
    std::vector< std::vector <std::pair< cost, index>>> matrix;
};

int main(void){

    std::vector<int> sequences {0, 1, 2, 3, 4, 5, 6};
    std::vector<int> frequencies {2, 5, 4, 1, 6, 3, 8};

    std::unique_ptr<OptimalBst<int>> opt_bst = std::make_unique<OptimalBst<int>>(sequences, frequencies);

    std::unique_ptr<Node<int>>& resp_node = opt_bst->search(2);
    
    std::cout << resp_node->frequency << std::endl;
    std::cout << resp_node->value << std::endl;
    std::cout << resp_node->right->value << std::endl;

    opt_bst->printTree();
    
    return 0;
}