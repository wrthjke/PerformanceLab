//============================================================================
// Name        : task3.cpp
// Author      : Gavrilov Denis
// Version     : Release
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Cashbox
{
	double lengthOfQueue[16];
};

struct Magazine
{
	Cashbox cashboxes[5];
};

Cashbox readFromFileToCashbox(std::string name)
{
	Cashbox cashbox;
	string word;
	int counter=0;
	std::ifstream fin;
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
			istringstream iss(str);
			while (iss>>word)
			{
				cashbox.lengthOfQueue[counter]=std::stod(word);
				counter++;
			}
		}
	}
	fin.close();
	return cashbox;
}

int FindMax(Magazine magazine)
{
	double FromAllCashBox[16];
	for (int i=0;i<16;i++)
		FromAllCashBox[i]=0;
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<5;j++)
		{
			FromAllCashBox[i]=FromAllCashBox[i]+magazine.cashboxes[j].lengthOfQueue[i];
		}
	}
	double max=FromAllCashBox[0];
	int PosOfMax=0;
	for (int i=0;i<16;i++)
	{
		if (FromAllCashBox[i]>max) max=FromAllCashBox[i];
	}
	for (int i=0;i<16;i++)
	{
		if (FromAllCashBox[i]==max)
		{
			PosOfMax=i+1;
			break;
		}
	}
	return PosOfMax;
}

int main(int argc, char *argv[])
{
	Magazine magazine;
	Cashbox tempCashBox;
	for (int i=0;i<5;i++)
	{
		tempCashBox=readFromFileToCashbox(argv[i+1]);
		magazine.cashboxes[i]=tempCashBox;
	}
	cout<<FindMax(magazine);
	return 0;
}
