#include "consumer.h"
#include "producer.h"
#include "thread.h"
#include "mutex.h"
#include <time.h>
#include <stdlib.h>

static mutex_t *consumer_mutex;
static thread_t *consumer_thread;

struct producer_s{
    int m[5];
    thread_t *thread;
};

struct consumer_s{
    int *m[5];
    thread_t *thread;
    producer_t *p;
};
static void *consumer_loop(consumer_t *cInput)
{
    consumer_t *c = cInput;
    int sum;
    int i;
    int mas[5];
    while(1)
    {

        mutex_lock(consumer_mutex);
        sum=0;
        for (i = 0; i < 5; i++)
        {
            mas[i] = c->p->m[i];
            sum += mas[i];
        }

        if (sum>0)
        {
            for (i = 0; i < 5; i++)
            {
                printf("%i ", mas[i]);
            }
            printf("\n");
        }

    }
}

void consumer_startThread()
{
    consumer_mutex = mutex_new();
    consumer_thread = thread_getCurrentThread();
}
void consumer_stopThread()
{
    mutex_free(consumer_mutex);
    thread_free(consumer_thread);
}
consumer_t *consumer_new(producer_t *p)
{
    consumer_t *c = malloc(sizeof(consumer_t));
    c->p = p;
    int i;
    for (i=0; i<5; i++)
    {
        c->m[i] = p->m[i];
    }

    c->thread = NULL;
}

void consumer_execute(consumer_t *c)
{
    thread_t *thread;
    mutex_lock(consumer_mutex);
    thread = thread_create_args(consumer_loop, c);
    c->thread = thread;
    mutex_unlock(consumer_mutex);
}


void consumer_free(consumer_t *c)
{
    free(c);
}
