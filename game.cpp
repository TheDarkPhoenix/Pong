#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <string>
#include "game.h"

using namespace std;

Gra::Gra()
{
	nPunkt = 0;
	nPoziomTrudnosci = 0;
	nKoniec = 0;
	nTrybGry = 0;
	Kierunek[0] = 0;
	Kierunek[1] = 0;
}

Gra::~Gra()
{

}

void Gra::Sortowanie(int* aTablicaWynikow, int lewy, int prawy)
{
	int i,j,piwot;
	i = (lewy + prawy) / 2;
	piwot = aTablicaWynikow[i];
	aTablicaWynikow[i] = aTablicaWynikow[prawy];
	for(j = i = lewy; i < prawy; i++)
		if(aTablicaWynikow[i] < piwot)
		{
			swap(aTablicaWynikow[i], aTablicaWynikow[j]);
			j++;
		}
	aTablicaWynikow[prawy] = aTablicaWynikow[j];
	aTablicaWynikow[j] = piwot;
	if(lewy < j - 1) 
		Sortowanie(aTablicaWynikow, lewy, j - 1);
	if(j + 1 < prawy)
		Sortowanie(aTablicaWynikow, j + 1, prawy);
}

bool Gra::StartGry()
{
	cout << "Podaj imiê pierwszego gracza: ";
	cin >> gracz1.strImie;
	cout << "Podaj imiê drugiego gracza: ";
	cin >> gracz2.strImie;
	cout << "Podaj  poziom trudnoœci: " << endl;
	cout << "1. Bardzo ³atwy" << endl;
	cout << "2. £atwy" << endl;
	cout << "3. Œredni" << endl;
	cout << "4. Trudny" << endl;
	cout << "5. Bardzo trudny" << endl;
	cout << "6. Extreme" << endl;
	cin >> nPoziomTrudnosci;
	switch (nPoziomTrudnosci)
	{
		case 1:
			nPoziomTrudnosci *= 10;
			break;
		case 2:
			nPoziomTrudnosci *= 30;
			break;
		case 3:
			nPoziomTrudnosci *= 40;
			break;
		case 4:
			nPoziomTrudnosci *= 50;
			break;
		case 5:
			nPoziomTrudnosci *= 60;
			break;
		case 6:
			nPoziomTrudnosci *= 68;
			break;
	}
	cout << "Podaj maksymaln¹ liczbê punktów: ";
	cin >> nKoniec;
	gracz1.nPunkty = 0;
	gracz2.nPunkty = 0;
	plansza.CzyszczeniePlanszy();
	Start();
	Losowanie();
	plansza.RysujPlansze(gracz1.nPunkty, gracz2.nPunkty, gracz1.strImie, gracz2.strImie);
	return true;
}

bool Gra::Start()
{
	nPunkt.x = plansza.GetSize().x/2;
	nPunkt.y = plansza.GetSize().y/2;	//ustawienie pi³ki na œrodek planszy
	plansza.aPlansza[static_cast<int>(nPunkt.x)][static_cast<int>(nPunkt.y)] = FLD_BALL;
	gracz1.nPong.x = 0;
	gracz1.nPong.y = plansza.GetSize().y/2;
	gracz2.nPong.x = plansza.GetSize().x-1;
	gracz2.nPong.y = plansza.GetSize().y/2;
	plansza.aPlansza[static_cast<int>(gracz1.nPong.x)][static_cast<int>(gracz1.nPong.y)] = FLD_PONG;
	plansza.aPlansza[static_cast<int>(gracz2.nPong.x)][static_cast<int>(gracz2.nPong.y)] = FLD_PONG;
	return true;
}

bool Gra::Losowanie()
{
	srand (static_cast<unsigned>(time(NULL))); // losowanie w którym kierunku pi³ka ma na pocz¹tku pod¹rzaæ
	int i = rand() % 2 + 0;
	(i == 0 ? Kierunek[0] = '+' : Kierunek[0] = '-');
	int j = rand() % 2 + 0;
	(j == 0 ? Kierunek[1] = '+' : Kierunek[1] = '-');
	return true;
}

bool Gra::Ruch()
{
	plansza.CzyscPlansze(nPunkt, gracz1.nPong, gracz2.nPong);
	int j = plansza.SprawdzPlansze(nPunkt);
	if (j != 0)
	{
		if (j == 1)	// gracz nie odbi³ pi³ki
		{
			Start();
			plansza.RysujPlansze(gracz1.nPunkty, gracz2.nPunkty, gracz1.strImie, gracz2.strImie);
			++gracz1.nPunkty;
		}
		else if (j == 2)
		{
			Start();
			plansza.RysujPlansze(gracz1.nPunkty, gracz2.nPunkty, gracz1.strImie, gracz2.strImie);
			++gracz2.nPunkty;
		}
		else if (j == 3)	//jeœli pi³ka dotknê³a barierki ma zmieniæ kierunek
			Kierunek[1] = '+';
		else if (j == 4)
			Kierunek[1] = '-';
	}
	if ((nPunkt.x == gracz1.nPong.x && nPunkt.y == gracz1.nPong.y) || (nPunkt.x == gracz2.nPong.x && nPunkt.y == gracz2.nPong.y))
	{
		(Kierunek[0] == '+' ? Kierunek[0] = '-' : Kierunek[0] = '+');	//jeœli pi³ka odbije siê od paletki zmienia kierunek
	}
	if (gracz1.nPunkty >= nKoniec || gracz2.nPunkty >= nKoniec)
		return false;
	if (Kierunek[0] == '+') // aktualizowanie pozycji pi³ki
		++nPunkt.x;
	else if (Kierunek[0] == '-')
		--nPunkt.x;
	if (Kierunek[1] == '+')
		++nPunkt.y;
	else if (Kierunek[1] == '-')
		--nPunkt.y;
	while (kbhit())
	{
		char ch;
		ch = getch();
		switch (ch)
		{
			case 'w':
				if (gracz1.nPong.y > 0)
					--gracz1.nPong.y;
				break;
			case 's':
				if (gracz1.nPong.y < plansza.GetSize().y-1)
					++gracz1.nPong.y;
				break;
			case 72:
				if (gracz2.nPong.y > 0)
					--gracz2.nPong.y;
				break;
			case 80:
				if (gracz2.nPong.y < plansza.GetSize().y-1)
					++gracz2.nPong.y;
				break;
		}
	}
	plansza.AktualizujPlansze(nPunkt, gracz1.nPong, gracz2.nPong, gracz1.nPunkty, gracz2.nPunkty);
	Sleep(500 - nPoziomTrudnosci);
	return true;
}

bool Gra::KoniecGry()
{
	string strWygrany, strPrzegrany;
	int i = 0;
	system("cls");
	if (gracz1.nPunkty != gracz2.nPunkty)
	{	
		strWygrany = (gracz1.nPunkty > gracz2.nPunkty ? gracz1.strImie : gracz2.strImie);
		strPrzegrany = (gracz1.nPunkty < gracz2.nPunkty ? gracz1.strImie : gracz2.strImie);
		cout << "Wygra³ " << strWygrany << endl;
		i = 1;
	}
	else
		cout << "Remis!";
	fstream Ranking;
	Ranking.open("ranking.txt", ios::in | ios::out);
	int n = 0, a;
	if (Ranking.good())
		Ranking >> n;
	Gracz* ranking = new Gracz[n+2];
	a = n;
	switch (i)
	{
	case 1:
		if (Ranking.good())
		{
			int b[2] = {0};
			for (int i = 0; i < n; ++i)
			{
			if (!Ranking.eof())
			{
				Ranking >> ranking[i].strImie >> ranking[i].nWon >> ranking[i].nDraw >> ranking[i].nLose;
				//cout << ranking[i].strImie << ranking[i].nWon << ranking[i].nDraw << ranking[i].nLose;
				if (strWygrany == ranking[i].strImie)
					++ranking[i].nWon;
				else
					++b[0];
				if (strPrzegrany == ranking[i].strImie)
					++ranking[i].nLose;
				else
					++b[1];	
			}
			}
			if (b[0] == n)
			{
				ranking[n].strImie = strWygrany;
				ranking[n].nWon = 1;
				ranking[n].nDraw = 0;
				ranking[n].nLose = 0;
				++a;
			}
			if (b[1] == n)
			{
				ranking[n+1].strImie = strPrzegrany;
				ranking[n+1].nWon = 0;
				ranking[n+1].nDraw = 0;
				ranking[n+1].nLose = 1;
				++a;
			}
		}
		getch();
		break;
	case 0:
		if (Ranking.good())
		{
			int b[2] = {0};
			for (int i = 0; i < n; ++i)
			{
			if (!Ranking.eof())
			{
				Ranking >> ranking[i].strImie >> ranking[i].nWon >> ranking[i].nDraw >> ranking[i].nLose;
				if (gracz1.strImie == ranking[i].strImie)
					++ranking[i].nDraw;
				else
					++b[0];
				if (gracz2.strImie == ranking[i].strImie)
					++ranking[i].nDraw;
				else
					++b[1];

			}
			}
			if (b[0] == n)
			{
				ranking[n].strImie = gracz1.strImie;
				ranking[n].nWon = 0;
				ranking[n].nDraw = 1;
				ranking[n].nLose = 0;
				++a;
			}
			if (b[1] == n)
			{
				ranking[n+1].strImie = gracz2.strImie;
				ranking[n+1].nWon = 0;
				ranking[n+1].nDraw = 1;
				ranking[n+1].nLose = 0;
				++a;
			}
		}
		getch();
		break;
	}
	int* aTablicaWynikow = new int[a];
	Ranking.close();
	for (int i = 0; i < a; ++i)
	{
		if ((ranking[i].nDraw + ranking[i].nLose) != 0 && ranking[i].nWon)
			ranking[i].nSrednia = (ranking[i].nWon * 100) / (ranking[i].nDraw + ranking[i].nLose);
		else if (!ranking[i].nDraw && !ranking[i].nWon)
		{
			ranking[i].nSrednia = 0;
			ranking[i].nSrednia -= ranking[i].nLose;
		}
		else
			ranking[i].nSrednia = ranking[i].nWon * 100;
		aTablicaWynikow[i] = ranking[i].nSrednia;
		ranking[i].byl = false;
	}
	Sortowanie(aTablicaWynikow, 0, a);
	Ranking.open("ranking.txt", ios::in | ios::out | ios::trunc);
	Ranking << a << endl;
	for (int i = a; i >= 0; --i)
		for (int j = 0; j < a; ++j)
			if (aTablicaWynikow[i] == ranking[j].nSrednia && ranking[j].byl == false)
			{
				Ranking << ranking[j].strImie << ' ' << ranking[j].nWon << ' ' << ranking[j].nDraw << ' ' << ranking[j].nLose << endl;
				//cout << ranking[j].strImie << ' ' << ranking[j].nWon << ' ' << ranking[j].nDraw << ' ' << ranking[j].nLose << endl;
				ranking[j].byl = true;
				break;
			}
	Ranking.close();
	return true;
}

bool Gra::Game()
{
	int a = 0;
	bool b = true;
	for (;a != '-1';)
	{
		system("cls");
		cout << "Wybierz opcjê: " << endl;
		cout << "1. Nowa gra." << endl;
		cout << "2. Ranking. " << endl;
		cout << "-1. Wyjœcie. " << endl;
		cin >> a;
		switch (a)
		{
			case 1:
				{b = true;
				StartGry();
				while(b)
					b = Ruch();
				KoniecGry();
				getch();}
				break;
			case 2:
				{
				int n;
				system("cls");
				cout << "RANKING" << endl;
				cout << "--------------" << endl;
				fstream Ranking;
				Ranking.open("ranking.txt", ios::in | ios::out);
				string str;
				if (Ranking.good())
				{
					Ranking >> n;
					Ranking.seekg(2, ios::cur);
					for (int i = 1; i <= 10; ++i)
					{
						cout << i << ". ";
						if (!Ranking.eof())
						{
							getline(Ranking, str);
							cout << str;
						}
						cout << endl;	
					}
				}
				else
					cout << "B³¹d";
				getch();
				Ranking.close();
				break;
				}
			case -1:
				return true;
		}
	}
}