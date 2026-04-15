#include "codexion.h"

typedef struct thread_s
{
    int age;
    char *name;
}thread;

pthread_mutex_t lock;

void *func(void *p)
{
    int *n = (int *)p;
    pthread_mutex_lock(&lock);
    (*n)++;
    printf("im %d ayaya\n", *n);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t id;
    pthread_t id2;
    pthread_t id3;

    int n1 = 0;
    int n2 = 1;
    int n3 = 2;
    pthread_create(&id, NULL, func, &n1);

    pthread_create(&id2, NULL, func, &n2);

    pthread_create(&id3, NULL, func, &n3);
    pthread_join(id, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);

}
