#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

double CalculateTime(__time_t start_sec, __time_t end_sec, __suseconds_t start_usec, __suseconds_t end_usec){
return (end_sec + (double) end_usec/1000000) - (start_sec + (double) start_usec/1000000);
}

int main (){
struct timeval total_start, total_end, partial_start, partial_end;
char path[255];
char arg[255];
int status;

gettimeofday(&total_start, NULL);

while (scanf(" %s %s", path, arg) != EOF) {
gettimeofday(&partial_start, NULL);
if(fork()){
  wait(&status);
  gettimeofday(&partial_end, NULL);

  double time = CalculateTime(partial_start.tv_sec, partial_end.tv_sec, partial_start.tv_usec, partial_end.tv_usec);
  printf("> It took %.1lf seconds, returned %d\n", time, status/256);
  fflush(stdout);
} else {
  if(execl(path, path, arg, NULL) == -1){
    printf("> Error: %s\n", strerror(errno));
    fflush(stdout);
    _exit(errno);
  };
}

}

gettimeofday(&total_end, NULL);

double total_time = CalculateTime(total_start.tv_sec, total_end.tv_sec, total_start.tv_usec, total_end.tv_usec);

printf(">> The total time was %.1lf seconds\n", total_time);

return 0;
}




