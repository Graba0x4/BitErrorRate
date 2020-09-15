#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class Log
{
    private:
    fstream Logfile;
    char *fileName;

    public:
    Log();
    Log(char *fileName);
    virtual ~Log();
    void OpenLog();
    void CloseLog();
    void LogToFile(char *message);
};

#endif // LOG_H
