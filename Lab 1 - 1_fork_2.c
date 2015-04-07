#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid,pid2;
	int rv,rv2;

	switch(pid = fork()) {
		case -1:
		perror("fork"); /*something went wrong*/
		exit(1); /*parent exits*/

		case 0:
		printf(" CHILD: This is the child process!\n");
		printf(" CHILD: My PID is %d\n", getpid());
		printf(" CHILD: My parent's PID is %d\n", getpid());
		printf(" CHILD: Enter my exit status (make it small): ");
		scanf(" %d", &rv);
		printf(" CHILD: I'm outta here!\n");
		exit(rv);

		default:
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: My PID is %d\n", getpid());
		printf("PARENT: My child's PID is %d\n", pid);
		printf("PARENT: I'm now waiting for my child to exit()...\n");
		switch(pid2 = fork()) {
			case -1:
			perror("fork"); /*something went wrong*/
			exit(1); /*parent exits*/

			case 0:
			printf(" CHILD: This is the child process!\n");
			printf(" CHILD: My PID is %d\n", getpid());
			printf(" CHILD: My parent's PID is %d\n", getpid());
			printf(" CHILD: Enter my exit status (make it small): ");
			scanf(" %d", &rv2);
			printf(" CHILD: I'm outta here!\n");
			exit(rv2);

			default:
			printf("PARENT: This is the parent process!\n");
			printf("PARENT: My PID is %d\n", getpid());
			printf("PARENT: My child's PID is %d\n", pid2);
			printf("PARENT: I'm now waiting for my child to exit()...\n");
			wait(&rv2);
			printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv2));
		}
		printf("PARENT: I'm outta here!\n");
	}

	return 0;
}
