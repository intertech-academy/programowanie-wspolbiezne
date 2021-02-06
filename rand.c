#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 100

int main()
{
    srand(time(0));
    for (int i=0; i<10; i++)
    {
        int x = rand() % (MAX_VALUE+1);
        printf("%d\n", x);
    }

    return 0;
}