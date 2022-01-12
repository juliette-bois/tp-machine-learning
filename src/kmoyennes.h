#ifndef __KMOYENNES_H__
#define __KMOYENNES_H__


//Renvoie vraie quand l'image est foncée
bool is_dark(Color col);

//Transforme l'image en noir et blanc
void black_white_image( Image* im );

//Couleurs noir et blanc
Color black = {.r=0,   .g=0,  .b=0};
Color white = {.r=255, .g=255,.b=255};

typedef struct {
    Color *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(Color));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array *a, int element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

#endif
