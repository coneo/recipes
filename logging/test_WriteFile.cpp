#include "WriteFile.h"

int main()
{
    WriteFile file("./test.file");

    char msg[32] = "hello logging";
    file.append(msg, sizeof(msg));
}
