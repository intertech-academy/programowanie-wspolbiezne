#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread1(LPVOID params)
{
    return 123;
}

int main()
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);

    DWORD ret;
    GetExitCodeThread(hThread1, &ret); //ret = GetExitCodeThread();

    printf("return value = %d\n", ret);
    CloseHandle(hThread1);
    return 0;
}