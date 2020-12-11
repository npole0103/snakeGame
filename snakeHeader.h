#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

enum GameState {
	InitVeiw,
	GameStart,
	GameOver,
};

#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define UP 72