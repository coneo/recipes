#include <string.h>
#include <stdio.h>

int main()
{
    char b[10] = "hello";
    char a[2];

    strncpy(a,b,2);
    printf("len a:%s\n", a);
    printf("len b:%s\n", b);
}
