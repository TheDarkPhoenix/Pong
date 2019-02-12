#include <conio.h>
#include <Windows.h>
#include <iostream>

#include "Board.h"

using namespace std;

Plansza::Plansza()
{
	CzyszczeniePlanszy();
}

Plansza::~Plansza()
{

}

void Plansza::gotoxy(int x,int y)
{
	COORD pos={x,y};
	HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleCursorPosition(out, pos);
}

bool Plansza::CzyszczeniePlanszy()
{
	for (int i = 0; i < nWymiarX; ++i)
		for (int j = 0; j < nWymiarY; ++j)
			aPlansza[i][j] = FLD_EMPTY;
	return true;
}

bool Plansza::RysujPlansze(int nPunkty1, int nPunkty2, string strImie1, string strImie2)
{
	system("cls");

	cout << ' ';
	for (int i = 0; i < nWymiarX; ++i)
		cout << '-';
	cout << endl;
	for (int i = 0; i < nWymiarY; ++i)
	{
		cout << '|';
		for (int j = 0; j < nWymiarX; ++j)
			cout << ' ';
		cout << '|' << endl;
	}
	cout << ' ';
	for (int i = 0; i < nWymiarX; ++i)
		cout << '-';
	gotoxy(nWymiarX/2 - 2, nWymiarY + 3);
	cout << nPunkty1;
	gotoxy(nWymiarX/2 + 2, nWymiarY + 3);
	cout << nPunkty2;
	gotoxy(1, nWymiarY + 2);
	cout << strImie1;
	gotoxy(nWymiarX - strImie2.length()+1, nWymiarY + 2);
	cout << strImie2;
	return true;
}

bool Plansza::CzyscPlansze(pt::Point nPunkt, pt::Point nPong1, pt::Point nPong2)
{
	gotoxy(nPunkt.x+1, nPunkt.y+1);
	cout << static_cast<char>(FLD_EMPTY);
	gotoxy(nPong1.x+1, nPong1.y+1);
	cout << static_cast<char>(FLD_EMPTY);
	gotoxy(nPong2.x+1, nPong2.y+1);
	cout << static_cast<char>(FLD_EMPTY);
	aPlansza[static_cast<int>(nPong1.x)][static_cast<int>(nPong1.y)] = FLD_EMPTY;
	aPlansza[static_cast<int>(nPong2.x)][static_cast<int>(nPong2.y)] = FLD_EMPTY;
	aPlansza[static_cast<int>(nPunkt.x)][static_cast<int>(nPunkt.y)] = FLD_EMPTY;
	return true;
}

bool Plansza::AktualizujPlansze(pt::Point nPunkt, pt::Point nPong1, pt::Point nPong2, int nPunkty1, int nPunkty2)
{
	gotoxy(nPunkt.x+1, nPunkt.y+1);
	cout << static_cast<char>(FLD_BALL);
	gotoxy(nPong1.x+1, nPong1.y+1);
	cout << static_cast<char>(FLD_PONG);
	gotoxy(nPong2.x+1, nPong2.y+1);
	cout << static_cast<char>(FLD_PONG);
	gotoxy(nWymiarX/2 - 2, nWymiarY + 3);
	cout << nPunkty1;
	gotoxy(nWymiarX/2 + 2, nWymiarY + 3);
	cout << nPunkty2;
	aPlansza[static_cast<int>(nPong1.x)][static_cast<int>(nPong1.y)] = FLD_PONG;
	aPlansza[static_cast<int>(nPong2.x)][static_cast<int>(nPong2.y)] = FLD_PONG;
	aPlansza[static_cast<int>(nPunkt.x)][static_cast<int>(nPunkt.y)] = FLD_BALL;
	return true;
}
int Plansza::SprawdzPlansze(pt::Point nPunkt)
{
	if (nPunkt.x < 0)
		return 2;
	else if (nPunkt.x > nWymiarX - 1)
		return 1;
	else if (nPunkt.y <= 0)
		return 3;
	else if (nPunkt.y >= nWymiarY - 1)
		return 4;
	return 0;
		
}