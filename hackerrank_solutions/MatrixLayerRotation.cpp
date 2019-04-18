/*
 In Place Solution - Problem : https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    int rows,cols,rotation_count;
    
    std::cin >> rows >> cols >> rotation_count;
    
    std::vector<std::vector<int>> matrix(rows,std::vector<int>(cols,0));
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cin >> matrix[i][j];
        }
    }
    
    int width = cols - 1;
    int height = rows - 1;
    int start_x = 0;
    int start_y = 0;
    
    int c_r = rows;
    int c_c = cols;
    //for(int rot = 0; rot < rotation_count; rot++)
    while(width > start_y && height > start_x){
        
        //while(width > start_y && height > start_x)
        int square_size = 2 * (c_r + c_c) - 4;
        //std::cout << square_size << std::endl;
        //std::cout << rotation_count % square_size << std::endl;
        int layer_rot_count = rotation_count % square_size;
        for(int rot = 0; rot < layer_rot_count; rot++){
            
            int prev = matrix[start_x][start_y];
            
            for(int i = start_x + 1; i <= height; i++){
                int temp = matrix[i][start_y];
                matrix[i][start_y] = prev;
                prev = temp;
            }
            
            for(int i = start_y + 1; i <= width; i++){
                int temp = matrix[height][i];
                matrix[height][i] = prev;
                prev = temp;
            }
            
            for(int i = height - 1; i >= start_x; i--){
                int temp = matrix[i][width];
                matrix[i][width] = prev;
                prev = temp;
            }
            
            for(int i = width - 1; i >= start_y; i--){
                int temp = matrix[start_x][i];
                matrix[start_x][i] = prev;
                prev = temp;
            }           
        }
        
        width--;
        height--;
        start_x++;
        start_y++;
        c_r -= 2;
        c_c -= 2;
        
    }
    
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
