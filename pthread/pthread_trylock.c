#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define NUM_THREADS 10

pthread_mutex_t mutex;

void *try_lock(void *arg)
{
    int threadID = *(int *)arg;

    // sleep aléatoire entre 0 et 2 secondes
    unsigned int seed = (unsigned int)time(NULL) ^ threadID; // seed différent par thread
    int sleeptime = rand_r(&seed) % 3;
    sleep(sleeptime);

    if (pthread_mutex_trylock(&mutex) == 0)
    {
        printf("Thread %d got the lock!\n", threadID);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Thread %d did not get the lock!\n", threadID);
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("mutex init failed");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int *x = malloc(sizeof(int));
        if (x == NULL)
        {
            perror("malloc failed");
            return 1;
        }
        *x = i;

        int rc = pthread_create(&threads[i], NULL, &try_lock, x);
        if (rc != 0)
        {
            fprintf(stderr, "pthread_create failed: %s\n", strerror(rc));
            free(x);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int rc = pthread_join(threads[i], NULL);
        if (rc != 0)
        {
            fprintf(stderr, "pthread_join failed: %s\n", strerror(rc));
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}