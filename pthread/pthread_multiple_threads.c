/*
This program creates shows how to create and join multiple threads
using a for loop.

Expected Output:
Hello from threads
Hello from threads
Thread ID 0 has finished
Thread ID 1 has finished
Thread ID 2 has finished
Thread ID 3 has finished
Hello from threads
Hello from threads
Hello from threads
Hello from threads
Hello from threads
Hello from threads
Thread ID 4 has finished
Thread ID 5 has finished
Thread ID 6 has finished
Thread ID 7 has finished
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 8 // number of threads

// just a function which prints statements
void *print_message(void *arg)
{
    int id = *(int *)arg;
    printf("Hello from thread %d\n", id);
    return NULL;
}

int main()
{
    // variable to store the thread
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS]; // skip malloc/free, tableau local

    // thread creation
    for (int i = 0; i < NUM_THREADS; i++)
    {
        ids[i] = i; // assign an ID to each thread
        if (pthread_create(&threads[i], NULL, &print_message, &ids[i]) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    // thread joining
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 1;
        }
        printf("Thread ID %d has finished\n", i);
    }

    return 0;
}