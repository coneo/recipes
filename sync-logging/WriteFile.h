#pragma once
#include <string>

class WriteFile
{
public:
    WriteFile(std::string name);
    ~WriteFile();

    void append(const char* msg, const size_t line);

    void flush();

private:
    size_t write(const char* msg, const size_t line);

    FILE* fp;
};
