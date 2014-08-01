#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned long long size = 8ULL * 1024ULL * 1024ULL;
unsigned long long a[size];

void printnow()
{
    struct timeval tv;
    struct timezone tz;
    struct tm *tm;
    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);
    printf("%d:%02d:%02d %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec, (int)tv.tv_usec);
}

#ifdef TEST_IO_BUFFER1
int main()
{
    printnow();
    FILE *stream = fopen("./binary.f", "wb");
    for (int loop = 0; loop < 32; ++loop)
    {
	//fwrite(a, sizeof(unsigned long long), size, stream);
	fwrite(a, 1, sizeof(unsigned long long) * size, stream);
    }
    fclose(stream);
    printnow();
}
#endif

#ifdef TEST_IO_NOBUFFER2
#include <fcntl.h>
#include <unistd.h>
int main ()
{
    printnow();
    int data = open("./binary.f", O_WRONLY | O_CREAT, 0777);
    for (int loop = 0; loop < 32; ++loop)
    {
	write(data, a, size * sizeof(unsigned long long));
    }
    close(data);
    printnow();
}
#endif

#ifdef TEST_IO_NOBUFFER3
#include <fstream>

int main()
{
    printnow();
    std::ofstream file("./binary.f", std::ios::out | std::ios::binary);
    for (int loop = 0; loop < 32; ++loop)
    {
	file.write((char*)&a, size * sizeof(unsigned long long)) ;
    }
    file.close();
    printnow();
}
#endif
