#include <viewMain.h>

void printSnakeText_1()
{
	gotoxy(0, 0);

	cout << endl << endl << endl << endl;
	cout << "   		   бсбсбс  бс     бс     бс    бс  бс бсбсбс   бсбсбс     бс    бс      бс  бсбсбс" << endl;
	cout << "   		   бс      бсбс   бс   бс  бс  бс бс  бс      бс        бс  бс  бсбс  бсбс  бс	" << endl;
	cout << "   		   бсбсбс  бс  бс бс  бс    бс бсбс   бсбсбс  бс  бсбс бс    бс бс бсбс бс  бсбсбс" << endl;
	cout << "   		       бс  бс   бсбс  бсбсбсбс бс бс  бс      бс    бс бсбсбсбс бс  бс  бс  бс    " << endl;
	cout << "   		   бсбсбс  бс     бс  бс    бс бс  бс бсбсбс   бсбсбс  бс    бс бс      бс  бсбсбс" << endl;

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
	cout << "   		   брбрбр  бр     бр     бр    бр  бр брбрбр   брбрбр     бр    бр      бр  брбрбр" << endl;
	cout << "   		   бр      брбр   бр   бр  бр  бр бр  бр      бр        бр  бр  брбр  брбр  бр	" << endl;
	cout << "   		   брбрбр  бр  бр бр  бр    бр брбр   брбрбр  бр  брбр бр    бр бр брбр бр  брбрбр" << endl;
	cout << "   		       бр  бр   брбр  брбрбрбр бр бр  бр      бр    бр брбрбрбр бр  бр  бр  бр    " << endl;
	cout << "   		   брбрбр  бр     бр  бр    бр бр  бр брбрбр   брбрбр  бр    бр бр      бр  брбрбр" << endl;

	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "   					         Made by SU HEON KIM" << endl;
	cout << endl << endl << endl << endl << endl;
	cout << "                                             You Should Select the Mode" << endl << endl;
	cout << "                                          Easy : E / Normal : N / Hard : H" << endl << endl;
	cout << "   					  Press E or N or H key to keyboard" << endl;
}

void initVeiw(GameState* gameState, int* mode)
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
				*mode = 6;
				system("cls");
				*gameState = GameStart;
				break;
			}
			else if (key == 78 || key == 110) // normal mode
			{
				*mode = 4;
				system("cls");
				*gameState = GameStart;
				break;
			}
			else if (key == 72 || key == 104) // hard mode
			{
				*mode = 3;
				system("cls");
				*gameState = GameStart;
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

void gameoverVeiw(int* bestLen, int* bestSpeed)
{
	gotoxy(24, 8);
	cout << "        GAMEOVER";

	gotoxy(24, 10);
	cout << "    Your Best Score";

	gotoxy(24, 12);
	cout << "     BEST Length : " << *bestLen;

	gotoxy(24, 14);
	cout << "     BEST Speed : " << *bestSpeed;

	gotoxy(24, 17);
	cout << "CONTINUE ? : R / EXIT : X";
}

void gameMain(Snake* s1, Map* m1, GameState* gameState, int* bestLen, int* bestSpeed, int* mode)
{
	while (1)
	{
		switch (*gameState)
		{
		case InitVeiw:
			initVeiw(gameState, mode);
			break;
		case Pause:
			while (1)
				if (_kbhit())
				{
					system("cls");
					*gameState = GameStart;
					int a = _getch();
					//erase buffer
					Sleep(300);
					break;
				}
			break;
		case GameStart:

			m1->printMap();
			s1->initSnakeDraw();
			s1->randomItem();

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
							if ((s1->getKey() == UP && key == DOWN) || (s1->getKey() == DOWN && key == UP) ||
								(s1->getKey() == RIGHT && key == LEFT) || (s1->getKey() == LEFT && key == RIGHT))
								break;
							//set the direction for snake
							s1->setKey(key);
						}
					}
					//input X = EXIT
					else if (key == 88 || key == 120)
					{
						*gameState = GameOver;
						break;
					}
					//input P - PAUSE
					else if (key == 80 || key == 112)
					{
						gotoxy(52, 15);
						cout << "press any key";
						*gameState = Pause;
						break;
					}
				}
				Sleep(150 / (s1->getSnakeLen() / *mode));

				s1->snakeMove(gameState, bestLen, bestSpeed, mode);
				s1->printSnakeInfo(mode);

				if (*gameState == GameOver)
					break;
			}
			break;
		case GameOver:

			system("cls");

			gameoverVeiw(bestLen, bestSpeed);

			while (1)
			{
				int key;
				if (_kbhit())
				{
					key = _getch();

					//Restart
					if (key == 82 || key == 114)
					{
						s1->restart();
						s1->setKey(RIGHT);
						*gameState = InitVeiw;
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
}