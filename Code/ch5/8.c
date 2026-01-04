#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fds[2];
  if (pipe(fds) == -1) {
    perror("pipe");
    exit(1);
  }
  int rc1 = fork();

  if (rc1 < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc1 == 0) {
    close(fds[0]);               // close read end
    dup2(fds[1], STDOUT_FILENO); // redirect stdout to pipe
    close(fds[1]);               // discard

    printf("Child 1 (PID: %d, Parent PID: %d) is running.\n", getpid(),
           getppid());

    fflush(stdout);

    exit(0);
  } else {
    int rc2 = fork();

    if (rc2 < 0) {
      fprintf(stderr, "fork failed\n");
    } else if (rc2 == 0) {
      printf("Child 2 (PID: %d, Parent PID: %d) is running.\n", getpid(),
             getppid());
      close(fds[1]);              // close write end
      dup2(fds[0], STDIN_FILENO); // redirect stdin to pipe
      close(fds[0]);              // discard

      char buffer[100];
      while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("Child 2 read: %s", buffer);
      }
      exit(0);
    } else {
      close(fds[0]);
      close(fds[1]);
      waitpid(rc1, NULL, 0);
      waitpid(rc2, NULL, 0);
      printf("parent done\n");
    }
  }

  return 0;
}
