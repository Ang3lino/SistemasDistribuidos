#include "vector.h"

// private:
static void 
resize (vector *v) {
    v->capacity *= 2;
	v->item = realloc(v->item, sizeof(void *) * v->capacity);
    if (v->item == NULL) {
        perror ("Empty memory D: \n");
        exit (EXIT_FAILURE);
    }
}

static void 
moveSubvectorOneStepRight(vector *v, int a) {
	int i;
	for (i = v->size - 1; i >= a; i--)
		v->item[i + 1] = v->item[i];
}

// public:
vector *
new_vector (void) {
    vector *v = malloc(sizeof(vector));
    v->capacity = 2;
    v->size = 0;
    v->item = calloc (sizeof (void *), v->capacity);
    return v;
}


void 
vpush_back (vector *v, void *data) {
    if (v->size  + 1 >= v->capacity)
        resize (v);
    v->item[v->size++] = data;
}

void 
vpush_front (vector *v, void *data) {
    v->size++;  
	int i;
    if (v->size > v->capacity)
        resize (v);
	moveSubvectorOneStepRight (v, 0);
	v->item[0] = data;
}

void // Se debe hacer que len > 0
vresize (vector *v, size_t len) {
    while (v->capacity < len)
        resize (v);
}

void *
vpop_back (vector *v) {
    if (v->size <= 0) {
        perror ("Error at vecpop_back: " 
                "emtpy vector. -_- \n");
        exit (EXIT_FAILURE);
    }
    return v->item[--v->size];
}

void 
vset (vector *v, size_t index, void *data) {
    if (index < v->size && index >= 0) 
        v->item[index] = data;
    else {
        perror ("Error at vec_set: invalid index -_- ");
        exit (EXIT_FAILURE);
    }
}

void  
vadd (vector *v, size_t index, void *data) {
    if (index >= v->size || index < 0) {
        perror ("Error at vec_add: invalid index -_- ");
        exit (EXIT_FAILURE);
    }
	moveSubvectorOneStepRight(v, index);
	v->item[index] = data;
}

void 
vclear(vector *v) {
    free(v->item);
    free(v);
}
