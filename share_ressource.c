#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// pas prévisible = situation de compétition
void* read(void* data)
{
    int* value = data;

    for (int i = 0; i < 10; i++) {
        printf("Read : %d\n", *value);
    }
}

void* write(void* data)
{
    int* value = data;

    for (int i = 0; i < 10; i++) {
        (*value)++;
        printf("Write : %d\n", *value);
    }
}

int main()
{
    int data = 15;

    pthread_t write_thread, read_thread;

    pthread_create(&write_thread, NULL, write, &data);
    pthread_create(&read_thread, NULL, read, &data);

    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    return 0;
}