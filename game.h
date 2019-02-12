#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "Board.h"
#include <string>

enum SIGN {SGN_RIGHT = '+', SGN_LEFT = '-'};

class Gra
{
	private:
		struct Gracz
		{
			std::string strImie;
			int nWon;
			int nLose;
			int nDraw;
			bool byl;
			pt::Point nPong;
			double nPunkty;
			int nSrednia;
			Gracz() { strImie = '0'; nWon = 0; nLose = 0; nDraw = 0; byl = false; nPong = 0; nPunkty = 0; nSrednia = 0;}
		};
		
		pt::Point nPunkt;
		int nPoziomTrudnosci;
		int nKoniec;
		int nTrybGry;
		char Kierunek[2];

		Gracz gracz1;
		Gracz gracz2;

		Plansza plansza;

	public:
		Gra();
		~Gra();
		
		bool StartGry();
		bool Ruch();
		bool KoniecGry();
		bool Losowanie();
		bool Start();
		void Sortowanie(int* aTablicaWynikow, int lewy, int prawy);
		bool Game();
};

#endif