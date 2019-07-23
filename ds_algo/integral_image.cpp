#include <iostream>
#include <memory>
#include <exception>
#include <vector>
#include <climits>

#ifdef _MSC_VER
#define _NOEXCEPT noexcept
#else
#define _NOEXCEPT noexcept
#endif

template<typename T>
using matrix = std::vector<std::vector<T>>;

template <typename T>
class IntegralImage{
public:
    IntegralImage(int _rows, int _cols);
    IntegralImage(const IntegralImage<T> &other);
    IntegralImage(IntegralImage<T> && rhs_other) _NOEXCEPT;

    ~IntegralImage();
    
    T         get_area(int row_x, int col_x, int row_y, int col_y) const;
    T         get_value(int row, int col) const;
    T         get_sum_val(int row, int col) const;
    
    matrix<T> getIntegral(); 
    
    void      print_integral() const;
    void      print() const;

    IntegralImage<T> & operator=(const IntegralImage<T> &other);
	IntegralImage<T> & operator=(IntegralImage<T> && rhs_other) _NOEXCEPT;

private:
    T isInMatrix(int row, int col);

public:
    matrix<T>     image;
    matrix<T>     integral_image;
    
    int rows;
    int cols;
};

template <typename T>
IntegralImage<T>::IntegralImage(int _rows, int _cols):rows(_rows), cols(cols){
    this->image.resize(_rows, std::vector<T>(_cols));
    this->integral_image = this->getIntegral();
}
template IntegralImage<int>::IntegralImage(int _rows, int _cols);

template <typename T>
IntegralImage<T>::IntegralImage(const IntegralImage<T> &other){
    this->rows           = other.rows;
    this->cols           = other.cols;
    this->image          = other.image;
    this->integral_image = other.integral_image;
}
template IntegralImage<int>::IntegralImage(const IntegralImage<int> &other);

template <typename T>
IntegralImage<T>::IntegralImage(IntegralImage<T> && rhs_other) _NOEXCEPT{
    this->rows = std::move(rhs_other.rows);
    this->cols = std::move(rhs_other.cols);
    this->image = std::move(rhs_other.image);
    this->integral_image = std::move(rhs_other.integral_image);
}
template IntegralImage<int>::IntegralImage(IntegralImage<int> && rhs_other) _NOEXCEPT;

template <typename T>
IntegralImage<T> & IntegralImage<T>::operator=(const IntegralImage<T> &other){
    this->rows           = other.rows;
    this->cols           = other.cols;
    this->image          = other.image;
    this->integral_image = other.integral_image;
    return *this;
}
template IntegralImage<int> & IntegralImage<int>::operator=(const IntegralImage<int> &other);

template <typename T>
IntegralImage<T> & IntegralImage<T>::operator=(IntegralImage<T> && rhs_other) _NOEXCEPT{
    if(this != &rhs_other){
        this->rows = std::move(rhs_other.rows);
        this->cols = std::move(rhs_other.cols);
        this->image = std::move(rhs_other.image);
        this->integral_image = std::move(rhs_other.integral_image);
    }
    return *this;
}
template IntegralImage<int> & IntegralImage<int>::operator=(IntegralImage<int> && rhs_other) _NOEXCEPT;

template <typename T>
IntegralImage<T>::~IntegralImage(){

}
template IntegralImage<int>::~IntegralImage();

template <typename T>
T IntegralImage<T>::get_sum_val(int row, int col) const {
    return this->integral_image[row][col];
}
template int IntegralImage<int>::get_sum_val(int row, int col) const;

template <typename T>
T IntegralImage<T>::get_area(int row_x, int col_x, int row_y, int col_y) const {
    return (this->get_sum_val(row_y, col_y) + this->get_sum_val(row_x, col_x)) - 
            (this->get_sum_val(row_x, row_y) - this->get_sum_val(row_y, col_x));
}
template int IntegralImage<int>::get_area(int row_x, int col_x, int row_y, int col_y) const;

template <typename T>
T IntegralImage<T>::get_value(int row, int col) const {
    return this->integral_image[row][col];
}
template int IntegralImage<int>::get_value(int row, int col) const;

template <typename T>
matrix<T> IntegralImage<T>::getIntegral(){
    matrix<T> int_matrix = std::vector<std::vector<T>>(this->rows, std::vector<T>(this->cols, 0));

    for(int row = 0; row < this->rows; ++row){
        for(int col = 0; col < this->cols; ++col){
            int val = this->get_value(row, col);
            int vdx = isInMatrix(row, col - 1);
            int vdy = isInMatrix(row - 1, col);
            int vdz = isInMatrix(row - 1, col - 1);
            int_matrix[row][col] = val + vdx + vdy - vdz;
        }   
    }

    return std::move(int_matrix);
}
template matrix<int> IntegralImage<int>::getIntegral();

template <typename T>
void IntegralImage<T>::print_integral() const {
    for(int row = 0; row < this->rows; ++row){
        for(int col = 0; col < this->cols; ++col){
            std::cout << this->integral_image[row][col] << " ";
        }
        std::cout << std::endl;
    }        
}
template void IntegralImage<int>::print_integral() const;

template <typename T>
void IntegralImage<T>::print() const{
    for(int row = 0; row < this->rows; ++row){
        for(int col = 0; col < this->cols; ++col){
            std::cout << this->image[row][col] << " ";
        }
        std::cout << std::endl;
    }        
}
template void IntegralImage<int>::print() const;

template <typename T>
T IntegralImage<T>::isInMatrix(int row, int col){
    return (row >= 0) && (col >= 0) && (row < this->rows) && (col < this->cols) ? this->get_value(row, col) : 0;
}
template int IntegralImage<int>::isInMatrix(int row, int col);

int main(void){
    std::unique_ptr<IntegralImage<int>> image = std::make_unique<IntegralImage<int>>(5, 5);
    image->print();
    return 0;
}