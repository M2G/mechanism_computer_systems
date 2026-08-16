#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int sum = 0;

// increases value of variable sum
// NOTE: this function is intentionally NOT thread-safe
// to demonstrate a race condition on the shared variable "sum"
void *increase_sum(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        sum++;
    }
    return NULL;
}

int main()
{
    // variable to store the threads
    pthread_t t1, t2;

    // thread creation
    int rc1 = pthread_create(&t1, NULL, &increase_sum, NULL);
    if (rc1 != 0)
    {
        fprintf(stderr, "pthread_create failed: %s\n", strerror(rc1));
        return 1;
    }

    int rc2 = pthread_create(&t2, NULL, &increase_sum, NULL);
    if (rc2 != 0)
    {
        fprintf(stderr, "pthread_create failed: %s\n", strerror(rc2));
        return 1;
    }

    // wait for the child threads to join main thread
    int rc3 = pthread_join(t1, NULL);
    if (rc3 != 0)
    {
        fprintf(stderr, "pthread_join failed: %s\n", strerror(rc3));
    }

    int rc4 = pthread_join(t2, NULL);
    if (rc4 != 0)
    {
        fprintf(stderr, "pthread_join failed: %s\n", strerror(rc4));
    }

    // print sum after both threads join
    printf("The total should be 2000000\n");
    printf("The total sum is %d \n", sum);

    return 0;
}