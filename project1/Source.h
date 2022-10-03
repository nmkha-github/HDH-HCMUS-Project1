#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <atlstr.h>

using namespace std;

struct FAT32 {
    int bytePerSec;          // 	Số byte của một Sector      (B - 2)
    int SC;       // 	Số Sector của một Cluster   (D - 1) 
    int SB;         // 	Số Sector của BootSector    (E - 2) 
    int NF;                 // 	Số bảng FAT                 (10 - 1)
    int SRDET;              // 	Số Entry của RDET           (11 - 2) 
    int SR;            // Kích thước RDET
    int Sv;            //  Kích thước Volume           (32 - 4) 
    int Sf;           //  Số Sector của một bảng FAT  (24 - 4) 
    int firstSectorRDET;            //  Sector đầu tiên của RDET
    int Ss;            //  Kich thuoc vung he thong
};

int hexToDec(BYTE*, int, int);
int readSector(LPCWSTR, int, BYTE sector[512]);

/* Phần của Bootsector */
void inputBootsector(BYTE*, FAT32&);
void outputInforBootSector(FAT32);