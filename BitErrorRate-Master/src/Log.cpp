#include "Log.h"

Log::Log() : Log("log.txt")
{

}

Log::Log(char *fileName)
{
    this->fileName = fileName;
}

void Log::LogToFile(char *message)
{
    time_t t;
    time(&t);
    string data = ctime(&t);
    data.erase(data.length() - 1, data.length() - 1);
    Logfile << "[" << data << "]" << " - " << message << endl;
}

void Log::CloseLog()
{
    char *msg = "Close log file!\n\n\n";
    cout << msg << endl;
    LogToFile(msg);
    Logfile.close();
}

void Log::OpenLog()
{
    Logfile.open(fileName, ios::app);

    char* msg;

    if(Logfile.good() == true)
    {
        msg = "Open log file";
        LogToFile(msg);
        cout << msg << endl;
    }
    else
    {
        msg = "Can't open log file.";
        std::cerr << msg << endl;
    }
}




Log::~Log()
{
    //close file
    if(Logfile.is_open() == true)
    {
        CloseLog();
    }
}
