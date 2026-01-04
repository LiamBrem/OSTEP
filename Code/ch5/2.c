#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  FILE *fp;
  fp = fopen("random.txt", "r");

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    int character;
    while ((character = fgetc(fp)) != EOF) {
      printf("[%d] %c", getpid(), character);
    }
  } else {
    int character;
    while ((character = fgetc(fp)) != EOF) {
      printf("[%d] %c", getpid(), character);
    }
  }

  return 0;
}
