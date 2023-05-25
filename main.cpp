#include <iostream>
#include <vector>
#include <random>
#include <fstream>

void printVector(std::vector<int>& vec)
{
	for (int& iter : vec)
		std::cout << iter;
}
std::vector<int> sequenceGeneration()
{
	std::vector<int> vec;
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(0, 1);

	vec.reserve(128);
	for (int i = 0; i < 128; ++i)
	{
		vec.push_back(distribution(generator));
	}
	printVector(vec);
	std::ofstream file;
	file.open("/Users/aleksandragorbuncova/CLionProjects/isb-2/sequence.txt");
	if (file.is_open())
	{
		for (auto i : vec)
		{
			file << i;
		}
	}
	file.close();
	return vec;
}

float testFrequencyBit(std::vector<int>& sequence)
{
	double sum = 0;
	for (int i : sequence)
	{
		if (i == 1)
			++sum;
		else
			--sum;
	}
	sum = sum / sqrt(sequence.size());
	float result = erfc(sum / sqrt(2));
	return result;
}

int main()
{
	auto s = sequenceGeneration();
	std::cout << "\n" << testFrequencyBit(s);
	return 0;
}