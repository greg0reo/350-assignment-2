#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid;

	pid = fork();
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork failed.\n");
		return 1;
	}
	
	if (pid == 0){
		execlp("/bin/ls", "ls", NULL);
//		printf("adult pid: %d\n", pid);
	}else{

		wait(NULL);
//		pid_t ppid;
//		ppid = getppid();
		printf("%d\n", pid);
		printf("Child Complete.\n");
	}
	return 0;
}
