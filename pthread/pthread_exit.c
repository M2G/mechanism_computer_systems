/*
This program creates a new thread which calls the function return_value()
and stores the return value in main

Expected output:
Returned Value: 100
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// just a function which prints statements
void *return_value(void *arg)
{
    int *result = malloc(sizeof(int));
    if (result == NULL)
    {
        perror("malloc failed");
        pthread_exit(NULL);
    }
    *result = 100;
    pthread_exit((void *)result);
}

int main()
{
    // variable to store the thread
    pthread_t t1;
    int *result;
    // thread creation
    if (pthread_create(&t1, NULL, &return_value, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }
    // wait for the child thread to join main thread
    // and store the returned value in result
    if (pthread_join(t1, (void **)&result) != 0)
    {
        perror("pthread_join failed");
        return 1;
    }

    if (result != NULL)
    {
        printf("Returned Value: %d\n", *result);
        free(result);
    }
    else
    {
        printf("Thread failed to produce a result\n");
    }

    // destroy the result variable
    free(result);

    return 0;
}