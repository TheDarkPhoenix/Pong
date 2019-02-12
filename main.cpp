/*
Copyright (c) 2019 Maciej Stępień
Licensed under the MIT license: 
http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <fstream>
#include <conio.h>
#include <locale>
#include "game.h"

using namespace std;

Gra gra;

locale myloc ("Polish");
locale oldloc = locale::global (myloc);

int main()
{
	gra.Game();
	return 0;
}