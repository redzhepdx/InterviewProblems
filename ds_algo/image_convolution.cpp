#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

bool isInImage(const int currentCol,
               const int currentRow,
               const int inImageWidth,
               const int inImageHeight){
  return currentCol < inImageWidth && currentRow < inImageHeight && currentCol >= 0 && currentRow >= 0;
}

bool blurImage(
  const unsigned char* inImage,
  const int inImageWidth,
  const int inImageHeight,
  const int inRadius,
  unsigned char* outImage)
{
  
  if(inImageWidth <= 0 && inImageHeight <= 0 && inRadius <= 0){
    return false;
  }

  unsigned int kernel_edge = 2 *  inRadius + 1;
  unsigned int kernel_area = kernel_edge * kernel_edge;
  
  std::vector<unsigned int> kernel(kernel_area, 1);  // Static average filtering
  
  for(int row = 0; row < inImageHeight; ++row){
    for(int col = 0; col < inImageWidth; ++col){
      
      // int row_idx = threadIdx.x + blockDim.x * blockIdx.x
      // int row_idy = threadIdx.y + blockDim.y * blockIdx.y
      
      // 2D -> 1D index convertion
      int index = row * inImageWidth + col;
      
      int total = 0;
      
      int sumTotalValidKernelValues = 0;
      
      // Convolution [Make it a function]
      for(int kernel_row = -inRadius; kernel_row <= inRadius; ++kernel_row){
        for(int kernel_col = -inRadius; kernel_col <= inRadius; ++kernel_col){
          
          // 2D -> 1D index convertion
          int neighbour_row = row + kernel_row;
          int neighbour_col = col + kernel_col;
          
          int neighbour_index = neighbour_row * inImageHeight + neighbour_col;
          int kernel_index = (kernel_row + inRadius) * kernel_edge + (kernel_col + inRadius);
          
          // Gather convolution values
          if(isInImage(neighbour_col, neighbour_row, inImageWidth, inImageHeight)){
            sumTotalValidKernelValues += kernel[kernel_index];
            total += inImage[neighbour_index] * kernel[kernel_index];
          }
        }
      }
      
      outImage[index] = (unsigned char)std::round((float)total / (float)sumTotalValidKernelValues);
    }
  }
  
  return true;
}

// TESTING: print an image
void printImage(
  const unsigned char* inImage,
  const int inImageWidth,
  const int inImageHeight)
{
  if (!inImage) return;
  for (int _x = 0; _x < inImageWidth; _x++)
  {
    for (int _y = 0; _y < inImageHeight; _y++)
    {
      std::cout << std::setw(3) << (int)inImage[_y * inImageWidth + _x] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << std::endl;
}

int main() {
  
  const int _testWidth = 7;
  const int _testHeight = 7;
  const int _testRadius = 1;
  unsigned char *_testImage = new unsigned char[_testWidth*_testHeight];
  unsigned char *_testOutput = new unsigned char[_testWidth*_testHeight];
  
  for (int _x=0; _x<_testWidth; _x++)
    for (int _y = 0; _y < _testHeight; _y++)
    {
      // three different cases. comment out.
      // _testImage[_y * _testWidth + _x] = 2;
      _testImage[_y * _testWidth + _x] = std::min(std::min(_x, _testWidth - _x), std::min(_y, _testHeight - _y));
      //_testImage[_y * _testWidth + _x] = std::min(_x, _y);
      //_testImage[_y * _testWidth + _x] = std::min(255, _x * _y);
    }
  
	std::cout << "Start..." << std::endl;
  printImage(_testImage, _testWidth, _testHeight);
  if (!blurImage(_testImage, _testWidth, _testHeight, _testRadius, _testOutput)) {
    std::cout << "Blurring failed!" << std::endl;
  } else {
    std::cout << "Blurring done!" << std::endl;
  }
  printImage(_testOutput, _testWidth, _testHeight);
	return 0;
}


/*
  0   0  -0-  0   0   0   0
  0   1   1   1   1   1   1
  0   1   2   2   2   2   1
  0   1   2   3   3   2   1
  0   1   2   3   3   2   1
  0   1   2   2   2   2   1
  0   1   1   1   1   1   1

*/