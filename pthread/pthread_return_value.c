/*
The program creates a new thread which calls the function return_value()
and stores the return value in main

Expected Output:
Returned Value: 100
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *return_value(void *arg)
{
    int *result = malloc(sizeof(int));
    if (result == NULL)
    {
        perror("malloc failed");
        return NULL;
    }
    *result = 100;
    return (void *)result;
}

int main()
{
    pthread_t t1;
    int *result;

    int rc1 = pthread_create(&t1, NULL, &return_value, NULL);
    if (rc1 != 0)
    {
        fprintf(stderr, "pthread_create failed: %s\n", strerror(rc1));
        return 1;
    }

    int rc2 = pthread_join(t1, (void **)&result);
    if (rc2 != 0)
    {
        fprintf(stderr, "pthread_join failed: %s\n", strerror(rc2));
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

    return 0;
}