#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int alrmct = 0;
void identifies(int signal) {
    if(signal == SIGUSR1) {
        printf("SIGUSR1 eh para aproveitar mais um pouco \n");

    }
    else if(alrmct < 2) {
        printf("Ai que sono, quero dormir mais um pouco\n");
        alrmct++;
    }
    else {
        printf("Os incomodados que se mudem, tchau\n");
        exit(0);
    }
}

int main(void) {
    signal(SIGUSR1, identifies);
    signal(SIGALRM, identifies);


    while(1) {
        pause();
    }
}