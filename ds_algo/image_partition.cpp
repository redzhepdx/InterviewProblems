#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <set>

#include <stdlib.h>
#include <time.h>

#define OPENCV

#ifdef OPENCV
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif

/*  Problem : Imagine you have a random image that partitioned 
                 vertically to N parts and those parts shuffled randomly. 
    Task : Can you re-assemble(sort the partitions in correct order) image from shuffled form?
    W : width of the image
    H : height of the image
    Image[W*H] : grayscale image
    Note1 : You don't know the 'N' and you don't know the 'width' of all partitions
    Note2 : Note : Any partition line cannot intersect any pixel 
    Note3 : Width of partitions are the same.
*/

class Image{
public:
    Image(cv::Mat image){
        this->rows = image.rows;
        this->cols = image.cols;

        this->data.resize(rows * cols);

        if (image.isContinuous())
            this->data.assign((uchar*)image.datastart, (uchar*)image.dataend);
    }

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
                std::cout << (unsigned int) this->data[row * this->cols + col] << " ";
            }
            std::cout << std::endl;
        }
    }

public:
    std::vector<uchar> data;
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
    std::vector<unsigned int> getPartitionOrder(std::unique_ptr<Image>& shuffledImage, unsigned int partition_count, unsigned int partition_size) const;

private:
    unsigned int partition_count;
};

std::unique_ptr<Image> Partitioner::createRandomImage(const unsigned int rows, const unsigned int cols) const{
    std::unique_ptr<Image> image = std::make_unique<Image>(rows, cols);

    if(cols % this->partition_count == 0){

        unsigned int partition_size = (unsigned int)(cols / this->partition_count); 
        
        for(unsigned int row = 0; row < rows; ++row){
            for(unsigned int col = 0; col < cols; ++col){
                // unsigned int value = rand() % 10; //
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
    float best_average  = std::numeric_limits<float>::min();
    
    for(unsigned int possible_width = 2; possible_width <= shuffledImage->cols / 2; ++possible_width){
        if(shuffledImage->cols % possible_width == 0){
            unsigned int currPartitionCount = shuffledImage->cols / possible_width;
            
            std::vector<unsigned long> total_diffs;
            
            for(unsigned int line = 1; line < currPartitionCount; ++line){
                unsigned long line_diff = 0;
                for(unsigned int row = 0; row < shuffledImage->rows; ++row){
                    int pixel_diff = (int)shuffledImage->getPixel(row, line * possible_width - 1) - 
                                     (int)shuffledImage->getPixel(row, line * possible_width);
                    line_diff += (unsigned long)(pixel_diff * pixel_diff);

                    // std::cout << (int)shuffledImage->getPixel(row, line * possible_width - 1) << " , " << (int)shuffledImage->getPixel(row, line * possible_width) << std::endl;
                    // std::cout << "pixel diff : " << pixel_diff << std::endl;
                    // std::cout << "line diff : " << line_diff << std::endl;
                    
                }
                total_diffs.push_back(line_diff);
                // std::cout << "New Line" << std::endl;
                // getchar();
            }

            
            float currentAverage = std::accumulate(total_diffs.begin(), total_diffs.end(), 0.0) / total_diffs.size();
            
            std::cout << "Width : " << possible_width << " Avg : " <<  currentAverage << std::endl;
            for(int i = 0; i < total_diffs.size(); ++i)
                std::cout << total_diffs[i] << " ";
            std::cout << std::endl;
            
            if (currentAverage > best_average){
                best_average    = currentAverage;
                partition_count = currPartitionCount;
            }
        }
    }

    return partition_count;
}

std::vector<unsigned int> Partitioner::getPartitionOrder(std::unique_ptr<Image>& shuffledImage, unsigned int partition_count, unsigned int partition_size) const{
    std::vector<std::vector<int>> left_right_diff(partition_count, std::vector<int>(partition_count, 1000));
    std::unordered_map<int, bool> partitions;
    std::set<int>                 partition_occ;
    std::vector<unsigned int>     ordered_partitions;
    
    int head_dist            = std::numeric_limits<int>::min();
    int head_partition_index = 0;

    // Find the first partition
    // Compare the leftmost pixels of current partition with the all other partitions' rightmost pixels
    // For each partition find closest other partition that can be next to current partition and also store the differences
    // Find the maximum difference and index of maximum difference is the first partition of shuffled image
    for(unsigned int p_x = 0; p_x < partition_count; ++p_x){
        int local_min = std::numeric_limits<int>::max();
        partition_occ.insert(p_x);
        partitions[p_x] = true;
        
        for(unsigned int p_y = 1; p_y < partition_count; ++p_y){
            if( p_x != p_y ){
                int total_diff = 0;
                
                for(unsigned int row = 0; row < shuffledImage->rows; ++row){
                    int diff = (int)shuffledImage->getPixel(row, p_x * partition_size) - (int)shuffledImage->getPixel(row, p_y * partition_size - 1);
                    total_diff += std::pow(diff, 2);
                }
                
                if(total_diff < local_min){
                    local_min = total_diff;
                }

                left_right_diff[p_x][p_y] = total_diff;
            }
        }

        if(local_min > head_dist){
            head_dist = local_min;
            head_partition_index = p_x;
        }
    }

    std::cout << "head partition index : " << head_partition_index << std::endl;

    // Sort the all other partitions
    while(!partition_occ.empty()){
        partitions[head_partition_index] = false;
        ordered_partitions.push_back(head_partition_index);
        partition_occ.erase(head_partition_index);
        
        unsigned int current_min = std::numeric_limits<int>::max();
        unsigned int currentHead = head_partition_index;

        for(unsigned int row = 0; row < partition_count; ++row){
            if(left_right_diff[row][currentHead] <= current_min && partitions[row]){
                current_min = left_right_diff[row][currentHead];
                head_partition_index = row; 
            }
        }
    }
    
    std::cout << "\nORDERED : " << std::endl;
    for(int i = 0; i < ordered_partitions.size(); ++i){
        std::cout << ordered_partitions[i] << " ";
    } 
    std::cout << std::endl;

    return ordered_partitions;
}

std::unique_ptr<Image> Partitioner::sortImage(std::unique_ptr<Image>& shuffledImage) const{
    std::unique_ptr<Image> sortedImage            = std::make_unique<Image>(shuffledImage->rows, shuffledImage->cols);
    unsigned int partition_count                  = this->getNumberOfPartitions(shuffledImage);
    unsigned int partition_size                   = shuffledImage->cols / partition_count;
    std::vector<unsigned int> oredered_partitions = this->getPartitionOrder(shuffledImage, partition_count, partition_size);

    std::cout << "Partition Count : " << partition_count << std::endl;

    for(unsigned int row = 0; row < shuffledImage->rows; ++row){
        for(unsigned int col = 0; col < shuffledImage->cols; ++col){
            unsigned int value   = (unsigned int)(col / partition_size);
            unsigned int new_col = oredered_partitions[value] * partition_size + col % partition_size;
            sortedImage->setPixel(row, new_col, shuffledImage->getPixel(row, col));
        }
    }
    
    return sortedImage;
}

int main(void){

    std::unique_ptr<Partitioner> partitioner = std::make_unique<Partitioner>(15);
    
    if(true){
        std::cout << "Enter the name of the image " << std::endl;
        std::string image_name;
        std::cin >> image_name;

        cv::Mat img = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
        //cv::resize(img, img, cv::Size(100, 100), 0, 0);
        

        std::unique_ptr<Image> image = std::make_unique<Image>(img);
        std::unique_ptr<Image> shuffled_image = std::move(partitioner->shuffleImage(image));
        cv::Mat shuffled_mat(shuffled_image->rows, shuffled_image->cols, CV_8UC1);
        memcpy(shuffled_mat.data, shuffled_image->data.data(), shuffled_image->data.size() * sizeof(uchar));
        

        std::unique_ptr<Image> sorted_image = std::move(partitioner->sortImage(shuffled_image));
        cv::Mat sorted_cv(sorted_image->rows, sorted_image->cols, CV_8UC1);
        memcpy(sorted_cv.data, sorted_image->data.data(), sorted_image->data.size() * sizeof(uchar));

        cv::imshow("Real Image", img);
        cv::imshow("Shuffled Image", shuffled_mat);
        cv::imwrite("shuffled.png", shuffled_mat);
        cv::imshow("Sorted Image", sorted_cv);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
    else{
        srand (time(NULL));

        std::unique_ptr<Image> image = partitioner->createRandomImage(20, 20);
        image->print();
        std::cout << std::endl;

        std::unique_ptr<Image> shuffled_image = std::move(partitioner->shuffleImage(image));
        shuffled_image->print();

        std::unique_ptr<Image> sorted_image = std::move(partitioner->sortImage(shuffled_image));
        sorted_image->print();
    }

    std::cout << "Done!!!" << std::endl;

    return 0;
}