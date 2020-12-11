#pragma once
#include "snakeHeader.h"

#define WIDTH 120
#define HEIGHT 30
#define MAXLEN 50

GameState gamestate = InitVeiw;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Snake
{
public:
	Snake() //constructor
	{
		xPos[0] = 60; yPos[0] = 15;
		xPos[1] = 59; yPos[1] = 15;
		xPos[2] = 58; yPos[2] = 15;
		xPos[3] = 57; yPos[3] = 15;
		snakeLen = 4;
	}
	void initSnakeDraw();
	void snakeMove();
	void randomItem();

private:
	//뱀 좌표
	int xPos[MAXLEN];
	int yPos[MAXLEN];
	int snakeLen;
	int key; //현재 진행방향

	//Item 좌표
	int itemxPos;
	int itemyPos;
};

class Map
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
	char** map;
};

int Map::getHeight()
{
	return h;
}

int Map::getWidth()
{
	return w;
}

void Map::setWidthHeight(int width, int height)
{
	this->w = width;
	this->h = height;
}

void Map::setMap()
{
	//allocating 2D-array https://blog.naver.com/dic1224/220975113201
	map = new char* [h];
	for (int i = 0; i < h; i++)
		map[i] = new char[w];

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

void Map::printMap()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			cout << map[i][j];
		cout << endl;
	}
}

void initVeiw()
{
	gotoxy(0, 0);

	//글자 뼈대 출처 https://blog.naver.com/forcommang/221495736927
	cout << endl << endl << endl << endl;
	cout << "		■■■  ■     ■     ■    ■  ■ ■■■   ■■■     ■    ■      ■  ■■■" << endl;
	cout << "		■      ■■   ■   ■  ■  ■ ■  ■      ■        ■  ■  ■■  ■■  ■	" << endl;
	cout << "		■■■  ■  ■ ■  ■    ■ ■■   ■■■  ■  ■■ ■    ■ ■ ■■ ■  ■■■" << endl;
	cout << "		    ■  ■   ■■  ■■■■ ■ ■  ■      ■    ■ ■■■■ ■  ■  ■  ■    " << endl;
	cout << "		■■■  ■     ■  ■    ■ ■  ■ ■■■   ■■■  ■    ■ ■      ■  ■■■" << endl;
	

	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "					   Made by SU HEON KIM" << endl;
	cout << endl << endl << endl << endl << endl << endl;
	cout << "					Press any key to keyboard" << endl;

	while (_kbhit())
	{
		system("cls");
		gamestate = GameStart;
		
		//erase buffer
		int a = _getch();
	}

	Sleep(300);
}

int main()
{
	Map m1;
	m1.setWidthHeight(WIDTH, HEIGHT);
	m1.setMap();

	while (1)
	{
		switch (gamestate)
		{
		case InitVeiw:
			initVeiw();
			break;
		case GameStart:
			m1.printMap();
			gotoxy(0, 0);

			//initSnakeDraw
			
			//snake
			while (1)
			{
				int key;

				if (_kbhit())
				{
					key = _getch();
					if (key == 224)
					{
						key = _getch();
						switch (key)
						{
						// 화살표 방향 받았을 때만 통과
						case UP:
						case DOWN:
						case RIGHT:
						case LEFT:
						
						//반대 방향에 대한 예외처리
						
						//key값을 Snake에 넘겨줌

						}
					}
				}

				Sleep(200);
				//snakeMove
			}
			break;
		case GameOver:
			cout << "gameover" << endl;
			break;
		}
	}

	//int key = _getch();
	//switch (key)
	//{
	//case RIGHT:
	//	cout << "right" << endl;
	//	break;
	//case LEFT:
	//	cout << "left" << endl;
	//	break;
	//case DOWN:
	//	cout << "down" << endl;
	//	break;
	//case UP:
	//	cout << "up" << endl;
	//	break;
	//}
}

void Snake::initSnakeDraw()
{
	gotoxy(xPos[0], yPos[0]);
	cout << "●";
	
	for (int i = 1; i < snakeLen; i++)
	{
		gotoxy(xPos[i], yPos[i]);
		cout << "○";
	}
}

void Snake::snakeMove()
{

}
