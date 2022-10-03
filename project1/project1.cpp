
#include "Source.h"

int main() {

	BYTE sector[512];
	FAT32 fat32;
	readSector(L"\\\\.\\E:", 0, sector); //thay thế ổ đĩa thích hợp

	inputBootsector(sector, fat32);

	//Đọc các thông tin được mô tả trong Boot Sector
	cout << "++++++++++++++++++    THONG TIN BOOT SECTOR     ++++++++++++++++++\n";
	outputInforBootSector(fat32);

	system("pause");
	system("cls");
	return 0;
}