#include "menu.h"
#include "Infor.h"
#include "ViewFolder.h"
#include <filesystem>

BYTE sector[512];
FAT32 fat32;
NTFS ntfs;

bool firstTimeRun = true;
int mainMenu()
{
	wstring diskName;
	std::cout << "Nhap o dia (vi du E): ";
	std::wcin >> diskName;
	diskName = L"\\\\.\\" + diskName + L":";
	LPCWSTR drive = diskName.c_str();
	readSector(drive, 0, sector);

	system("cls");
	std::cout << "......MENU CHINH......." << endl;
	std::cout << "0. Thoat!" << endl;
	std::cout << "1. In noi dung sector " << endl;
	std::cout << "2. In cay thu muc " << endl;
	std::cout << "3. Mo file " << endl;
	std::cout << "4. Doc thong tin tren phan vung FAT32 " << endl;
	std::cout << "5. Doc thong tin tren phan vung NTFS " << endl;
	return 6;
}
int luaChon(int x)
{
	int choose;
	do
	{
		std::cout << "Hay nhap chon lua !!!   ";
		cin >> choose;
		if (cin.fail())
		{
			choose = -1;
			cin.clear();
			cin.ignore();
		}
	} while (choose < 0 || choose > x);
	return choose;
}
int menu1()
{
	system("cls");
	std::cout << "......FAT32......." << endl;
	std::cout << "0. Thoat!" << endl;
	std::cout << "1. In thong tin boot sector " << endl;
	std::cout << "2. In thong tin RDET " << endl;
	std::cout << "3. Quay lai menu chinh" << endl;
	return 4;
}
int menu2()
{
	system("cls");
	std::cout << "......NTFS......." << endl;
	std::cout << "0. Thoat!" << endl;
	std::cout << "1. In noi dung partition boot sector " << endl;
	std::cout << "2. In noi dung master file table " << endl;
	std::cout << "3. Quay lai menu chinh" << endl;
	return 4;
}
int chayMenu(int choose)
{
	if (choose == 1)
	{
		//In noi dung sector
		printf("\n Boot Sector: \n");
		for (int i = 0; i < 512; i++) {
			if (i % 16 == 0)
				printf("\n");
			BYTE tmp = sector[i];
			printf("%c ", isascii(tmp) ? tmp : '.');
		}
	}
	else if (choose == 2)
	{
		//In cay thu muc
		std::wstring path;
		std::cout << "Nhap duong dan: ";
		std::wcin.ignore();
		getline(std::wcin, path);
		if (fs::exists(path)) {
			try {
				if (fs::is_directory(path)) {
					Folder root(path);
					std::cout << "Ten folder: " << root.getName() << '\n';
					std::cout << "Kich thuoc cua " << root.getName() << ": " << root.getSize() << " bytes\n";
					int q;
					std::cout << "-----------------------------------\n";
					std::cout << "1. Liet ke con truc tiep.\n";
					std::cout << "2. Liet ke tat ca con.\n";
					std::cout << "Nhap yeu cau (1->2): "; std::cin >> q;
					if (q == 1) root.showChildren(); else root.showAllChildren();
				}
				else {
					File root(path);
					std::cout << "Ten file: " << root.getName() << '\n';
					std::cout << "Kich thuoc cua " << root.getName() << ": " << root.getSize() << " bytes";
				}
			}
			catch (std::exception e) {
				std::cout << "Ten file con hoac folder con khong duoc la tieng Viet co dau\n";
			}
		}
		else {
			std::cout << "Duong dan khong ton tai\n";
		}
	}
	else if (choose == 3)
	{
		//Mo file

	}
	else if (choose == 4)
	{
		//Doc thong tin tren phan vung FAT32

		int dieukien = 0;
		do
		{
			dieukien = runMenu1(luaChon(menu1()));
			if (dieukien == 1)
				break;
		} while (dieukien == 0);
	}
	else if (choose == 5)
	{
		//Doc thong tin tren phan vung NTFS
		int dieukien = 0;
		do
		{
			dieukien = runMenu2(luaChon(menu2()));
			if (dieukien == 1)
				break;
		} while (dieukien == 0);
	}
	else if (choose == 0)
	{
		return xacNhanThoat();
	}
}
int runMenu1(int choose)
{
	if (choose == 0)
		return xacNhanThoat();
	else if (choose == 1)
	{
		//In thong tin boot sector
		inputBootsector(sector, fat32);
		//Đọc các thông tin được mô tả trong Boot Sector FAT
		cout << "++++++++++++++++++    THONG TIN BOOTSECTOR FAT    ++++++++++++++++++\n";
		outputInforBootSector(fat32);

	}
	else if (choose == 2)
	{
		//In thong tin RDET

		std::cout << endl;
	}
	else if (choose == 3)
	{
		chayMenu(luaChon(mainMenu()));
	}
}
int runMenu2(int choose)
{
	if (choose == 0)
		return xacNhanThoat();
	if (choose == 1)
	{
		//In noi dung partition boot sector
		inputPartitionBootsector(sector, ntfs);
		cout << "++++++++++++++++++    THONG TIN PARTITION BOOTSECTOR NTFS    ++++++++++++++++++\n";
		outputInforPartitionBootSector(ntfs);
	}
	if (choose == 2)
	{
		//In noi dung master file table

		std::cout << endl;
	}
	if (choose == 3)
	{
		chayMenu(luaChon(mainMenu()));
	}
	std::cout << endl;
}
int xacNhanThoat()
{
	std::cout << "Ban chac chan muon thoat chu ?? [y/n]";
	char kt;
	cin >> kt;
	if (kt == 'y' || kt == 'Y')
		return 1;
	else
		return 0;
}