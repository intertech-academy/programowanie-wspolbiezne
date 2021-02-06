#include <stdio.h>
#include <windows.h>

HANDLE hMutex;

DWORD WINAPI kernel(LPVOID param)
{
    while(1)
    {
        WaitForSingleObject(hMutex, INFINITE);
        for (int i=0; i<10; i++)
        {
            printf("%d\n", i);
            Sleep(500);
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

int main()
{
    hMutex = CreateMutex(NULL, FALSE, TEXT("SharedMutex"));

    HANDLE hThread = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hMutex);

    return 0;
}