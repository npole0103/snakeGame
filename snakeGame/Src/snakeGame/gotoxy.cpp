#include <gotoxy.h>

void gotoxy(int x, int y)
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//why set the 2*x? Because console size is 120 : 30 = x : y
//If I set the 1*x and 1*y, It would be UP and DOWN faster than LEFT and RIGHT