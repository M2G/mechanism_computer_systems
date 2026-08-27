/*
This program creates a new thread by calling pthread_create() function,
and then the new thread executes the function print_message().
The program waits for the thread to finish execution using pthread_join()

Expected Output:
Hello from threads

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// just a function which prints statements
void *print_message(void *arg)
{
    printf("Hello from threads\n");
    return NULL;
}

int main()
{
    // variable to store the thread
    pthread_t t1;
    // thread creation
    if (pthread_create(&t1, NULL, &print_message, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }
    // wait for the child thread to join main thread
    printf("Main: waiting for thread to finish...\n");
    if (pthread_join(t1, NULL) != 0)
    {
        perror("pthread_join failed");
        return 1;
    }
    printf("Main: thread has finished, exiting.\n");
    return 0;
}