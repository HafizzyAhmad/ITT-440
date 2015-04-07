#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
	void sigterm_handler(int sig); 
	char s[200];

	if (signal(SIGTERM, sigterm_handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}

	printf("Enter a string: \n");

	if (gets(s) == NULL)
		perror("gets");
	else
	{
		printf("You entered: \"%s\"\n", s);
		printf("This is a special signal handler for <signal>");
	}

	return 0;
}

void sigterm_handler(int sig)
{
	printf("Not this time!\n");
}
