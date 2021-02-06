#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define PROD_TIME 500
#define CONS_TIME 300

#define QUEUE_SIZE 3
char data[QUEUE_SIZE+1];
int head_ptr = 1;
int tail_ptr = 0;

HANDLE hSemaphore;
HANDLE hSemaphoreQueue;
CRITICAL_SECTION cs;

void enqueue(char c)
{
    EnterCriticalSection(&cs);
    if (head_ptr == tail_ptr)
    {
        printf("\nError: Queue is full\n");
    }
    else
    {
        data[head_ptr] = c;
        head_ptr++;
        if (head_ptr == QUEUE_SIZE+1)
        {
            head_ptr = 0;
        }
    }
    LeaveCriticalSection(&cs);
}

char dequeue()
{
    char c;
    EnterCriticalSection(&cs);
    if ( ((tail_ptr+1) % (QUEUE_SIZE+1)) == head_ptr)
    {
        printf("\nError: Queue is empty\n");
        c = 0;
    }
    else
    {
        c = data[(tail_ptr+1) % (QUEUE_SIZE+1)];
        tail_ptr++;
        if (tail_ptr == QUEUE_SIZE+1)
        {
            tail_ptr = 0;
        }
    }
    LeaveCriticalSection(&cs);
    return c;
}

DWORD WINAPI producer(LPVOID params)
{
    char c = 'a';
    while(1)
    {
        int time = rand() % 2*PROD_TIME;
        Sleep(time);
        WaitForSingleObject(hSemaphoreQueue, INFINITE);
        enqueue(c);
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
        char c = dequeue();
        ReleaseSemaphore(hSemaphoreQueue, 1, NULL);
        Sleep(CONS_TIME);
        printf("%c,", c);
    }
    return 0;
}

int main()
{
    hSemaphore = CreateSemaphore(NULL, 0, QUEUE_SIZE, NULL);
    hSemaphoreQueue = CreateSemaphore(NULL, QUEUE_SIZE-1, QUEUE_SIZE, NULL);
    InitializeCriticalSection(&cs);

    HANDLE hProd = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    HANDLE hCons = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);

    CloseHandle(hProd);
    CloseHandle(hCons);
    CloseHandle(hSemaphore);
    CloseHandle(hSemaphoreQueue);
    DeleteCriticalSection(&cs);

    return 0;
}