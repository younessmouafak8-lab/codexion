#include "codexion.h"

typedef struct coder_s
{
    int id;
}coder;


void *func(void *p)
{
    coder *coders = (coder *)p;

    printf(" %d has taken a dongle\n", coders->id);
    printf(" %d has taken a dongle\n", coders->id);
    printf(" %d is compiling\n", coders->id);
    printf(" %d is debugging\n", coders->id);
    printf(" %d is refactoring\n", coders->id);
    coders->id++;

    return NULL;
}

int main()
{
    pthread_t id;
    pthread_t id2;

    coder *c1;
    coder *c2;
    c1 = malloc(sizeof(coder));
    c2 = malloc(sizeof(coder));
    c1->id = 23;
    c2->id = 24;
    pthread_create(&id, NULL, func, c1);
    pthread_create(&id2, NULL, func, c2);
    pthread_join(id, NULL);
    pthread_join(id2, NULL);
}
