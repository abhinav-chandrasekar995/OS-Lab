#include <stdio.h>
#include <windows.h>

#define N 5 // Number of philosophers

HANDLE forks[N]; // One mutex per fork
HANDLE philosophers[N];

DWORD WINAPI philosopher(LPVOID num) {
    int id = *(int*)num;
    int left = id;           // left fork index
    int right = (id + 1) % N; // right fork index

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        Sleep(1000); // Thinking (Sleep in ms)

        // To avoid deadlock, even IDs pick left then right, odd IDs pick right then left
        if (id % 2 == 0) {
            // Pick up left fork
            WaitForSingleObject(forks[left], INFINITE);
            printf("Philosopher %d picked up left fork %d.\n", id, left);

            // Pick up right fork
            WaitForSingleObject(forks[right], INFINITE);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
        } else {
            // Pick up right fork
            WaitForSingleObject(forks[right], INFINITE);
            printf("Philosopher %d picked up right fork %d.\n", id, right);

            // Pick up left fork
            WaitForSingleObject(forks[left], INFINITE);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        Sleep(2000); // Eating

        // Put down forks
        ReleaseMutex(forks[left]);
        ReleaseMutex(forks[right]);
        printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
    }

    return 0;
}

int main() {
    int ids[N];

    // Initialize forks (mutexes)
    for (int i = 0; i < N; i++) {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        philosophers[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

    // Wait for threads (will never exit because of while(1))
    WaitForMultipleObjects(N, philosophers, TRUE, INFINITE);

    // Cleanup (never reached)
    for (int i = 0; i < N; i++) {
        CloseHandle(forks[i]);
        CloseHandle(philosophers[i]);
    }

    return 0;
}