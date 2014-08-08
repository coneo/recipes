#include "log_file.h"
#include <stdio.h>

using namespace water;

LogFile::LogFile(std::string filename)
    : fp(::fopen(filename.c_str(), "a"))
{
}

LogFile::~LogFile()
{
    ::fclose(fp);
}

size_t LogFile::write(const char* msg, const size_t len)
{
    return ::fwrite(msg, 1, len, fp);
}

void LogFile::append(const char* msg, const size_t len)
{
    size_t n = write(msg, len);
    size_t rest = len - n;
    while (rest)
    {
	size_t rt = write(msg + n, rest);
	if (0 == rt)
	{
	    int error = ferror(fp);
	    if (error)
		printf("append failed,error:%d\n",error);
	    break;
	}
	rest -= rt;
    }
}

void LogFile::flush()
{
    ::fflush(fp);
}

