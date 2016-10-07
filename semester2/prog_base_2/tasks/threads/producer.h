#ifndef PRODUCER_H
#define PRODUCER_H
#include <windows.h>
typedef struct producer_s producer_t;
void producer_startThread();

void producer_free(producer_t *p);

void producer_execute(producer_t *p);
#endif
