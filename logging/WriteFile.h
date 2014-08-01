#pragma once
#include <string>

class WriteFile
{
public:
    WriteFile(std::string name);
    ~WriteFile();

    size_t write(const char* msg, const size_t line);

    void append(const char* msg, const size_t line);

    void flush();


private:

    FILE* fp;
};
