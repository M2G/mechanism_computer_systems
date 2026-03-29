#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fn(void* data)
{
    int nom = *(int*)data;

    for (int i = 0; i < 50; i++) {
        printf("Thread N%d %d\n", nom, i);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    int id1 = 1;
    int id2 = 2;

    pthread_create(&thread1, NULL, fn, &id1);
    pthread_create(&thread2, NULL, fn, &id2);

    for (int i = 0; i < 50; i++) {
        printf("Main thread %d\n", i);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}