#pragma once
#include <iostream>
#include <string>
using namespace std;

class Map
{
public:
	int getHeight();
	int getWidth();

	void setWidthHeight(int w, int h);
	void setMap();
	void printMap();
	~Map(); //destructor

private:
	int h;
	int w;
	char** map;
};