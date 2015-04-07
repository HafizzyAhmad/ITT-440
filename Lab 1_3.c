#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int pfds[2], pfds2[2];
	char buf[30], buf2[30], p1[30], p2[30];

	pipe(pfds);
	pipe(pfds2);

	if(!fork()) {
		printf(" CHILD: writing to the pipe : ");
		scanf(" %s", p1);
		write(pfds[1], p1, 30);
		printf(" CHILD: exiting\n");
		if(!fork()) {
			printf(" CHILD: writing to the pipe : ");
			scanf(" %s", p2);
			write(pfds2[1], p2, 30);
			printf(" CHILD: exiting\n");
			exit(0);
		}
	} else {
		printf("PARENT: reading from pipe\n");
		read(pfds[0], buf, 30);
		read(pfds2[0], buf2, 30);
		printf("PARENT: read \"%s\"\n", buf);
		printf("PARENT: read \"%s\"\n", buf2);
		wait(NULL);
	}

	return 0;
}
