#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int vector_one[10000000];
int vector_two[10000000];

struct thread_st {
    int *v;
    int size;
    pthread_t tid;
};

int compar(const void *a, const void *b) {
    if(*(int*)a > *(int*)b) return 1;
    if(*(int*)a < *(int*)b) return -1;
    return 0;
}

void *threadfunc(void *p) {
    struct thread_st *a = (struct thread_st*)p;
    qsort(a -> v, a -> size, sizeof(int), compar);
}

int main() {
    int size;

    scanf("%d", &size);

    for(int i = 0; i < size; i++) {
        scanf("%d", &vector_one[i]);
    }

    for(int i = 0; i < size; i++) {
        scanf("%d", &vector_two[i]);
    }

    struct thread_st t1, t2;
    t1.v = vector_one;
    t1.size = size;
    t2.v = vector_two;
    t2.size = size;

    pthread_create(&t1.tid, NULL, threadfunc, (void*)&t1);
    pthread_create(&t2.tid, NULL, threadfunc, (void*)&t2);
    pthread_join(t1.tid, NULL);
    pthread_join(t2.tid,NULL);

    for(int i = 0; i < size; i++) {
        if(vector_one[i] != vector_two[i]) {
            printf("Diferentes");
            return 0;
        }
    }

    printf("Mesmos elementos");
    return 0;
}