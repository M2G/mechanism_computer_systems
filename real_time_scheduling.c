#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#define N 5

void* threadFn(void* arg)
{
    int id = *(int*)arg;

    // Param scheduling
    struct sched_param param;
    param.sched_priority = 80 + id;

    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0) {
        perror("pthread_setschedparam");
    }

    int policy;
    pthread_getschedparam(pthread_self(), &policy, &param);

    printf("Thread %d START (prio=%d)\n", id, param.sched_priority);

    // Simu. work
    for (int i = 0; i < 5; i++) {
        printf("Thread %d work (%d)\n", id, i);
        usleep(100000); // 100 ms
    }

    printf("Thread %d END\n", id);
    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("=== Test SCHED_FIFO ===\n");

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], &attr, threadFn, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    pthread_attr_destroy(&attr); // IMPORTANT destroy

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("=== Fin ===\n");
    return 0;
}