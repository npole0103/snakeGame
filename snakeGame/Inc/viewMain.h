#pragma once

#include <iostream>
#include <string>

#include <snakeMain.h>
#include <mapMain.h>
#include <gotoxy.h>

using namespace std;

void printSnakeText_1();
void printSnakeText_2();
void initVeiw(GameState* gameState, int* mode);
void gameoverVeiw(int* bestLen, int* bestSpeed);
void gameMain(Snake* s1, Map* m1, GameState* gameState, int* bestLen, int* bestSpeed, int* mode);