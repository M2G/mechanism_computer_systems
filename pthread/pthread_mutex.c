#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERATIONS 1000000
#define NUM_THREADS 2

int sum = 0;
pthread_mutex_t mutex;

// fonction exécutée par chaque thread
void *increase_sum(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];

    // init du mutex
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("Erreur init mutex");
        return EXIT_FAILURE;
    }

    // création des threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, increase_sum, NULL) != 0)
        {
            perror("Erreur création thread");
            return EXIT_FAILURE;
        }
    }

    // attente des threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // destruction du mutex
    pthread_mutex_destroy(&mutex);

    printf("Total attendu : %d\n", ITERATIONS * NUM_THREADS);
    printf("Total obtenu  : %d\n", sum);

    return EXIT_SUCCESS;
}