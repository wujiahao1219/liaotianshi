#include "../server_h/liaotianshi_server.h"

void thread_add_job(struct threadpool* pool, void* (*func)(void*), void* arg)
{
    pthread_mutex_lock(&(pool->mutex));
    while (pool->queue_cur_num == pool->queue_max_num)
    {
        pthread_cond_wait(&(pool->queue_not_full), &(pool->mutex));
    }

    struct job* pjob = (struct  job*)malloc(sizeof(struct job));
    //malloc

    pjob->func = func;
    pjob->arg = arg;

    if (pool->head == NULL)
    {
        pool->head = pool->tail = pjob;
        pthread_cond_broadcast(&(pool->queue_not_empty));
    }

    pool->tail->next = pjob;
    pool->tail = pjob;

    pool->queue_cur_num++;
    pthread_mutex_unlock(&(pool->mutex));
}
