/*
This program illustrates how to use mutex to avoid race conditions.

Expected Output:
The total should be 2000000
The total sum is 2000000
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int sum;
    pthread_mutex_t mutex;
} shared_data_t;

void *increase_sum(void *arg)
{
    shared_data_t *data = (shared_data_t *)arg;
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&data->mutex);
        data->sum++;
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    shared_data_t data = { .sum = 0 }; // instance locale à main

    if (pthread_mutex_init(&data.mutex, NULL) != 0)
    {
        perror("mutex init failed");
        return 1;
    }

    int rc = pthread_create(&t1, NULL, &increase_sum, &data); // adresse de data, pas NULL
    if (rc != 0)
    {
        fprintf(stderr, "pthread_create failed: %s\n", strerror(rc));
        exit(1);
    }
    int rc2 = pthread_create(&t2, NULL, &increase_sum, &data);
    if (rc2 != 0)
    {
        fprintf(stderr, "pthread_create failed: %s\n", strerror(rc2));
        exit(1);
    }

    int rc3 = pthread_join(t1, NULL);
    if (rc3 != 0)
        fprintf(stderr, "pthread_join failed: %s\n", strerror(rc3));

    int rc4 = pthread_join(t2, NULL);
    if (rc4 != 0)
        fprintf(stderr, "pthread_join failed: %s\n", strerror(rc4));

    int rc5 = pthread_mutex_destroy(&data.mutex);
    if (rc5 != 0)
        fprintf(stderr, "pthread_mutex_destroy failed: %s\n", strerror(rc5));

    printf("The total should be 2000000\n");
    printf("The total sum is %d \n", data.sum);
    return 0;
}