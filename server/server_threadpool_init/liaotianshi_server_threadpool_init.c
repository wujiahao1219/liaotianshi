#include "../server_h/liaotianshi_server.h"

void* threadpool_function(void* arg)
{
    struct  threadpool* pool = (struct threadpool*)arg;
    struct job* pjob = NULL;
    while (1)
    {
        pthread_mutex_lock(&(pool->mutex));

        while (pool->queue_cur_num == 0)
        {
            pthread_cond_wait(&(pool->queue_not_empty), &(pool->mutex));
        }

        pjob = pool->head;
        pool->queue_cur_num--;
        if (pool->queue_cur_num != pool->queue_max_num)
        {
            pthread_cond_broadcast(&(pool->queue_not_full));
        }

        if (pool->queue_cur_num == 0)
        {
            pool->head = pool->tail = NULL;
        }
        else
        {
            pool->head = pjob->next;
            pthread_cond_broadcast(&(pool->queue_empty));
        }

        printf("线程池 get job\n");         

        pthread_mutex_unlock(&(pool->mutex));
        pjob->func(pjob->arg);
        free(pjob);
        pjob = NULL;
    }
}

struct threadpool* threadpool_init(int thread_num, int queue_max_num)
{
    struct threadpool* pool = (struct threadpool*)malloc(sizeof(struct threadpool));
    //malloc

    pool->queue_max_num = queue_max_num;
    pool->queue_cur_num = 0;
    pool->head = NULL;
    pool->tail = NULL;

    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->queue_empty), NULL);
    pthread_cond_init(&(pool->queue_not_empty), NULL);
    pthread_cond_init(&(pool->queue_not_full), NULL);

    pool->thread_num = thread_num;
    pool->pthread_ids = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);
    //malloc

    for (int i = 0;i < pool->thread_num;i++)
    {
        pthread_create(&(pool->pthread_ids[i]), NULL, threadpool_function, (void*)pool);
    }
    return pool;
}