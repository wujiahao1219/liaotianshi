#include "../server_h/liaotianshi_server.h"

void thread_destroy(struct threadpool* pool)
{
    pthread_mutex_lock(&(pool->mutex));
    while (pool->queue_cur_num != 0)
    {
        pthread_cond_wait(&(pool->queue_empty), &(pool->mutex));
    }

    pthread_mutex_unlock(&(pool->mutex));
    pthread_cond_broadcast(&(pool->queue_not_empty));
    pthread_cond_broadcast(&(pool->queue_not_full));

    for (int i = 0;i < pool->thread_num;i++)
    {
        printf("thread exit!\n");
        //pthread_cancel(pool->queue_ids[i]);
        pthread_join(pool->pthread_ids[i], NULL);
    }

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->queue_empty));
    pthread_cond_destroy(&(pool->queue_not_empty));
    free(pool->pthread_ids);

    struct job* temp;
    while (pool->head != NULL)
    {
        temp = pool->head;
        pool->head = temp->next;
        free(temp);
    }
}