#pragma once

#include <iostream>
#include <fstream>
#include <map>

class Logger
{
public:
    Logger(int pid);

    void log(unsigned long long code);

    void log(const char* data);

    ~Logger();
private:
    static std::map<unsigned long long, std::string> syscall_names;

    std::ofstream logFile;
    int pid;

    std::string getCurrentDatetime();
};