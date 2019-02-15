#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* So the way this'll work:

	when level = 1, either sleep or paush, depending on relevant tag
	processes should be called in bredth first order

 */

void process(int u, int N, int M, int p, int s){
	if(u == 0){
		printf("USAGE: \n");
		printf("prog2tree [-u] [-N <num_levels>] [-M <num_children>] [-p] [-s <sleep_time>]\n");
		exit(0);
	}else{
		// Process must print level, pid, and ppid

		pid_t pid;
		pid_t ppid;
		pid = getpid();
		ppid = getppid();
		printf("\nALIVE: Level %d", N);
		printf(" process with pid= %ld", pid);
		printf(", child of ppid= %ld\n", ppid);


		// BASE CASE: N =1
		if(N == 1){
			// This is the base case of the function, where no additional processes are made
			//function must pause or sleep child processes

			//execlp("ps", "ps", NULL);

			if(p == 0){
				// must pause processes
				pause();
			}else{
				// must sleep processes according to s
				sleep(s);
				printf("EXITING: Level %d", N);
				printf(" process with pid= %ld", pid);
				printf(", child of ppid= %ld\n", ppid);

			}
		}

		// RECURSIVE STEP: N != 1
		if(N > 1){
			// So long as it isn't the lowest level, the program will keep
			//generating processes

			//for each M, one process will be created
			int n = N-1;

			int length;
			if(p == 0){
				length = 24; //I manually counted how many chars it is
			}else{
				length = 27; //s can be double digit this way
			}

			char output[length];
			if(p == 0){
				sprintf(output, "./prog2tree -N %d -M %d -p", n, M);
			}else{
				sprintf(output, "./prog2tree -N %d -M %d -s %d", N-1, M, s);
				//printf("%d\n", n);
				//printf(output);
				printf("\n");

			}

			pid_t newp;
			for(int i=0; i<M; i++){
				//pid_t newp;
				//printf("Do I even get here??\n");
				newp = fork();
				if(newp < 0){
					// make sure fork successful
					fprintf(stderr, "Fork failed.\n");
				}
				if(newp == 0){
					// if newp == 0, child process
					printf(output);
					printf("\n");
					execlp("./prog2tree", output, NULL);
					

//					execlp("/bin/ls", "./prog2tree -M %d -N %d", M, n, NULL);
				}
/*				}else{
					// Parent process must wait() before children finish
					wait(NULL);
					printf("EXITING: Level %d", N);
					printf(" process with pid= %ld", pid);
					printf(", child of ppid= %ld\n", ppid);

				}
*/
			}

			if(newp > 0){
			
			wait(NULL);
			printf("EXITING: Level %d", N);
			printf(" process with pid= %ld", pid);
			printf(", child of ppid= %ld\n", ppid);

			}
		}

	}

}






// This is the main function, it reads in args and runs process accordingly

int main(int argc, char *argv[]){
	int opt;
	int u = 1;
	int N = 1;
	int M = 1;
	int p = 1;
	int s = 1;
	int sChecker = 1; //to check is p and s are called at the same time

	while((opt = getopt(argc, argv, "uN:M:ps:" )) != -1){
		switch(opt){
		case 'u':
			u = 0;
			break;
		case 'N':
			N=atoi(optarg);
			break;
		case 'M':
			M=atoi(optarg);
			break;
		case 'p':
			p = 0;
			break;
		case 's':
			s = 0;
			s=atoi(optarg);
			break;
		}
	}

	//Now that all args are loaded in, check that there are no contradictions

	if(N < 1 || N > 4){
		printf("N must be between 1 and 4\n");
		exit(0);
	}
	if(M < 1 || M > 3){
		printf("M must be between 1 and 3\n");
		exit(0);
	}
	if(sChecker == 0 && p == 0){
		printf("p and s cannot be called at the same time\n");
		exit(0);
	}

	//Certain that all arguments are within bounds, proceed to running process


	process(u, N, M, p, s);
	return 0;

}
