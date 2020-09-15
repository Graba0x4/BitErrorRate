#include <iostream>
#include <sstream>
#include <time.h>
#include <string.h>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include "log.h"

using namespace std;

const int BUFFOR_SIZE = (int)(1 << 10); //1024

string floatToString(float number)
{
    stringstream ss;
    string str;

    ss << number;
    ss >> str;
    ss.clear();

    return str;
}

void CreateFile(char *path, int _size)
{
    fstream file;
    file.open(path, ios::out);

    //LogToFile("Open file -> \" " + (string)path + " \" ");

    if (file.good() == true)
    {
        //ok
        for (int i = 0; i < _size; i++)
        {

            char r = rand() % 94 + 32;
            file << r;
        }
        //LogToFile("Add data to file successful! -> \" " + (string)path + " \" ");
        cout << "Add data to file successful!" << endl;
    }
    else
    {
        //rip
        //LogToFile("Error with file -> \" " + (string)path + " \" ");
        cout << "Error with file" << endl;
    }
    file.close();
}

long getFileSize(char *path)
{
    long start, stop;
    ifstream file(path);
    start = file.tellg();
    file.seekg(0, ios::end);
    stop = file.tellg();
    file.close();
    return (stop - start);
}

string CalcBitErorrRate(char *file_path1, char *file_path2)
{
    clock_t t1 = clock();
    long diff = 0,
         allbits = max(getFileSize(file_path1),
                       getFileSize(file_path2)) * 8;
    double BER = 0.0;
    double _time= 0.0;

    fstream file1;
    fstream file2;

    file1.open(file_path1, ios::in | ios::binary);
    file2.open(file_path2, ios::in | ios::binary);

    if (file1.good() == true && file2.good() == true)
    {
        char *buff = new char[BUFFOR_SIZE];
        char *buff2 = new char[BUFFOR_SIZE];


        while (!file1.eof() || !file2.eof())
        {
            memset(buff, 0, sizeof(buff));
            memset(buff2, 0, sizeof(buff2));

            file1.read(buff, BUFFOR_SIZE);
            file2.read(buff2, BUFFOR_SIZE);

            for (int i = 0; i < BUFFOR_SIZE; i++)
                {
                    bitset<8> test = (bitset<CHAR_BIT>(buff[i]) ^ bitset<CHAR_BIT>(buff2[i]));
                    string str = test.to_string();
                    diff += (count(str.begin(), str.end(), '1'));
                }
        }
        delete[] buff;
        delete[] buff2;
        file1.close();
        file2.close();
    }
    else
    {
        return "Can't get access to file!";
    }


    _time = ((double)((clock() - t1) / CLOCKS_PER_SEC));
    BER = (double)diff / allbits;

    stringstream ss;
    ss << "allbits:" << allbits << " | " << "diff:" << diff << " | "<< "BER:" << BER << " | " << "time:" << _time << "s";

    return ss.str();
}


int main()
{
    Log log;

    //CreateFile("test1.bin",1<<10);
    //CreateFile("test2.bin",1<<10);


    log.OpenLog();
    cout << CalcBitErorrRate("test1.bin","test2.bin") << endl;
    log.CloseLog();

    return 0;
}
