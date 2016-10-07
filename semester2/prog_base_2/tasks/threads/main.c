#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>
#include "thread.h"
#include "mutex.h"
#include "consumer.h"
#include "producer.h"

int main(void)
{
    srand(time(NULL));
    consumer_t *c;
    producer_t *p;
    int m[5];
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    m[4] = 2;
    producer_startThread();
    consumer_startThread();
    p = producer_new(&m);
    c = consumer_new(p);


    producer_execute(p);
    consumer_execute(c);

    getchar();



    producer_stopThread();
    consumer_stopThread();

    producer_free(p);
    consumer_free(c);



}
