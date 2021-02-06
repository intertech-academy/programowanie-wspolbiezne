#include <windows.h>
#include <stdio.h>

int sum;

int flag = 1;

DWORD WINAPI kernel1(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        while(flag != 1);

        sum = sum + 1;
        flag = 2;
    }

    return 0;
}

DWORD WINAPI kernel2(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        while(flag != 2);

        sum = sum + 1;
        flag = 1;
    }

    return 0;
}


int main()
{
    sum = 0;

    HANDLE hThread1 = CreateThread(NULL, 0, kernel1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("sum = %d\n", sum);

    return 0;
}