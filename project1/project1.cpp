
#include "Source.h"

int main() {

	BYTE sector[512];
	FAT32 fat32;
	NTFS ntfs;
	readSector(L"\\\\.\\E:", 0, sector); //thay thế ổ đĩa thích hợp

	//inputBootsector(sector, fat32);
	////Đọc các thông tin được mô tả trong Boot Sector FAT
	//cout << "++++++++++++++++++    THONG TIN BOOTSECTOR FAT    ++++++++++++++++++\n";
	//outputInforBootSector(fat32);

	inputPartitionBootsector(sector, ntfs);
	//Đọc các thông tin được mô tả trong Boot Sector FAT
	cout << "++++++++++++++++++    THONG TIN PARTITION BOOTSECTOR NTFS    ++++++++++++++++++\n";
	outputInforPartitionBootSector(ntfs);

	system("pause");
	system("cls");
	return 0;
}