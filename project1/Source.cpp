
#include "Source.h"

int hexToDec(BYTE* sector, int offset, int len)
{
    int power = 0;
    int dec = 0;

    for (int i = offset; i < (offset + len); i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (sector[i] & 1) {
                dec += (int)pow(2, power);
            }
            sector[i] >>= 1;
            power++;
        }
    }
    return dec;
}
int readSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }
}

void inputBootsector(BYTE* sector, FAT32& f32)
{
    f32.bytePerSec = hexToDec(sector, 11, 2);
    f32.SC = hexToDec(sector, 13, 1);
    f32.SB = hexToDec(sector, 14, 2);
    f32.NF = hexToDec(sector, 16, 1);
    f32.SRDET = hexToDec(sector, 17, 2);
    f32.Sv = hexToDec(sector, 32, 4);
    f32.Sf = hexToDec(sector, 36, 4);
    f32.SR = f32.SRDET * 32 / 512;
    f32.Ss = f32.SB + f32.NF * f32.Sf + f32.SR;
    f32.firstSectorRDET = f32.SB + f32.NF * f32.Sf;
}

void outputInforBootSector(FAT32 f32)
{
    cout << "1. Loai FAT: FAT32";
    cout << "\n2. So Byte cho 1 sector: " << f32.bytePerSec;
    cout << "\n3. So Sector cho 1 cluster: " << f32.SC;
    cout << "\n4. So Sector cua BootSector (Sb): " << f32.SB;
    cout << "\n5. So bang FAT (NF): " << f32.NF;
    cout << "\n6. So Sector cho bang RDET: " << f32.SR;
    cout << "\n7. Tong so sector, kich thuoc Volume (Sv): " << f32.Sv;
    cout << "\n8. kich thuoc ban FAT: " << f32.Sf;
    cout << "\n9. Sector dau tien FAT1: " << f32.SB;
    cout << "\n10. Sector dau tien cua vung RDET: " << f32.firstSectorRDET;
    cout << "\n11. Sector dau tien cua vung Data: " << f32.Ss << "\n\n";
}


