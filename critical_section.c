#include <windows.h>
#include <stdio.h>

CRITICAL_SECTION cs;
int sum;

DWORD WINAPI kernel(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        EnterCriticalSection(&cs);
        sum = sum + 1;
        LeaveCriticalSection(&cs);
    }

    return 0;
}


int main()
{
    sum = 0;

    InitializeCriticalSection(&cs);

    HANDLE hThread1 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    DeleteCriticalSection(&cs);

    printf("sum = %d\n", sum);

    return 0;
}