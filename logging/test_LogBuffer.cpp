#include "log_buffer.h"
#include <stdio.h>

using namespace water;

int main()
{
    LogBuffer<BIG_BUFFER_SIZE> buffer;

    char msg1[32] = "hello shok";
    buffer.put(msg1, sizeof(msg1));

    printf("str=%s,len=%u\n", buffer.data(), buffer.length());
}
