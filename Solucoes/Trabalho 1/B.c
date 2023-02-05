#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>


int main(int argc, char **argv) {
    void *open;

    open = dlopen(argv[1], RTLD_NOW);

    if(open == NULL) {
    printf("nao disponivel\n");
    return 0;
    }

    int (*imprime)(void);
    imprime = dlsym(open, "imprime");

    if(dlerror() != NULL) {
    printf("nao implementado\n");

    }
    else {
    int result_imp = (*imprime)();
    printf("%d\n", result_imp);
    }

    int (*calcula)(int, int);
    calcula = dlsym(open, "calcula");

    if(dlerror() != NULL) {
    printf("nao implementado\n");
        
    }
    else {
    int result_cal = (*calcula)(atoi(argv[2]),atoi(argv[3]));
    printf("%d\n", result_cal);
    }

    int (*trigo)(double, double*);
    trigo = dlsym(open, "trigo");

    if(dlerror() != NULL) {
    printf("nao implementado\n");
        
    }
    else {
    int result_trigo = (*trigo)(atof(argv[4]),NULL);
    printf("%d\n", result_trigo);
        
    }

    dlclose(open);

    return 0;
}