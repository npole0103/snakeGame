#pragma once
#include "stdafx.h"

//메인화면 글자 뼈대 출처 https://blog.naver.com/forcommang/221495736927
//방향키 입력 참고 https://blog.naver.com/sharonichoya/220875372940
//snakeMove / gotoxy 메소드  참고 https://blog.naver.com/whddnr746/221808605143
//2차원 배열 heap 메모리에 할당하는 법 https://blog.naver.com/dic1224/220975113201

int main()
{
	//easy = 6 / normal = 4 / hard = 3
	int* mode = new int; *mode = 4;
	int* bestLen = new int; *bestLen = 0;
	int* bestSpeed = new int; *bestSpeed = 0;

	GameState* gameState = new GameState();
	Snake* s1 = new Snake();
	Map* m1 = new Map();

	m1->setWidthHeight(WIDTH, HEIGHT);
	m1->setMap();

	gameMain(s1, m1, gameState, bestLen, bestSpeed, mode);

	delete mode;
	delete bestLen;
	delete bestSpeed;
	delete gameState;
	delete s1;
	delete m1;

	return 0;
}
