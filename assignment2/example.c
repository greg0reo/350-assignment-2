#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid;

	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork failed.");
		return 1;
	}
	
	if (pid == 0){
		execlp("/bin/ls", "ls", NULL);
	}else{

		wait(NULL);
		printf("Child Complete.");
	}
	return 0;
}
