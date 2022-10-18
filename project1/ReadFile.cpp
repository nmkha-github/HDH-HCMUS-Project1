#include "ReadFile.h"
#include "Infor.h"
#include "menu.h"
ATTRIBUTES::ATTRIBUTES(string name, int size, int level, int firstSector)
{
	this->size = size;
	this->level = level;
	this->firstSector = firstSector;
	this->name = name;
}

string ATTRIBUTES::getName()
{
	return this->name;
}

int ATTRIBUTES::getSize()
{
	return this->size;
}

string ATTRIBUTES::getType()
{
    string res = "";
    for (int i = this->name.size() - 1; this->name[i] != '.' && i >= 0; i--) res = this->name[i] + res;
    return res;
}

int ATTRIBUTES::getFirstSector()
{
	return this->firstSector;
}

void ATTRIBUTES::printID()
{
	std::cout << ATTRIBUTES::leveling(this->level) << this->name;
	if (this->size > 0)
		std::cout << " - Sector bat dau: " << this->firstSector;
	std::cout << std::endl;
}

string ATTRIBUTES::leveling(int level)
{
	string tab = "";
	for (int i = 0; i < level; i++)
		tab += "\t";
	return tab;
}

string byteToString(BYTE* DATA, int offset, int number)
{
    char* str = new char[number + 1];
    memcpy(str, DATA + offset, number);
    string res = "";
    for (int i = 0; i < number; i++)
        res += str[i];
    return res;
}

void readFile(FAT32 fat32, int startSector) {
    for (int i = 0; i < fat32.fileList.size(); i++)
        if (fat32.fileList[i].getFirstSector() == startSector)
        {
            if (fat32.fileList[i].getType() == ".txt" || fat32.fileList[i].getType() == ".TXT")
            {
                int size = fat32.fileList[i].getSize(), index = startSector;
                BYTE* data = new BYTE[size];
                std::cout << fat32.fileList[i].getName() << std::endl;
                std::cout << "** Noi dung file: ";
                while (size > 0)
                {
                    BYTE* DATA = new BYTE[512];
                    readSector(drive, index * 512, DATA);
                    std::cout << byteToString(DATA, 0, 512);
                    size -= 512;
                    index += 1;
                }
                std::cout << std::endl;
                return;
            }
            else
            {
                std::cout << fat32.fileList[i].getType() << std::endl;
                std::cout << "Khong the mo file nay." << std::endl;
                return;
            }
        }
    std::cout << "Khong tim thay tap tin." << std::endl;
}