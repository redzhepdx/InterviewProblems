#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>

class Image{
public:
    Image(unsigned int rows, unsigned int cols){
        this->rows = rows;
        this->cols = cols;
        this->data.resize(rows * cols, 0);
    }

    unsigned int getPixel(const unsigned int row, const unsigned int col){
        return this->data[row * this->cols + col];
    }

    void setPixel(const unsigned int row, const unsigned int col, unsigned int val){
        this->data[row * this->cols + col] = val;
    }

    void print(){
        for(unsigned int row = 0; row < this->rows; ++row){
            for(unsigned int col = 0; col < this->cols; ++col){
                std::cout << this->data[row * this->cols + col] << " ";
            }
            std::cout << std::endl;
        }
    }

public:
    std::vector<unsigned int> data;
    unsigned int rows;
    unsigned int cols;
};

class Partitioner{
public:
    Partitioner(unsigned int partition_count):partition_count(partition_count){}

public:
    std::unique_ptr<Image> shuffleImage(std::unique_ptr<Image>& image) const;
    std::unique_ptr<Image> sortImage(std::unique_ptr<Image>& shuffledImage) const;
    std::unique_ptr<Image> createRandomImage(const unsigned int rows, const unsigned int cols) const;
    unsigned int getNumberOfPartitions(std::unique_ptr<Image>& shuffledImage) const;

private:
    unsigned int partition_count;
};

std::unique_ptr<Image> Partitioner::createRandomImage(const unsigned int rows, const unsigned int cols) const{
    std::unique_ptr<Image> image = std::make_unique<Image>(rows, cols);

    if(cols % this->partition_count == 0){

        unsigned int partition_size = (unsigned int)(cols / this->partition_count); 
        
        for(unsigned int row = 0; row < rows; ++row){
            for(unsigned int col = 0; col < cols; ++col){
                unsigned int value = (unsigned int)(col / partition_size);
                image->setPixel(row, col, value);
            }
        }
    }
    else{
        throw "Column size of the image is not divisible by partition count!";
    }

    return image;
}

std::unique_ptr<Image> Partitioner::shuffleImage(std::unique_ptr<Image>& image) const{
    std::unique_ptr<Image> shuffledImage = std::make_unique<Image>(image->rows, image->cols);
    
    std::vector<unsigned int> shuffledPartitionVector(this->partition_count);

    // Generate sorted index list : 0, 1, 2, 3, .... partition count
    std::generate(shuffledPartitionVector.begin(), shuffledPartitionVector.end(), [n = 0]() mutable { return n++; });

    // Shuffle generated List
    std::random_shuffle(shuffledPartitionVector.begin(), shuffledPartitionVector.end());

    unsigned int partition_size = (unsigned int)(image->cols / this->partition_count);
    
    // Shuffle partitions
    for(unsigned int row = 0; row < image->rows; ++row){
        for(unsigned int col = 0; col < image->cols; ++col){
            unsigned int value   = (unsigned int)(col / partition_size);
            unsigned int new_col = shuffledPartitionVector[value] * partition_size + col % partition_size;
            shuffledImage->setPixel(row, new_col, image->getPixel(row, col));
        }
    }
    
    return shuffledImage;
}

unsigned int Partitioner::getNumberOfPartitions(std::unique_ptr<Image>& shuffledImage) const{
    int partition_count = 0;
    float best_average  = -9999;

    for(unsigned int divisor = 2; divisor <= shuffledImage->cols / 2; ++divisor){
        if(shuffledImage->cols % divisor == 0){
            unsigned int currPartitionCount = shuffledImage->cols / divisor;
            
            std::vector<unsigned long> total_diffs;
            
            for(unsigned int line = 1; line < currPartitionCount; ++line){
                unsigned long line_diff = 0;
                for(unsigned int row = 0; row < shuffledImage->rows; ++row){
                    int pixel_diff = (int)shuffledImage->getPixel(row, line * divisor) - (int)shuffledImage->getPixel(row, line * divisor + 1);
                    line_diff += (unsigned int)(pixel_diff * pixel_diff);
                }
                total_diffs.push_back(line_diff);
            }

            float currentAverage = std::accumulate(total_diffs.begin(), total_diffs.end(), 0.0) / total_diffs.size();
            if (currentAverage > best_average){
                best_average    = currentAverage;
                partition_count = currPartitionCount;
            }
        }
    }

    return shuffleImage->cols / partition_count;
}

std::unique_ptr<Image> Partitioner::sortImage(std::unique_ptr<Image>& shuffledImage) const{
    std::unique_ptr<Image> sortedImage = std::make_unique<Image>(shuffledImage->rows, shuffledImage->cols);
    unsigned int partition_count = this->getNumberOfPartitions(shuffledImage);
    std::cout << "Number of partitions : " << partition_count << std::endl;
    // TODO : IN PROGRESS
    return sortedImage;
}

int main(void){
   
    std::unique_ptr<Partitioner> partitioner = std::make_unique<Partitioner>(5);
    
    std::unique_ptr<Image> image = partitioner->createRandomImage(30, 30);

    image->print();
    std::cout << std::endl;

    std::unique_ptr<Image> shuffled_image = std::move(partitioner->shuffleImage(image));
    shuffled_image->print();

    std::unique_ptr<Image> sorted_image = std::move(partitioner->sortImage(shuffled_image));
    sorted_image->print();

    std::cout << "Done!!!" << std::endl;

    return 0;
}