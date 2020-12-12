#pragma once
#include "snakeHeader.h"

//메인화면 글자 뼈대 출처 https://blog.naver.com/forcommang/221495736927
//방향키 입력 참고 https://blog.naver.com/sharonichoya/220875372940
//snakeMove 메소드 참고 https://blog.naver.com/whddnr746/221808605143
//2차원 heap 메모리에 할당하는 법 https://blog.naver.com/dic1224/220975113201

//easy = 6 / normal = 4 / hard = 3
int mode = 4;
int bestLen = NULL;
int bestSpeed = NULL;

GameState gamestate = InitVeiw;

class Snake
{
public:
	Snake() //constructor
	{
		xPos[0] = 20; yPos[0] = 10;
		xPos[1] = 20; yPos[1] = 11;
		xPos[2] = 20; yPos[2] = 12;
		xPos[3] = 20; yPos[3] = 13;
		xPos[4] = 20; yPos[4] = 14;
		xPos[5] = 20; yPos[5] = 15;
		snakeLen = 6;
	}
	void initSnakeDraw();
	void snakeMove();
	void randomItem();
	void eatItem();
	void collisionCheck();
	void printSnakeInfo();
	void restart();

	//setter getter method
	int getSnakeLen();
	void setKey(int key);
	int getKey();
	int getxPos();
	int getyPos();
	int getItemxPos();
	int getItemyPos();

private:
	//snake coordinates, length and direction
	int xPos[MAXLEN];
	int yPos[MAXLEN];
	int snakeLen;
	int key = NULL;

	//item coordinates
	int itemxPos;
	int itemyPos;
};

void Snake::initSnakeDraw()
{
	//initialize direction RIGHT
	if (key == NULL)
		key = RIGHT;
	else //if key data is exist - PAUSE CASE
		key == getKey();

	//print the initial body
	for (int i = snakeLen - 1; i > 0; i--)
	{
		gotoxy(xPos[i], yPos[i]);
		cout << "○";
	}

	//head print
	gotoxy(xPos[0], yPos[0]);
	cout << "●";
}

void Snake::snakeMove()
{
	//erase the tail
	gotoxy(xPos[snakeLen - 1], yPos[snakeLen - 1]);
	cout << "  ";

	collisionCheck();

	eatItem();

	//push the coordinates forward one by one
	for (int i = snakeLen - 1; i > 0; i--)
	{
		xPos[i] = xPos[i - 1];
		yPos[i] = yPos[i - 1];
	}
	//current head coordinates is changed body coordinates
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
	//new head coordinates print
	gotoxy(xPos[0], yPos[0]);
	cout << "●";
}

void Snake::randomItem()
{
	//set the seed for random
	srand((unsigned int)time(NULL));

	bool quit = true;

	while (quit)
	{
		//console defalut size 120 / 30
		itemxPos = (rand() % (WIDTH / 2 - 2)) + 1;
		itemyPos = (rand() % (HEIGHT - 2)) + 1;

		for (int i = 1; i < snakeLen; i++)
		{
			//If the head coordinates and the body coordinates matched.
			if (xPos[i] == itemxPos && yPos[i] == itemyPos)
				break;
			//If there's nothing wrong with the tail.
			if (i == snakeLen - 1)
				quit = false; //while문 탈출
		}
	}
	gotoxy(itemxPos, itemyPos);
	cout << "★";

}

void Snake::eatItem()
{
	if (xPos[0] == itemxPos && yPos[0] == itemyPos)
	{
		this->randomItem();
		if (snakeLen < MAXLEN - 1)
			snakeLen++;
	}
}

void Snake::collisionCheck()
{
	//colliison the border 
	if (xPos[0] == WIDTH / 2 || xPos[0] == 0 || yPos[0] == HEIGHT - 1 || yPos[0] == 0)
	{
		if (bestLen == NULL && bestSpeed == NULL)
		{
			bestLen = snakeLen;
			bestSpeed = snakeLen / mode;
		}
		if (snakeLen >= bestLen)
			bestLen = snakeLen;
		if ((snakeLen / mode) == bestSpeed)
			bestSpeed = (snakeLen / mode);

		gamestate = GameOver;
	}

	//collision one's own body
	for (int i = 1; i < snakeLen; i++)
		if (xPos[0] == xPos[i] && yPos[0] == yPos[i])
		{
			if (bestLen == NULL && bestSpeed == NULL)
			{
				bestLen = snakeLen;
				bestSpeed = snakeLen / mode;
			}
			if (snakeLen >= bestLen)
				bestLen = snakeLen;
			if ((snakeLen / mode) == bestSpeed)
				bestSpeed = (snakeLen / mode);

			gamestate = GameOver;
		}
}

void Snake::printSnakeInfo()
{
	//current mode
	gotoxy(52, 4);
	if (mode == 6)
		cout << "Mode : Easy";
	else if (mode == 4)
		cout << "Mode : Normal";
	else if (mode == 3)
		cout << "Mode : Hard";

	//current snakeLen
	gotoxy(52, 7);
	cout << "SNAKE LEN : "<< snakeLen;

	//current speed
	gotoxy(52, 10);
	cout << "SPEED : " << (snakeLen/mode);

	//Restart
	gotoxy(52, 18);
	cout << "PAUSE : P";

	//Exit
	gotoxy(52, 20);
	cout << "EXIT : X";

	//block processing
	gotoxy(59, 29);
	cout << " ";
}

void Snake::restart()
{
	xPos[0] = 20; yPos[0] = 10;
	xPos[1] = 20; yPos[1] = 11;
	xPos[2] = 20; yPos[2] = 12;
	xPos[3] = 20; yPos[3] = 13;
	xPos[4] = 20; yPos[4] = 14;
	xPos[5] = 20; yPos[5] = 15;
	snakeLen = 6;
}

int Snake::getSnakeLen()
{
	return snakeLen;
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

int Map::getHeight()
{
	return h;
}

int Map::getWidth()
{
	return w;
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


//normal method
void printSnakeText_1()
{
	gotoxy(0, 0);

	cout << endl << endl << endl << endl;
	cout << "   		   ■■■  ■     ■     ■    ■  ■ ■■■   ■■■     ■    ■      ■  ■■■" << endl;
	cout << "   		   ■      ■■   ■   ■  ■  ■ ■  ■      ■        ■  ■  ■■  ■■  ■	" << endl;
	cout << "   		   ■■■  ■  ■ ■  ■    ■ ■■   ■■■  ■  ■■ ■    ■ ■ ■■ ■  ■■■" << endl;
	cout << "   		       ■  ■   ■■  ■■■■ ■ ■  ■      ■    ■ ■■■■ ■  ■  ■  ■    " << endl;
	cout << "   		   ■■■  ■     ■  ■    ■ ■  ■ ■■■   ■■■  ■    ■ ■      ■  ■■■" << endl;

	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "   					         Made by SU HEON KIM" << endl;
	cout << endl << endl << endl << endl << endl;
	cout << "                                             You Should Select the Mode" << endl << endl;
	cout << "                                          Easy : E / Normal : N / Hard : H" << endl << endl;
	cout << "   					  Press E or N or H key to keyboard" << endl;
}

void printSnakeText_2()
{
	gotoxy(0, 0);

	cout << endl << endl << endl << endl;
	cout << "   		   □□□  □     □     □    □  □ □□□   □□□     □    □      □  □□□" << endl;
	cout << "   		   □      □□   □   □  □  □ □  □      □        □  □  □□  □□  □	" << endl;
	cout << "   		   □□□  □  □ □  □    □ □□   □□□  □  □□ □    □ □ □□ □  □□□" << endl;
	cout << "   		       □  □   □□  □□□□ □ □  □      □    □ □□□□ □  □  □  □    " << endl;
	cout << "   		   □□□  □     □  □    □ □  □ □□□   □□□  □    □ □      □  □□□" << endl;

	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "   					         Made by SU HEON KIM" << endl;
	cout << endl << endl << endl << endl << endl;
	cout << "                                             You Should Select the Mode" << endl << endl;
	cout << "                                          Easy : E / Normal : N / Hard : H" << endl << endl;
	cout << "   					  Press E or N or H key to keyboard" << endl;
}

void initVeiw()
{
	while (1)
	{
		Sleep(150);
		printSnakeText_1();
		Sleep(150);
		printSnakeText_2();
		Sleep(150);
		if (_kbhit())
			break;
	}

	while (1)
	{
		int key;
		if (_kbhit())
		{
			key = _getch();

			if (key == 69 || key == 101) //easy mode
			{
				mode = 6;
				system("cls");
				gamestate = GameStart;
				break;
			}
			else if (key == 78 || key == 110) // normal mode
			{
				mode = 4;
				system("cls");
				gamestate = GameStart;
				break;
			}
			else if (key == 72 || key == 104) // hard mode
			{
				mode = 3;
				system("cls");
				gamestate = GameStart;
				break;
			}
			else
			{
				int a = _getch();
				//erase buffer
				//Because UP key is 224 + 72
				//If int a = _getch() is not exist, its program would excute hard mode accroding to 72
				continue;
			}
			
		}
	}

	Sleep(300);
}

void gameoverVeiw()
{
	gotoxy(24, 8);
	cout << "        GAMEOVER";

	gotoxy(24, 10);
	cout << "    Your Best Score";

	gotoxy(24, 12);
	cout << "     BEST Length : " << bestLen;

	gotoxy(24, 14);
	cout << "     BEST Speed : " << bestSpeed;

	gotoxy(24, 17);
	cout << "CONTINUE ? : R / EXIT : X";
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
		case Pause:
			while (1)
				if (_kbhit())
				{
					system("cls");
					gamestate = GameStart;
					int a = _getch();
					//erase buffer
					Sleep(300);
					break;
				}
		case GameStart:

			m1.printMap();
			s1.initSnakeDraw();
			s1.randomItem();
		
			while (1)
			{
				int key;

				if (_kbhit())
				{
					key = _getch();
					
					//direction key processing
					if (key == 224)
					{
						key = _getch();
						switch (key)
						{
						// UP || DOWN || RIGHT || LEFT is only pass this switch loop
						case UP:
						case DOWN:
						case RIGHT:
						case LEFT:

							//exception for opposite direction
							if ((s1.getKey() == UP && key == DOWN) || (s1.getKey() == DOWN && key == UP) ||
								(s1.getKey() == RIGHT && key == LEFT) || (s1.getKey() == LEFT && key == RIGHT))
								break;
							//set the direction for snake
							s1.setKey(key);
						}
					}
					//input X = EXIT
					else if (key == 88 || key == 120)
					{
						gamestate = GameOver;
						break;
					}
					//input P - PAUSE
					else if (key == 80 || key == 112)
					{
						gotoxy(52, 15);
						cout << "press any key";
						gamestate = Pause;
						break;
					}
				}
				Sleep(150/(s1.getSnakeLen()/mode));

				s1.snakeMove();
				s1.printSnakeInfo();

				if (gamestate == GameOver)
					break;
			}
			break;
		case GameOver:

			system("cls");

			gameoverVeiw();

			while (1)
			{
				int key;
				if (_kbhit())
				{
					key = _getch();

					//Restart
					if (key == 82 || key == 114)
					{
						s1.restart();
						s1.setKey(RIGHT);
						gamestate = InitVeiw;
						system("cls");
						break;
					}

					//Exit
					else if (key == 88 || key == 120)
					{
						exit(1);
					}
				}
			}

			break;
		}
	}

	return 0;
}
