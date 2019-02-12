#ifndef BOARD_H
#define BOARD_H

#include "point.h"
#include <string>

enum FIELD {FLD_EMPTY = ' ', FLD_PONG = '|', FLD_BALL = '@'};

class Plansza
{
	private:
		static const int nWymiarX = 24;
		static const int nWymiarY = 10;
		

	public:
		Plansza();
		~Plansza();
		
		FIELD aPlansza [nWymiarX][nWymiarY];

		bool RysujPlansze(int nPunkty1, int nPunkty2, std::string strImie1, std::string strImie2);
		bool AktualizujPlansze(pt::Point nPunkt, pt::Point nPong1, pt::Point nPong2, int nPunkty1, int nPunkty2);
		int SprawdzPlansze(pt::Point nPunkt);
		bool CzyszczeniePlanszy();
		bool CzyscPlansze(pt::Point nPunkt, pt::Point nPong1, pt::Point nPong2);
		void gotoxy(int x,int y);
		pt::Point GetSize() const {return pt::PointMake(nWymiarX, nWymiarY);};
};

#endif