#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
writepid(const char *pidfile)
{
	FILE *fp = fopen(pidfile, "w");
	if (fp == NULL) {
		perror("cannot open pid file");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "%d\n", getpid());
	fclose(fp);
}

int
main(int argc, char **argv)
{
	if (argc > 1) {
		if (!strcmp(argv[1], "-h")) {
			printf("%s [pidfile]\n", argv[0]);
			return 0;
		} else {
			writepid(argv[1]);
		}
	}
	pause();
}
