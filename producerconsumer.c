#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE empty; // counts empty slots
HANDLE full;  // counts filled slots
HANDLE mutex; // for mutual exclusion

DWORD WINAPI producer(LPVOID arg) {
    int item = 0;
    while (1) {
        // Produce item
        int i = item++;

        WaitForSingleObject(empty, INFINITE); // wait for empty slot
        WaitForSingleObject(mutex, INFINITE); // enter critical section

        buffer[in] = i;
        printf("Produced: %d at buffer[%d]\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);         // leave critical section
        ReleaseSemaphore(full, 1, NULL); // signal that new item is available

        Sleep(1000); // simulate production time
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    int item;
    while (1) {
        WaitForSingleObject(full, INFINITE);  // wait for filled slot
        WaitForSingleObject(mutex, INFINITE); // enter critical section

        item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);          // leave critical section
        ReleaseSemaphore(empty, 1, NULL); // signal that a slot is free

        Sleep(2000); // simulate consumption time
    }
    return 0;
}

int main() {
    DWORD prodThreadId, consThreadId;

    // Create Windows semaphores and mutex
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL); // initial = BUFFER_SIZE, max = BUFFER_SIZE
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);            // initial = 0, max = BUFFER_SIZE
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Create producer and consumer threads
    HANDLE prodThread = CreateThread(NULL, 0, producer, NULL, 0, &prodThreadId);
    HANDLE consThread = CreateThread(NULL, 0, consumer, NULL, 0, &consThreadId);

    // Wait for threads (will never exit because while(1))
    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    // Cleanup (never reached in this infinite example)
    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);
    CloseHandle(prodThread);
    CloseHandle(consThread);

    return 0;
}