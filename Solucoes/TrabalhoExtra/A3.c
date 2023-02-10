#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>

int g_has_error = 0;

void HandleSignal(int signo) {
if (signo == SIGUSR1) {
g_has_error = 1;
}
}


double time_difference(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}
void HandleParentProcess() {
int child_status;
struct timeval start, end;

gettimeofday(&start, NULL);
pid_t p = wait(&child_status);
gettimeofday(&end, NULL);

if (g_has_error == 1) {
    printf("> Error: %s\n", strerror(WEXITSTATUS(child_status)));
}

printf("> It took %0.1lf seconds, returned %d\n", CalculateTimeDifference(&start , &end), WEXITSTATUS(child_status));
fflush(stdout);

}

void HandleChildProcess(const char *path, const char *args) {
execl(path, path, args, NULL);
kill(getppid(), SIGUSR1);
_exit(errno);
}

int main (void) {
char executable_path[255], arguments[255];
struct timeval initial_total_time, final_total_time;

signal(SIGUSR1, HandleSignal);

gettimeofday(&initial_total_time, NULL);

while (scanf("%s %[^\n]", executable_path, arguments) == 2) {
    g_has_error = 0;
    pid_t pid = fork();
    if (pid == 0) { // child
        HandleChildProcess(executable_path, arguments);
    }
    else if (pid > 0) { // parent
        HandleParentProcess();
    }
}

gettimeofday(&final_total_time, NULL);

printf(">> Total time was %0.1lf seconds\n", CalculateTimeDifference(&initial_total_time , &final_total_time));
return 0;
}



