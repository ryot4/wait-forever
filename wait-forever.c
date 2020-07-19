#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void writepid(const char *pidfile);

int
main(int argc, char **argv)
{
	const char *pidfile = NULL;

	for (int i = 1 ; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0) {
			printf("%s [pidfile]\n", argv[0]);
			return 0;
		} else {
			pidfile = argv[i];
			break;
		}
	}

	if (pidfile != NULL) {
		writepid(pidfile);
	}

	pause();
}

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
