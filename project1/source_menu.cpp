#include "menu.h"
int mainMenu()
{
	system("cls");
	cout << "......MENU CHINH......." << endl;
	cout << "0. Thoat!" << endl;
	cout << "1. In noi dung sector " << endl;
	cout << "2. In cay thu muc " << endl;
	cout << "3. Mo file " << endl;
	cout << "4. Doc thong tin tren phan vung FAT32 " << endl;
	cout << "5. Doc thong tin tren phan vung NTFS " << endl;
	return 6;
}
int luaChon(int x)
{
	int choose;
	do
	{
		cout << "Hay nhap chon lua !!!   ";
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
	cout << "......FAT32......." << endl;
	cout << "0. Thoat!" << endl;
	cout << "1. In thong tin boot sector " << endl;
	cout << "2. In thong tin RDET " << endl;
	cout << "3. Quay lai menu chinh" << endl;
	return 4;
}
int menu2()
{
	system("cls");
	cout << "......NTFS......." << endl;
	cout << "0. Thoat!" << endl;
	cout << "1. In noi dung partition boot sector " << endl;
	cout << "2. In noi dung master file table " << endl;
	cout << "3. Quay lai menu chinh" << endl;
	return 4;
}
int chayMenu(int choose)
{
	if (choose == 1)
	{
	//In noi dung sector
	
	}
	else if (choose == 2)
	{
		//In cay thu muc
		
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
			system("pause");
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
			system("pause");
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

		cout << endl;
	}
	else if (choose == 2)
	{
		//In thong tin RDET

		cout << endl;
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

		cout << endl;
	}
	if (choose == 2)
	{
		//In noi dung master file table

		cout << endl;
	}
	if (choose == 3)
	{
		chayMenu(luaChon(mainMenu()));
	}
	cout << endl;
}
int xacNhanThoat()
{
	cout << "Ban chac chan muon thoat chu ?? [y/n]";
	char kt;
	cin >> kt;
	if (kt == 'y' || kt == 'Y')
		return 1;
	else
		return 0;
}