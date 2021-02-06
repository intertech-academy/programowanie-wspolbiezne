#include <windows.h>
#include <stdio.h>

int flag = 1;

DWORD WINAPI kernel1(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        Sleep(1000);
        while(flag != 1);
        //Critical section
        printf("Thread1: %d\n", i);
        flag = 2;
    }

    return 0;
}

DWORD WINAPI kernel2(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        Sleep(10);
        while(flag != 2);
        //Critical section
        printf("Thread2: %d\n", i);
        flag = 1;
    }

    return 0;
}


int main()
{
    HANDLE hThread1 = CreateThread(NULL, 0, kernel1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    return 0;
}