#include <stdlib.h>
#include <stdio.h>
#include "module.h"

struct array_s {
    int * array;
    int size;
    status_t status;
};

array_t * array_new(int size) {
    array_t * arr = malloc(sizeof(struct array_s));
    arr->array = malloc(sizeof(int) * size);
    arr->size = size;
    arr->status = ARRAY_OK;
    return arr;
}

int array_getFirstNegative(const array_t * self)
{
	int i;
	for (i=0; i<self->size; i++)
	{
		if (self->array[i]<0)
			return i;
	}
	return -1;
}

int array_getMostPopular(const array_t * self)
{
	int j, i;
	int popularity[self->size][2];
	for (i=0; i<self->size; i++)
	{
		popularity[i][0] = self->array[i];
		popularity[i][1] = 1;
	}
	for (i=0; i<self->size; i++)
	{
		for (j=0; j<self->size; j++)
		{
			if (popularity[i][0] == popularity[j][0])
			{
				popularity[i][1]++;
				popularity[j][1]++;
			}
		}
	}
	int max[2];
	max[1]=popularity[0][1];
	max[0] = popularity[0][0];
	for (i=0; i<self->size; i++)
	{
		if (popularity[i][1]>max[1])
		{
			max[1] = popularity[i][1];
			max[0] = popularity[i][0];
		}

	}
	return max[0];

}
void array_free(array_t * self) {
    free(self->array);
    free(self);
}

int array_getSize(const array_t * self) {
    return self->size;
}

int array_getValueAt(array_t * self, int pos) {
    self->status = ARRAY_OK;
    if (pos>=self->size||pos<0){
        self->status = ARRAY_BADINDEX;
    }
    return self->array[pos];
}

void array_fill(array_t * self) {
    int i;
    for (i = 0; i < self->size; i++) {
        self->array[i] = i;
    }
}

void array_print(const array_t * self) {
    int i;
    for (i = 0; i < self->size; i++) {
        printf("%i, ", self->array[i]);
    }
}

void array_edit(array_t * arr, int index, int value){
    arr->status=ARRAY_OK;
    if (arr->size<=index||index<0){
        arr->status=ARRAY_BADINDEX;
        return;
    }
    arr->array[index] = value;
}

status_t array_getStatus(array_t * arr){
    return arr->status;
}
