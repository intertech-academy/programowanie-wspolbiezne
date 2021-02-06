#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread1(LPVOID params)
{
    int offset = *((int*)params);

    for (int i = offset; i<offset+10; i++)
    {
        printf("%d\n",i);
    }

    return 0;
}

int main()
{
    int x = 2;
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, &x, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);
    CloseHandle(hThread1);

    return 0;
}