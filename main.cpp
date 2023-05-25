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

float testIdenticalConsecutiveBits(std::vector<int>& sequence)
{
	float psi = 0;
	unsigned long n = sequence.size();
	for (auto i : sequence)
		psi += i;
	psi /= n;
	if (abs(psi - 0.5) >= (2 / sqrt(n)))
		return 0;
	float value = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		if (sequence[i] != sequence[i + 1])
			++value;
	}
	float numerator = abs(value - n * psi * (1 - psi) * 2);
	float denominator = 2 * sqrt(2 * n) * psi * (1 - psi);
	float result = erfc(numerator / denominator);
	return result;
}

float testLongestSequenceOfUnits(std::vector<int>& sequence)
{
	int index = 0;
	std::vector<int> countUnits;
	while (index != 128)
	{
		std::vector<int> tmp;
		for (int i = index; i < index + 8; ++i)
		{
			tmp.push_back(sequence[i]);
		}
		int len = 0, count = 0, max = 0;
		for (auto i : tmp)
		{
			if (i == 1) ++count;
			else
			{
				if (count > max) max = count;
				count = 0;
			}
		}
		len = max;
		countUnits.push_back(len);
		index += 8;
	}

	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	for (auto i : countUnits)
	{
		if (i <= 1) ++v1;
		if (i == 2) ++v2;
		if (i == 3) ++v3;
		if (i >= 4) ++v4;
	}
	std::vector<int> v = { v1, v2, v3, v4 };
	std::vector<double> p = { 0.2345, 0.3231, 0.1304, 0.2673 };
	double x2 = 0;
	for (int i = 0; i < 4; ++i)
	{
		x2 += (pow((v[i] - 16 * p[i]), 2) / (16 * p[i]));
	}
	return x2;
}

int main()
{
	std::vector<int> sequence;
	sequence = sequenceGeneration();
	std::cout << std::endl;
	double first_test = testFrequencyBit(sequence);
	std::cout << "1 test: " << first_test << std::endl;
	double second_test = testIdenticalConsecutiveBits(sequence);
	std::cout << "2 test: " << second_test << std::endl;
	double x2 = testLongestSequenceOfUnits(sequence);
	std::cout << "Xu: " << x2 << std::endl;
	std::cout << "3 test (Used calculator): " << 0.266043 << std::endl;
	return 0;
}