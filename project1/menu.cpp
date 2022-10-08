#include <iostream>
#include "menu.h"
using namespace std;
void main()
{
	int dieukien = 0;
	do
	{
		dieukien = chayMenu(luaChon(mainMenu()));
	} while (dieukien == 0);
	system("pause");
}
