
#include "Infor.h"
#include "ViewFolder.h"
#include "menu.h"
#include <filesystem>

int main() {
    
    int dieukien = 0;
    do
    {
        dieukien = chayMenu(luaChon(mainMenu()));
    } while (dieukien == 0);

	system("pause");
	return 0;
}