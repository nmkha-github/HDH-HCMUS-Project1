#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using namespace std;

struct FAT32 {
    int bytePerSec;          // 	Số byte của một Sector
    int SC;       // 	Số Sector của một Cluster
    int SB;         // 	Số Sector của BootSector
    int NF;                 // 	Số bảng FAT 
    int SRDET;              // 	Số Entry của RDET
    int SR;            // Kích thước RDET
    int Sv;            //  Kích thước Volume
    int Sf;           //  Số Sector của một bảng FAT 
    int firstSectorRDET;            //  Sector đầu tiên của RDET
    int Ss;            //  Kich thuoc vung he thong
};

struct NTFS {
    int bytePerSec;             //  Số byte của một Sector 
    int SC;                     //  Số Sector của một Cluster
    int secPerTrack;            //  Số sector cho 1 track 
    int numberOf_Heads;         //  Số mặt đĩa 
    int totalSector;            //  Số Sector của ổ đĩa logic 
    int startSecDisk;           //  Sector bắt đầu của ổ đĩa logic
    int startCluster_MFT;       //  Cluster bắt đầu của MFT 
    int startCluster_MFTMirr;   //  Cluster bắt đầu của MFT dự phòng
    int sizeOf_MFTEntry;        //  Kích thước của 1 bản ghi trong MFT 
};

int hexToDec(BYTE*, int, int);
int readSector(LPCWSTR, int, BYTE sector[512], int count=512);

bool initListClusters(std::vector<uint64_t>& listClusters, uint64_t startCluster, BYTE sector[]);

// Bootsector FAT 32
void inputBootsector(BYTE*, FAT32&);
void outputInforBootSector(FAT32);

// Partition Bootsector NTFS
void inputBIOSparameterblock(BYTE*, NTFS&);
void outputInforBIOSparameterblock(NTFS);
