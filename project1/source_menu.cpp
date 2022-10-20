#include "menu.h"
#include "Infor.h"
#include "ViewFolder.h"
#include <filesystem>

BYTE sector[512];
FAT32 fat32;
NTFS ntfs;
wstring diskName;
BYTE* FAT;
BYTE* BootSector;

bool firstTimeRun = true;
int mainMenu()
{
	system("cls");

	bool isError = true;
	do {
		std::cout << "Nhap o dia (vi du E): ";
		std::wcin >> diskName;
		diskName = L"\\\\.\\" + diskName + L":";
		LPCWSTR drive = diskName.c_str();
		isError = readSector(drive, 0, sector);
		if (isError) {
			system("cls");
			std::cout << "Khong tim thay o dia moi nhap lai\n";
		}
	} while (isError);
	
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
	std::cout << "1. In noi dung BIOS parameter block " << endl;
	std::cout << "2. In noi dung master file table " << endl;
	std::cout << "3. Quay lai menu chinh" << endl;
	return 4;
}

string numToHexString(int num, bool c) {
	string res = c ? "000001" : "000000";
	if (num < 10) {
		res += char(num + '0');
		res += "0  ";
	}
	else {
		res += char(num - 10 + 'A');
		res += "0  ";
	}
	return res;
}

int chayMenu(int choose)
{
	if (choose == 1)
	{
		//In noi dung sector	
		int count = 0;
		int num = 0;
		std::cout << "\n--------------------------------------------------------------------------------------------\n";
		std::cout << "Offset       0  1  2  3  4  5  6  7    8  9  A  B  C  D  E  F" << std::endl;
		std::cout << "000000" << num << "0  ";
		bool flag = 0;
		for (int i = 0; i < 512; i++)
		{
			count++;
			if (!(i % 8)) {
				printf("  ");
			}
			printf("%02X ", sector[i]);
			if (i == 255)
			{
				flag = 1;
				num = 0;
			}
			if (i == 511) break;
			if (count == 16)
			{
				printf("\n");

				if (flag == 0)
				{
					num++;
					std::cout << numToHexString(num, 0);
				}
				else
				{
					std::cout << numToHexString(num, 1);
					num++;
				}

				count = 0;
			}
		}
		printf("\n"); system("pause");
	}
	else if (choose == 2)
	{
		//In cay thu muc
		std::wstring path;
		std::cout << "Cac vi du duong dan hop le:\n";
		std::cout << "1. E:\n";
		std::cout << "2. E:\\Folder1\n";
		std::cout << "3. E:\\Folder1\\folder2\\file.txt\n";
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
		system("pause");
	}
	else if (choose == 3)
	{
		//Mo file
		

		system("pause");
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
	return 0;
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
		printf("\n"); system("pause");

	}
	else if (choose == 2)
	{
		//In thong tin RDET

		std::cout << endl;
		system("pause");
	}
	else if (choose == 3)
	{
		chayMenu(luaChon(mainMenu()));
	}
	return 0;
}
int runMenu2(int choose)
{
	if (choose == 0)
		return xacNhanThoat();
	if (choose == 1)
	{
		//In noi dung partition boot sector
		inputBIOSparameterblock(sector, ntfs);
		cout << "++++++++++++++++++    THONG TIN BIOS parameter block    ++++++++++++++++++\n";
		outputInforBIOSparameterblock(ntfs);
		printf("\n"); system("pause");
	}
	if (choose == 2)
	{
		//In noi dung master file table

		std::cout << endl;
		system("pause");
	}
	if (choose == 3)
	{
		chayMenu(luaChon(mainMenu()));
	}
	std::cout << endl;
	return 0;
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