#pragma once
#include "snakeHeader.h"

#define WIDTH 120
#define HEIGHT 30
#define MAXLEN 50

//����Ű �Է� ���� https://blog.naver.com/sharonichoya/220875372940

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
	void eatItem();
	int getKey();
	void setKey(int key);

private:
	//�� ��ǥ
	int xPos[MAXLEN];
	int yPos[MAXLEN];
	int snakeLen;
	int key; //���� �������

	//Item ��ǥ
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

	//���� ���� ��ó https://blog.naver.com/forcommang/221495736927
	cout << endl << endl << endl << endl;
	cout << "		����  ��     ��     ��    ��  �� ����   ����     ��    ��      ��  ����" << endl;
	cout << "		��      ���   ��   ��  ��  �� ��  ��      ��        ��  ��  ���  ���  ��	" << endl;
	cout << "		����  ��  �� ��  ��    �� ���   ����  ��  ��� ��    �� �� ��� ��  ����" << endl;
	cout << "		    ��  ��   ���  ����� �� ��  ��      ��    �� ����� ��  ��  ��  ��    " << endl;
	cout << "		����  ��     ��  ��    �� ��  �� ����   ����  ��    �� ��      ��  ����" << endl;
	

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

void Snake::initSnakeDraw()
{
	key = RIGHT;
	gotoxy(xPos[0], yPos[0]);
	cout << "��";

	for (int i = 1; i < snakeLen; i++)
	{
		gotoxy(xPos[i], yPos[i]);
		cout << "��";
	}
}

// snakeMove �޼ҵ� ���� https://blog.naver.com/whddnr746/221808605143
void Snake::snakeMove()
{
	//���� �κ� ����
	gotoxy(xPos[snakeLen - 1], yPos[snakeLen - 1]);
	cout << " ";

	//���� �Ծ��� �� �˻�
	eatItem();

	//�浹 �˻�

	for (int i = snakeLen - 1; i > 0; i--)
	{
		xPos[i] = xPos[i - 1];
		yPos[i] = yPos[i - 1];
	}
	//�Ӹ��κ� ����
	gotoxy(xPos[0], yPos[0]);
	cout << "��";

	switch (key)
	{
	case UP:
		--yPos[0];
		break;
	case DOWN:
		++yPos[0];
		break;
	case RIGHT:
		++xPos[0];
		break;
	case LEFT:
		--xPos[0];
		break;
	}
	gotoxy(xPos[0], yPos[0]);
	cout << "��";
}

void Snake::randomItem()
{
	bool quit = true;
	srand((unsigned int)time(NULL));

	while (quit)
	{
		itemxPos = (rand() % (WIDTH - 2)) + 1;
		itemyPos = (rand() % (HEIGHT - 2)) + 1;

		for (int i = 1; i < snakeLen; i++)
		{
			if (xPos[i] == itemxPos && yPos[i] == itemyPos)
				break;
			if (i == snakeLen - 1)
				quit = false;
		}
	}
	gotoxy(itemxPos, itemyPos);
	cout << "��";
}

void Snake::eatItem()
{
	if (xPos[0] == itemxPos && yPos[0] == itemyPos)
	{
		randomItem();
		if (snakeLen < MAXLEN - 1)
			snakeLen++;
	}
}

int Snake::getKey()
{
	return key;
}

void Snake::setKey(int key)
{
	this->key = key;
}

int main()
{
	Snake s1;
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
			s1.initSnakeDraw();
			s1.randomItem();
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
						// ȭ��ǥ ���� �޾��� ���� ���
						case UP:
						case DOWN:
						case RIGHT:
						case LEFT:
						
						//�ݴ� ���⿡ ���� ����ó��
							if ((s1.getKey() == UP && key == DOWN) || (s1.getKey() == DOWN && key == UP) ||
								(s1.getKey() == RIGHT && key == LEFT) || (s1.getKey() == LEFT && key == RIGHT))
								break;
						//key���� Snake�� �Ѱ���
							s1.setKey(key);
						}
					}
				}
				Sleep(100);
				s1.snakeMove();
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
