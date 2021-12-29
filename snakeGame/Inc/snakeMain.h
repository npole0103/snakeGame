#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <gotoxy.h>

//πÊ«‚≈∞
#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define UP 72

//∏  ∆¯ ≥Ù¿Ã, πÏ √÷¥Î ±Ê¿Ã
#define WIDTH 101
#define HEIGHT 29
#define MAXLEN 50

using namespace std;

enum GameState {
	InitVeiw,
	Pause,
	GameStart,
	GameOver,
};

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
	void snakeMove(GameState* gameState, int* bestLen, int* bestSpeed, int* mode);
	void randomItem();
	void eatItem();
	void collisionCheck(GameState* gameState, int* bestLen, int* bestSpeed, int* mode);
	void printSnakeInfo(int* mode);
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