//============================================================================
// Name        : task2.cpp
// Author      : Gavrilov Denis
// Version     : Release
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

struct Point
{
	float x;
	float y;
};

struct Quadrangle
{
	Point a;
	Point b;
	Point c;
	Point d;
};

int readFromFileCountOfCoordinates(std::string name)
{
	int count=0;
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
			count++;
		}
	}
	fin.close();
	return count;
}

Quadrangle readFromFileToQuadrandle(std::string name)
{
	std::ifstream fin;
	std::string coord;
	int CoordOfPoint=1;
	Quadrangle quadrangle;
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
			while (iss>>coord)
			{
				switch (CoordOfPoint)
				{
					case 1:
						quadrangle.a.x=std::stof(coord);
						CoordOfPoint++;
						break;
					case 2:
						quadrangle.a.y=std::stof(coord);
						CoordOfPoint++;
						break;
					case 3:
						quadrangle.b.x=std::stof(coord);
						CoordOfPoint++;
						break;
					case 4:
						quadrangle.b.y=std::stof(coord);
						CoordOfPoint++;
						break;
					case 5:
						quadrangle.c.x=std::stof(coord);
						CoordOfPoint++;
						break;
					case 6:
						quadrangle.c.y=std::stof(coord);
						CoordOfPoint++;
						break;
					case 7:
						quadrangle.d.x=std::stof(coord);
						CoordOfPoint++;
						break;
					case 8:
						quadrangle.d.y=std::stof(coord);
						CoordOfPoint=1;
						break;
					default:
						break;
				}
			}
		}
	}
	fin.close();
	return quadrangle;
}

Point* readFromFileToCoords(std::string name, int count)
{
	Point *points=new Point[count];
	std::fstream fin;
	std::string coord;
	int countOfPoints=0;
	int flag=1;
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
			while (iss>>coord)
			{
				switch (flag)
				{
				case 1:
					points[countOfPoints].x=std::stof(coord);
					flag=2;
					break;
				case 2:
					points[countOfPoints].y=std::stof(coord);
					flag=1;
					countOfPoints++;
					break;
				default:
					break;
				}
			}
		}
	}
	fin.close();
	return points;
}

bool OnTheTop(Quadrangle quadrangle, Point point)
{
	if (((point.x==quadrangle.a.x) && (point.y==quadrangle.a.y))
			|| ((point.x==quadrangle.b.x) && (point.y==quadrangle.b.y))
			|| ((point.x==quadrangle.c.x) && (point.y==quadrangle.c.y))
			|| ((point.x==quadrangle.d.x) && (point.y==quadrangle.d.y)))
	{
		return true;
	}
	else return false;
}

Point vector(Point A, Point B)
{
	Point V;
	V.x=B.x-A.x;
	V.y=B.y-A.y;
	return V;
}

float PseudoScalarMul(Point A, Point B)
{
	float value;
	value=A.x*B.y-B.x*A.y;
	return value;
}

float ScalarMul(Point A, Point B)
{
	float value;
	value= A.x*B.x+A.y*B.y;
	return value;
}

bool OnTheSide(Quadrangle quadrangle, Point point)
{
	float psmAB = PseudoScalarMul(vector(quadrangle.a,quadrangle.b),vector(quadrangle.a,point));
	float psmBC = PseudoScalarMul(vector(quadrangle.b,quadrangle.c),vector(quadrangle.b,point));
	float psmCD = PseudoScalarMul(vector(quadrangle.c,quadrangle.d),vector(quadrangle.c,point));
	float psmDA = PseudoScalarMul(vector(quadrangle.d,quadrangle.a),vector(quadrangle.d,point));
	float smAB = ScalarMul(vector(point,quadrangle.a),vector(point,quadrangle.b));
	float smBC = ScalarMul(vector(point,quadrangle.b),vector(point,quadrangle.c));
	float smCD = ScalarMul(vector(point,quadrangle.c),vector(point,quadrangle.d));
	float smDA = ScalarMul(vector(point,quadrangle.d),vector(point,quadrangle.a));
	float d1=(quadrangle.b.x-quadrangle.a.x)*(point.y-quadrangle.a.y)-(point.x-quadrangle.a.x)*(quadrangle.b.y-quadrangle.a.y);
	float d2=(quadrangle.c.x-quadrangle.b.x)*(point.y-quadrangle.b.y)-(point.x-quadrangle.b.x)*(quadrangle.c.y-quadrangle.b.y);
	float d3=(quadrangle.d.x-quadrangle.c.x)*(point.y-quadrangle.c.y)-(point.x-quadrangle.c.x)*(quadrangle.d.y-quadrangle.c.y);
	float d4=(quadrangle.a.x-quadrangle.d.x)*(point.y-quadrangle.d.y)-(point.x-quadrangle.d.x)*(quadrangle.a.y-quadrangle.d.y);
	if (((d1==0) && (psmAB==0) && (smAB<=0)) || ((d2==0) && (psmBC==0) && (smBC<=0))
		|| ((d3 == 0) && (psmCD==0) && (smCD<=0)) || ((d4==0) && (psmDA==0) && (smDA<=0))) return true;
	else return false;
}

bool InsideQuad(Quadrangle quadrangle, Point point)
{
	float d1=(quadrangle.b.x-quadrangle.a.x)*(point.y-quadrangle.a.y)-(point.x-quadrangle.a.x)*(quadrangle.b.y-quadrangle.a.y);
	float d2=(quadrangle.c.x-quadrangle.b.x)*(point.y-quadrangle.b.y)-(point.x-quadrangle.b.x)*(quadrangle.c.y-quadrangle.b.y);
	float d3=(quadrangle.d.x-quadrangle.c.x)*(point.y-quadrangle.c.y)-(point.x-quadrangle.c.x)*(quadrangle.d.y-quadrangle.c.y);
	float d4=(quadrangle.a.x-quadrangle.d.x)*(point.y-quadrangle.d.y)-(point.x-quadrangle.d.x)*(quadrangle.a.y-quadrangle.d.y);
	if ((d1<0) &&(d2<0)&&(d3<0)&&(d4<0)) return true;
	else return false;
}

int* FindPointPositions(Quadrangle quadrangle, Point* points, int count)
{
	bool f1=false,f2=false,f3=false,f4=false;
	int *PointPositions = new int[count];
	for (int i=0;i<count;i++)
	{
		f1=OnTheTop(quadrangle,points[i]);
		f2=OnTheSide(quadrangle,points[i]);
		f3=InsideQuad(quadrangle,points[i]);
		if ((f1==false) && (f2==false) && (f3==false)) f4=true;
		else f4=false;
		if (f1) PointPositions[i]=0;
		else if (f2) PointPositions[i]=1;
		else if (f3) PointPositions[i]=2;
		else if (f4) PointPositions[i]=3;
	}
	return PointPositions;
}

int main(int argc, char *argv[])
{
	Quadrangle quadrangle=readFromFileToQuadrandle(argv[1]);
	int countOfPointsInFile=readFromFileCountOfCoordinates(argv[2]);
	Point *points = readFromFileToCoords(argv[2],countOfPointsInFile);
	int *PointPosition=FindPointPositions(quadrangle,points,countOfPointsInFile);
	for (int i=0;i<countOfPointsInFile;i++)
		cout<<PointPosition[i]<<"\n";
	return 0;
}
