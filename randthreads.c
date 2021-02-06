#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_VAL 100
#define NO_THREADS 10

HANDLE hSem1;
HANDLE hSem2;

int randomval;
DWORD WINAPI producer(LPVOID param)
{
    srand(time(0));
    while(1)
    {
        randomval = rand() % (MAX_VAL+1);
        ReleaseSemaphore(hSem1, 1, NULL);
        WaitForSingleObject(hSem2, INFINITE);
    }
}

int getrandom()
{
    WaitForSingleObject(hSem1, INFINITE);
    int val = randomval;
    ReleaseSemaphore(hSem2, 1, NULL);
    return val;
}

DWORD WINAPI kernel(LPVOID param)
{
    int val = getrandom();
    printf("%d\n", val);

    return 0;
}

int main()
{
    HANDLE hThreads[NO_THREADS];

    hSem1 = CreateSemaphore(NULL, 0, 1, NULL);
    hSem2 = CreateSemaphore(NULL, 0, 1, NULL);
    HANDLE hProd = CreateThread(NULL, 0, producer, NULL, 0, NULL);

    for (int i=0; i<NO_THREADS; i++)
    {
        hThreads[i] = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    }

    WaitForMultipleObjects(NO_THREADS, hThreads, TRUE, INFINITE);

    for (int i=0; i<NO_THREADS; i++)
    {
        CloseHandle(hThreads[i]);
    }
    CloseHandle(hProd);
    CloseHandle(hSem1);
    CloseHandle(hSem2);

    return 0;
}