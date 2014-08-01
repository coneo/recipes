#include "WriteFile.h"
#include <stdio.h>
#include <sys/file.h>

WriteFile::WriteFile(std::string filename)
    : fp(::fopen(filename.c_str(), "a"))
{
}

WriteFile::~WriteFile()
{
    ::fclose(fp);
}

size_t WriteFile::write(const char* msg, const size_t len)
{
    flock(fileno(fp), LOCK_EX);
    return ::fwrite(msg, 1, len, fp);
    flock(fileno(fp), LOCK_UN);
}

void WriteFile::append(const char* msg, const size_t len)
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

void WriteFile::flush()
{
    ::fflush(fp);
}

