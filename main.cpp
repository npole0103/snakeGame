#pragma once
#include "snakeHeader.h"

#define WIDTH 120
#define HEIGHT 30
#define MAXLEN 50

//방향키 입력 참고 https://blog.naver.com/sharonichoya/220875372940

GameState gamestate = InitVeiw;

void gotoxy(int x, int y)
{
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Snake
{
public:
	Snake() //constructor
	{
		xPos[0] = 20; yPos[0] = 10;
		xPos[1] = 20; yPos[1] = 11;
		xPos[2] = 20; yPos[2] = 12;
		xPos[3] = 20; yPos[3] = 13;
		snakeLen = 4;
	}
	void initSnakeDraw();
	void snakeMove();
	void randomItem();
	void eatItem();
	int getKey();
	int getxPos();
	int getyPos();
	int getItemxPos();
	int getItemyPos();
	void setKey(int key);

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

void Snake::initSnakeDraw()
{
	//초기 오른쪽 진행
	key = RIGHT;

	//몸통 출력
	for (int i = snakeLen - 1; i > 0; i--)
	{
		gotoxy(xPos[i], yPos[i]);
		cout << "○";
	}

	//머리 출력
	gotoxy(xPos[0], yPos[0]);
	cout << "●";
}

// snakeMove 메소드 참고 https://blog.naver.com/whddnr746/221808605143
void Snake::snakeMove()
{
	//꼬리 부분 제거
	gotoxy(xPos[snakeLen - 1], yPos[snakeLen - 1]);
	cout << "  ";

	//먹이 먹었을 때 검사
	eatItem();

	//충돌 검사

	for (int i = snakeLen - 1; i > 0; i--)
	{
		xPos[i] = xPos[i - 1];
		yPos[i] = yPos[i - 1];
	}
	//현재 머리부분 몸통
	gotoxy(xPos[0], yPos[0]);
	cout << "○";

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
	//바뀐 머리 좌표로 머리 출력
	gotoxy(xPos[0], yPos[0]);
	cout << "●";
}

void Snake::randomItem()
{
	bool quit = true;
	srand((unsigned int)time(NULL));

	while (quit)
	{
		itemxPos = (rand() % (WIDTH/2 - 2)) + 1;
		itemyPos = (rand() % (HEIGHT - 2)) + 1;

		for (int i = 1; i < snakeLen; i++)
		{
			//몸통과 좌표가 겹친다면
			if (xPos[i] == itemxPos && yPos[i] == itemyPos)
				break;
			//몸통 검사 부분 if문 맨 마지막이라면
			if (i == snakeLen - 1)
				quit = false; //while문 탈출
		}
	}
	gotoxy(itemxPos, itemyPos);
	cout << "■■";

}

void Snake::eatItem()
{
	//일반적으로 아이템을 먹었을 때
	if (xPos[0] == itemxPos && yPos[0] == itemyPos)
	{
		this->randomItem();
		if (snakeLen < MAXLEN - 1)
			snakeLen++;
	}
}

int Snake::getKey()
{
	return key;
}

int Snake::getxPos()
{
	return xPos[0];
}

int Snake::getyPos()
{
	return yPos[0];
}

int Snake::getItemxPos()
{
	return itemxPos;
}

int Snake::getItemyPos()
{
	return itemyPos;
}

void Snake::setKey(int key)
{
	this->key = key;
}

int main()
{
	Snake s1;
	//Map m1;
	//m1.setWidthHeight(WIDTH, HEIGHT);
	//m1.setMap();

	while (1)
	{
		switch (gamestate)
		{
		case InitVeiw:
			initVeiw();
			break;
		case GameStart:
			//m1.printMap();
			s1.initSnakeDraw();
			s1.randomItem();
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
							if ((s1.getKey() == UP && key == DOWN) || (s1.getKey() == DOWN && key == UP) ||
								(s1.getKey() == RIGHT && key == LEFT) || (s1.getKey() == LEFT && key == RIGHT))
								break;
						//key값을 Snake에 넘겨줌
							s1.setKey(key);
						}
					}
				}
				Sleep(200);
				s1.snakeMove();

				gotoxy(10, 25);
				cout << "item x : "<< s1.getItemxPos();
				cout << "item y : "<< s1.getItemyPos();
				cout << "head x : " << s1.getxPos();
				cout << "head y : " << s1.getyPos();
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
