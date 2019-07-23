#include <iostream>
#include <vector>
#include <memory>
#include <limits>

struct Image{
    std::vector<unsigned int> data;
    unsigned int rows;
    unsigned int cols;

    unsigned int getPixel(const unsigned int row, const unsigned int col){
        return this->data[row * cols + col];
    }

    void setPixel(const unsigned int row, const unsigned int col, unsigned int val){
        this->data[row * cols + col] = val;
    }

    void print();
};

class Partitioner{
public:
    Partitioner(){}

public:
    std::vector<unsigned int> shuffleImage(std::vector<unsigned int> image, unsigned int partition_count) const;
    std::vector<unsigned int> sortImage(std::vector<unsigned int> shuffledImage) const;
    unsigned int getNumberOfPartitions(std::vector<unsigned int> shuffledImage) const;
};

std::vector<unsigned int> Partitioner::shuffleImage(std::vector<unsigned int> image, unsigned int partition_count) const{
    std::vector<unsigned int> shuffeldImage;
    // TODO : IN PROGRESS
    return shuffeldImage;
}

std::vector<unsigned int> Partitioner::sortImage(std::vector<unsigned int> shuffledImage) const{
    std::vector<unsigned int> sortedImage;
    unsigned int partition_count = this->getNumberOfPartitions(shuffledImage);
    // TODO : IN PROGRESS
    return sortedImage;
}

unsigned int Partitioner::getNumberOfPartitions(std::vector<unsigned int> shuffeldImage) const{
    int partition_count = 0;
    // TODO : IN PROGRESS
    return partition_count;
}

int main(void){
    std::vector<unsigned int> image;

    std::unique_ptr<Partitioner> partitioner = std::make_unique<Partitioner>();
    std::vector<unsigned int> shuffled_image = partitioner->shuffleImage(image, 10);
    std::vector<unsigned int> sorted_image = partitioner->sortImage(shuffled_image);

    std::cout << "Done!!!" << std::endl;

    return 0;
}