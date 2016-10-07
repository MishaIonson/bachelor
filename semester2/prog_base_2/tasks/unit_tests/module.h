#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef struct array_s array_t;

typedef enum status_t{
    ARRAY_OK,
    ARRAY_BADINDEX,
} status_t;

array_t * array_new(int size);
void array_free(array_t * self);

int array_getSize(const array_t * self);
int array_getValueAt(array_t * self, int pos);
int array_getFirstNegative(const array_t * self);
int array_getMostPopular(const array_t * self);
void array_fill(array_t * self);
void array_print(const array_t * self);

status_t array_getStatus(array_t * arr);
void array_edit(array_t * arr, int index, int value);

#endif // ARRAY_H_INCLUDED
