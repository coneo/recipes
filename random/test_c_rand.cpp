#include <stdlib.h>
#include <stdio.h>

int main()
{
    //test1
    //printf("%d\n", RAND_MAX);

    //test2
    /*
    for (int i = 1; i <=20; ++i)
    {
	printf("%d ", 1 + (rand() % 6));

	if (i % 5 == 0)
	    printf("\n");
    }
    */

    //test3
    unsigned int seed = 0;
    printf("enter seed: ");
    scanf("%u", &seed);

    srand(seed);
    for (int i = 0; i < 20; ++i)
    {
	printf("%d ", rand());

	if (i % 5 == 0)
	    printf("\n");
    }
    printf("\n");
}
