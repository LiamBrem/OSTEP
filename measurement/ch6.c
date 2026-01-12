#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// measuring the cost of a syscall

void measure_syscall() {
  struct timespec start, end;
  long mtime, secs, nsecs;
  long times = 10000000;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  for (int i = 0; i < times; i++) {
    ssize_t bytes_read = read(0, NULL, 0);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  secs = end.tv_sec - start.tv_sec;
  nsecs = end.tv_nsec - start.tv_nsec;

  long long total_ns = (end.tv_sec - start.tv_sec) * 1000000000LL +
                       (end.tv_nsec - start.tv_nsec);

  double nsecs_average = (double)total_ns / times;

  printf("Syscall: %.1f average nanoseconds \n", nsecs_average);
}


void measure_context_switch(){
	//come back
}

int main() {
  measure_syscall();
  measure_context_switch();
}
