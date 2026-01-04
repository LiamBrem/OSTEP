#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	int x = 100;

	if (rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0){
		printf("child: %d\n", x); // 100

	} else {
		printf("parent: %d\n", x); // 100
	}

	return 0;
}
