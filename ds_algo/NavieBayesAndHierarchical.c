/*
Navie Bayes and Hierarchical Clustering Algorithms . You can obtain data set from https://archive.ics.uci.edu/ml/datasets/Dermatology.
*/
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>

#define INSTANCE_COUNT 366
#define FEATURE_COUNT 35
#define CLASS_COUNT 6
#define THRESHOLD 0.7
#define AVARAGE_AGE "35"
#define K_FOLD_CROSS_VALIDATION 0.7

//Data struct for the hold and set clustered instances
struct Cluster_t {

	std::vector<uint16_t> features;
	uint16_t index;
	uint16_t cluster;

};

//Navie Bayes Classification Algorithm
uint16_t NavieBayesClassification(std::vector<std::vector<uint16_t>> &inputs , std::vector<uint16_t> &sampleInfos) {

	std::vector<double> results;

	uint16_t prediction = 0;//Prediction class
	
	//Computing all necessary probabilities with counting for every class
	//Taking a class which has bigger probability than others
	for (uint16_t i = 1; i <= CLASS_COUNT; i++) {
		
		double probability = 1.0;
	
		for (uint16_t j = 0; j < sampleInfos.size() - 1; j++) {
		
			uint16_t counter = 0;
			
			uint16_t classCounter = 0;
			
			for (uint16_t k = 0; k < inputs.size(); k++) {
			
				if (inputs[k][inputs[k].size() - 1] == i) {
				
					classCounter++;
					
					if (inputs[k][j] == sampleInfos[j]) {
						counter++;
					}
				}
			}

			if (counter == 0) counter = 1;//If probability = 0 then , make it so small but not zero
			probability *= ((double)counter / (double)classCounter);
		}
		results.push_back(probability);
	}
	prediction = std::max_element(results.begin(), results.end()) - results.begin() + 1;//Find max element in prediction array and send it's position
	return prediction;
}

//Dividing inputs into 2 different data structures(train and test) with using k fold cross validation
void TestNavieBayesClassification(std::vector<std::vector<uint16_t>> &inputs, double k_folks_cross_validation) {
	
	std::vector<std::vector<uint16_t>> train((int)(k_folks_cross_validation * (double)INSTANCE_COUNT));
	
	std::vector<std::vector<uint16_t>> test(INSTANCE_COUNT - train.size());

	int confusionMatrix[6][6];//Class confusion matrix
	
	for (uint16_t i = 0; i < 6; i++)
	{
		for (uint16_t j = 0; j < 6; j++)
		{
			confusionMatrix[i][j] = 0;
		}
	}

	uint16_t truePredictionCount = 0;//True prediction count
	uint16_t falsePredictionCount = 0;//False prediction count

	//Getting the train inputs
	for (uint16_t i = 0; i < train.size(); i++) {
		train[i].resize(inputs[i].size());
		train[i] = inputs[i];
	}

	//Getting test inputs
	for (uint16_t i = 0; i < test.size(); i++) {
		test[i].resize(inputs[i + train.size()].size());
		test[i] = inputs[i + train.size()];
	}

	//Processing and learning with navie bayes
	for (uint16_t i = 0; i < test.size(); i++) {
		uint16_t prediction = NavieBayesClassification(train, test[i]);
		(prediction == test[i][test[i].size() - 1]) ? ++truePredictionCount : ++falsePredictionCount;
		confusionMatrix[prediction][test[i][test[i].size() - 1]]++;
	}

	std::cout << "True Prediction Count : " << truePredictionCount << std::endl;
	std::cout << "False Prediction Count : " << falsePredictionCount << std::endl;
	std::cout << "Confusion Matrix : " << std::endl;
	std::cout << "\t";
	for (uint16_t i = 0; i < 6; i++)
	{
		std::cout << i << "\t";
	}

	std::cout << std::endl;
	for (uint16_t i = 0; i < 6; i++)
	{
		std::cout << i << "\t";
		for (uint16_t j = 0; j < 6; j++)
		{
			std::cout << confusionMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "Navie Bayes Classification Done" << std::endl;
}

//Computing similarity between two class and return maximumum similarity
double ComputeSimilarityBetweenNodes(std::vector<Cluster_t> &firstBlob, std::vector<Cluster_t> &secondBlob) {

	double MaxSimilarity = 0.0;
	for (uint16_t i = 0; i < firstBlob.size(); i++) {

		for (uint16_t j = 0; j < secondBlob.size(); j++) {

			uint16_t sameCount = 0;

			for (uint16_t k = 0; k < firstBlob[i].features.size() - 1; k++) {
				if (firstBlob[i].features[k] == secondBlob[j].features[k]) {
					sameCount++;
				}
			}
			
			double similarity = (double)sameCount / (double)(FEATURE_COUNT - 1);
			
			if (similarity > MaxSimilarity) {
				MaxSimilarity = similarity;
			}
		}
	}

	return MaxSimilarity;
}

//Find most similar classes or instances and merges them 
void FindMostSimilarsAndMerge(std::vector < std::vector < Cluster_t>> &blobs , std::vector<std::vector<double>> distMatrix) {

	uint16_t rowPos = 0, colPos = 0;
	
	double maxSimilarity = 0.0;
	
	for (uint16_t i = 0; i < distMatrix.size(); i++) {
		
		uint16_t pos = std::max_element(distMatrix[i].begin(), distMatrix[i].end()) - distMatrix[i].begin();
		
		if (distMatrix[i][pos] > maxSimilarity) {
			rowPos = i;
			colPos = pos;
			maxSimilarity = distMatrix[i][pos];
		}
	}
	
	//Merge similar classes
	for (uint16_t i = 0; i < blobs[colPos].size(); i++) {
		blobs[rowPos].push_back(blobs[colPos][i]);
	}

	//Delete classes because they are MERGED!!They will consider together in next steps
	blobs.erase(blobs.begin() + colPos);
}

//Check all classes' distances bigger then selected threshold
bool FullyClassified(std::vector<std::vector<double>> distMatrix) {

	for (uint16_t i = 0; i < distMatrix.size(); i++) {
		for (uint16_t j = 0; j < distMatrix[i].size(); j++) {
			if (distMatrix[i][j] > THRESHOLD) {
				return false;
			}
		}
	}

	return true;
}

//Compute distance matrix between all classes
std::vector<std::vector<double>> CalculateDistanceMatrix(std::vector < std::vector < Cluster_t>> &blobs) {

	std::vector < std::vector < Cluster_t>> newBlobs = blobs;

	std::vector<std::vector<double>> distMatrix(blobs.size());

	for (uint16_t i = 0; i < blobs.size(); i++) {
		distMatrix[i].resize(blobs.size());
	}

	for (uint16_t i = 0; i < distMatrix.size(); i++) {
		for (uint16_t j = 0; j < distMatrix.size(); j++) {
			distMatrix[i][j] = ComputeSimilarityBetweenNodes(newBlobs[i], newBlobs[j]);
			//If classes are same make their similarity 0.0 
			//By using this way algorithm don't look this cases
			if (distMatrix[i][j] == 1.0) {
				distMatrix[i][j] = 0.0;
			}
		}
	}
	
	return distMatrix;
}

//Hierarchical Clustering Algorithm
//It uses similarity because just age feature is numerical , other features are nominal
void HierarchicalClustering(std::vector < std::vector < Cluster_t>> &blobs) {

	std::vector < std::vector < Cluster_t>> newBlobs = blobs;
	
	std::vector<std::vector<double>> distanceMatrix = CalculateDistanceMatrix(newBlobs);
	
	while (!FullyClassified(distanceMatrix)) {

		FindMostSimilarsAndMerge(newBlobs, distanceMatrix);

		distanceMatrix.resize(newBlobs.size());

		for (uint16_t i = 0; i < newBlobs.size(); i++) {
			distanceMatrix[i].resize(newBlobs.size());
		}

		distanceMatrix = CalculateDistanceMatrix(newBlobs);

		
		std::cout << "Class Count : " << newBlobs.size() << std::endl;
		
	}

	for (uint16_t i = 0; i < newBlobs.size(); i++) {
		std::cout << newBlobs[i].size() << std::endl;
		for (uint16_t j = 0; j < newBlobs[i].size(); j++) {
			newBlobs[i][j].cluster = i;
		}
	}
	
	uint16_t trueClassificationCount = 0;//True clustered count
	uint16_t falseClassificationCount = 0;//False Clustered count

	int confusionMatrix[6][6];//Class confusion matrix
	for (uint16_t i = 0; i < 6; i++)
	{
		for (uint16_t j = 0; j < 6; j++)
		{
			confusionMatrix[i][j] = 0;
		}
	}


	for (uint16_t i = 0; i < newBlobs.size(); i++) {
		for (uint16_t j = 0; j < newBlobs[i].size(); j++) {
			(newBlobs[i][j].cluster == newBlobs[i][j].features[FEATURE_COUNT - 1]) ? ++trueClassificationCount : ++falseClassificationCount;
			confusionMatrix[newBlobs[i][j].cluster][newBlobs[i][j].features[FEATURE_COUNT - 1]]++;
		}
	}

	std::cout << "True Classification Count : " << trueClassificationCount << std::endl;
	std::cout << "False Classification Count : " << falseClassificationCount << std::endl;

	std::cout << "Confusion Matrix : " << std::endl;
	std::cout << "\t";
	for (uint16_t i = 0; i < 6; i++)
	{
		std::cout << i << "\t";
	}

	std::cout << std::endl;
	for (uint16_t i = 0; i < 6; i++)
	{
		std::cout << i << "\t";
		for (uint16_t j = 0; j < 6; j++)
		{
			std::cout << confusionMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}


	getchar();
}

//Reading file line by line
void ReadFile(std::vector<std::vector<uint16_t>> &inputs, std::string filename) {

	std::string line;
	
	std::ifstream infile(filename);
	
	int inputCount = 0;
	
	while (std::getline(infile, line)) {
		
		int featureCount = 0;

		std::stringstream ss(line);

		std::string word;

		//Tokenizing line with ','
		while (std::getline(ss, word, ',')) {
			
			//All missing values in AGE feature
			//if any word is "?" , switch that value with pre computed AVARAGE AGE
			if (word == "?") {
				word = AVARAGE_AGE;
			}
			
			uint16_t input = std::atoi(word.c_str());

			inputs[inputCount][featureCount] = input;//Attach every value into the matrix

			featureCount++;
		}
		
		inputCount++;
	}
}

int main() {

	std::vector < std::vector<uint16_t>> inputs_matrix(INSTANCE_COUNT);
	
	std::string filename = "Dermatology.data.txt";
	
	for (uint16_t i = 0; i < INSTANCE_COUNT; i++) {
		inputs_matrix[i].resize(FEATURE_COUNT);
	}

	ReadFile(inputs_matrix, filename);//File reading
	
	TestNavieBayesClassification(inputs_matrix, K_FOLD_CROSS_VALIDATION);//Navie Bayes Classification

	std::vector<std::vector<Cluster_t>> blobs(INSTANCE_COUNT);//Cluster Data struct for Hierarchical Clustering
	
	//Write inputs into the Cluster Data struct
	for (uint16_t i = 0; i < inputs_matrix.size(); i++) {
		
		Cluster_t instance;
		
		instance.features.resize(FEATURE_COUNT);

		instance.index = i;

		for (uint16_t j = 0; j < inputs_matrix[i].size(); j++) {
			instance.features[j] = inputs_matrix[i][j];
		}
		
		blobs[i].push_back(instance);
	}

	HierarchicalClustering(blobs);//Hierarchical Clustering
	
	getchar();
	return 0;
}
