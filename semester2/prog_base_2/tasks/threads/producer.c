#include "producer.h"
#include "thread.h"
#include "mutex.h"
#include <time.h>
#include <stdlib.h>

static mutex_t *producer_mutex;
static thread_t *producer_thread;
static thread_t *producer_madenThread;
struct producer_s{
    int m[5];
    thread_t *thread;
};

static void *producer_loop(producer_t *pInput)
{
    producer_t *p = pInput;

    while(1)
    {
        mutex_lock(producer_mutex);

        if (thread_equals(producer_thread, p->thread))
        {
            mutex_unlock(producer_mutex);
            break;
        }
        int i;
        for (i = 0; i < 5; i++)
        {
            p->m[i] = rand() % 20 - 10;
        }
    }
}
int *producer_getNums(producer_t *p)
{
    return p->m;
}
void producer_startThread()
{
    producer_mutex = mutex_new();
    producer_thread = thread_getCurrentThread();
}

void producer_stopThread()
{
    mutex_free(producer_mutex);
    thread_free(producer_thread);
}

producer_t *producer_new()
{
    producer_t *p = malloc(sizeof(producer_t));
    int i;
    for (i=0; i<5; i++)
    {
        p->m[i] = rand() % 20 - 10;
    }


    p->thread = NULL;
}

void producer_execute(producer_t *p)
{
    thread_t *thread;
    mutex_lock(producer_mutex);
    thread = thread_create_args(producer_loop, p);
    p->thread = thread;
    mutex_unlock(producer_mutex);
}

void producer_free(producer_t *p)
{
    free(p);
}


