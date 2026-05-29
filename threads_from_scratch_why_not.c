#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct job_node {
    void (*run)(void *);
    void *data;
    struct job_node *next;
} job_node_t;

typedef struct {
    job_node_t *head, *tail;
    int pending_jobs, running_jobs, is_stopping;
    pthread_mutex_t mutex;
    pthread_cond_t has_jobs;
} workqueue_t;

void *worker_main(void *prt) {
workqueue_t *queue = (workqueue_t *) prt;
    for (;;) {
        pthread_mutex_lock(&queue->mutex);
        printf("OK");


        break;
    }




    return NULL;
}

int main() {
    workqueue_t q = {0};
    pthread_mutex_init(&q.mutex, NULL);
    pthread_cond_init(&q.has_jobs, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, worker_main, &q);

}

