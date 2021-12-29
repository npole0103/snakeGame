#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

enum GameState {
	InitVeiw,
	Pause,
	GameStart,
	GameOver,
};

#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define UP 72

#define WIDTH 101
#define HEIGHT 29
#define MAXLEN 50

void gotoxy(int x, int y)
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//why set the 2*x? Because console size is 120 : 30 = x : y
// if I set the 1*x and 1*y, it would be UP and DOWN faster than LEFT and RIGHT