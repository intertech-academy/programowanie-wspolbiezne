#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define PROD_TIME 500
#define CONS_TIME 500

char data = '@';

HANDLE hSemaphore;

DWORD WINAPI producer(LPVOID params)
{
    char c = 'a';
    while(1)
    {
        int time = rand() % 2*PROD_TIME;
        Sleep(time);
        data = c;
        ReleaseSemaphore(hSemaphore, 1, NULL);

        c++;
        if (c>'z')
        {
            c='a';
        }
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID params)
{
    while(1)
    {
        WaitForSingleObject(hSemaphore, INFINITE);
        char c = data;
        Sleep(CONS_TIME);
        printf("%c,", c);
    }
    return 0;
}

int main()
{
    hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);

    HANDLE hProd = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    HANDLE hCons = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);

    CloseHandle(hProd);
    CloseHandle(hCons);
    CloseHandle(hSemaphore);

    return 0;
}