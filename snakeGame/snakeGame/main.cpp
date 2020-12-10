#pragma once
#include "snakeHeader.h"

class snake
{
public:


private:
	int headXpos;
	int headYpos;

};

class map
{
public:
	int getHeight();
	int getWidth();

	void setWidthHeight(int w, int h);
	void setMap();
	void printMap();

private:
	int h;
	int w;
	string** map;
};

int map::getHeight()
{
	return h;
}

int map::getWidth()
{
	return w;
}

void map::setWidthHeight(int width, int height)
{
	this->w = width;
	this->h = height;
}

void map::setMap()
{
	//allocating 2D-array https://blog.naver.com/dic1224/220975113201
	map = new string* [h];
	for (int i = 0; i < h; i++)
		map[i] = new string[w];

	//border setting
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			map[i][j] = ' ';

	//y border setting
	for (int i = 0; i < h; i++)
	{
		map[i][0] = '|';
		map[i][w - 1] = '|';
	}

	//x border setting
	for (int j = 0; j < w; j++)
	{
		map[0][j] = '=';
		map[h-1][j] = '=';
	}
}

void map::printMap()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			cout << map[i][j];
		
		cout << endl;
	}
}

int main()
{
	map m1;
	m1.setWidthHeight(120, 20);
	m1.setMap();
	m1.printMap();
}