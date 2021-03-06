#include "stdafx.h"
#include <random>
#include <numeric>
#include <iostream>

class coin
{
private:
	std::random_device rd;
	std::mt19937 mt;
	std::uniform_int_distribution<int> dist;

public:
	coin() : mt(rd()), dist(0,1) {	}

	int toss()
	{
		return dist(mt);
	}
	
};

constexpr int head = 0;
constexpr int tail = 1;

int main()
{
	coin cn;

	
	std::vector<int> Alice, Bob;
	
	for (int i=1; i<10000; i++)
	{
		// Alice tosses a coin until she sees a head followed by a tail
		int oldcoin = cn.toss();
		int tosses = 1;
		while (true)
		{		
			int newcoin = cn.toss();
			tosses++;
			if (oldcoin == head && newcoin == tail)
			{
				Alice.push_back(tosses);
				break;
			}
			oldcoin = newcoin;
		}

		//Bob tosses a coin until he sees two heads in a row
		oldcoin = cn.toss();
		tosses = 1;
		while (true)
		{
			int newcoin = cn.toss();
			tosses++;
			if (oldcoin == head && newcoin == head)
			{
				Bob.push_back(tosses);
				break;
			}
			oldcoin = newcoin;
		}
	}

	double bobMean = std::accumulate(Bob.begin(), Bob.end(), 0.0) / Bob.size();
	double aliceMean = std::accumulate(Alice.begin(), Alice.end(), 0.0) / Alice.size();
	
	std::cout << "Bob: " << bobMean << " Alice: " << aliceMean << std::endl;
    return 0;
}

