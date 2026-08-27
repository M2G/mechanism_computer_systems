/*
This program creates a new thread by calling pthread_create() function,
and then the new thread executes the function print_message().
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// just a function which prints statements
void *print_message(void *arg) // void *(*)(void *)
{
    // usleep(100000);
    printf("Hello from threads\n");
    return NULL;
}

int main()
{
    // variable to store the thread
    pthread_t t1;
    // thread creation
    pthread_create(&t1, NULL, &print_message, NULL);
    return 0;
}