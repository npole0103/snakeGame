#include <snakeMain.h>

void Snake::initSnakeDraw()
{
	//initialize direction RIGHT
	if (key == NULL)
		key = RIGHT;

	//print the initial body
	for (int i = snakeLen - 1; i > 0; i--)
	{
		gotoxy(xPos[i], yPos[i]);
		cout << "¡Û";
	}

	//head print
	gotoxy(xPos[0], yPos[0]);
	cout << "¡Ü";
}

void Snake::snakeMove(GameState* gameState, int* bestLen, int* bestSpeed, int* mode)
{
	//erase the tail
	gotoxy(xPos[snakeLen - 1], yPos[snakeLen - 1]);
	cout << "  ";

	collisionCheck(gameState, bestLen, bestSpeed, mode);

	eatItem();

	//push the coordinates forward one by one
	for (int i = snakeLen - 1; i > 0; i--)
	{
		xPos[i] = xPos[i - 1];
		yPos[i] = yPos[i - 1];
	}
	//current head coordinates is changed body coordinates
	gotoxy(xPos[0], yPos[0]);
	cout << "¡Û";

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
	cout << "¡Ü";
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
				quit = false; //while loop break

			// this code is equal
			//quit = (i != (snakeLen - 1));
		}
	}
	gotoxy(itemxPos, itemyPos);
	cout << "¡Ú";

}

void Snake::eatItem()
{
	if (xPos[0] == itemxPos && yPos[0] == itemyPos)
	{
		this->randomItem();
		if (snakeLen < MAXLEN - 1)
			snakeLen++;

		//this code is equal
		//snakeLen += (snakeLen < MAXLEN - 1);
	}
}

void Snake::collisionCheck(GameState* gameState, int* bestLen, int* bestSpeed, int* mode)
{
	//colliison the border 
	if (xPos[0] == WIDTH / 2 || xPos[0] == 0 || yPos[0] == HEIGHT - 1 || yPos[0] == 0)
	{
		if (*bestLen == 0 && *bestSpeed == 0)
		{
			*bestLen = snakeLen;
			*bestSpeed = snakeLen / *mode;
		}
		if (snakeLen >= *bestLen)
			*bestLen = snakeLen;
		if ((snakeLen / *mode) == *bestSpeed)
			*bestSpeed = (snakeLen / *mode);

		*gameState = GameOver;
	}

	//collision one's own body
	for (int i = 1; i < snakeLen; i++)
		if (xPos[0] == xPos[i] && yPos[0] == yPos[i])
		{
			if (*bestLen == NULL && *bestSpeed == NULL)
			{
				*bestLen = snakeLen;
				*bestSpeed = snakeLen / *mode;
			}
			if (snakeLen >= *bestLen)
				*bestLen = snakeLen;
			if ((snakeLen / *mode) == *bestSpeed)
				*bestSpeed = (snakeLen / *mode);

			*gameState = GameOver;
		}
}

void Snake::printSnakeInfo(int* mode)
{
	//current mode
	gotoxy(52, 4);
	if (*mode == 6)
		cout << "Mode : Easy";
	else if (*mode == 4)
		cout << "Mode : Normal";
	else if (*mode == 3)
		cout << "Mode : Hard";

	//current snakeLen
	gotoxy(52, 7);
	cout << "SNAKE LEN : " << snakeLen;

	//current speed
	gotoxy(52, 10);
	cout << "SPEED : " << (snakeLen / *mode);

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