//============================================================================
// Name        : task1.cpp
// Author      : Gavrilov Denis
// Version     : Release
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>

std::vector<int> readFromFileToVector(std::string name)
{
	std::ifstream fin;
	std::vector<int> numbers;
	fin.open(name);
	if (!fin.is_open())
	{
		std::cout<<"Error!"<<std::endl;
	}
	else
	{
		std::string str;
		while (getline(fin,str))
		{
			if (str.size()==0) continue;
			int number = atoi(str.c_str());
			numbers.push_back(number);
		}
	}
	fin.close();
	return numbers;
}

double ninetypercentil(std::vector<int> numbers)
{
	double value,fraction,int_rank;
	int length=numbers.size();
	sort (numbers.begin(), numbers.end());
	double rank = (0.9 * (length-1.0))+1.0;
	fraction=modf(rank,&int_rank);
	int intrank=(int)int_rank;
	value=numbers[intrank-1]+fraction*(numbers[intrank]-numbers[intrank-1]);
	return value;
}

double mediana(std::vector<int>numbers)
{
	double value;
	sort (numbers.begin(), numbers.end());
	int length=numbers.size();
	int middle;
	if (length%2==0)
	{
		middle=length/2;
		value=(numbers[middle]+numbers[middle+1])/2.0;
	}
	else
	{
		middle=floor(length/2.0);
		value=numbers[middle];
	}
	return value;
}

double maxValue(std::vector<int> numbers)
{
	double max=numbers[0];
	int length=numbers.size();
	for (int i=0;i<length;i++)
	{
		if (numbers[i]>max) max=numbers[i];
	}
	return max;
}

double minValue(std::vector<int> numbers)
{
	double min=numbers[0];
	int length=numbers.size();
	for (int i=0;i<length;i++)
	{
		if (numbers[i]<min) min=numbers[i];
	}
	return min;
}

double middleValue(std::vector<int> numbers)
{
	int count=0;
	double sum=0;
	int length=numbers.size();
	for (int i=0;i<length;i++)
	{
		sum=sum+numbers[i];
		count++;
	}
	return sum/count;
}

int main(int argc, char *argv[])
{
	std::vector<int> numbers = readFromFileToVector(argv[1]);
	std::cout<<std::setprecision(2) << std::fixed<<ninetypercentil(numbers)<<"\n";
	std::cout<<std::setprecision(2) << std::fixed<<mediana(numbers)<<"\n";
	std::cout<<std::setprecision(2) << std::fixed<<maxValue(numbers)<<"\n";
	std::cout<<std::setprecision(2) << std::fixed<<minValue(numbers)<<"\n";
	std::cout<<std::setprecision(2) << std::fixed<<middleValue(numbers)<<"\n";
	return 0;
}
