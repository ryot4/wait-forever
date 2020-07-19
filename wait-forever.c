/* Copyright 2017 ryot4
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void writepid(const char *pidfile);
void handle_signal(int _sig);
void handle_child_signal(int _sig);

int
main(int argc, char **argv)
{
	const char *pidfile = NULL;
	bool remove_pidfile = false;

	for (int i = 1 ; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0) {
			printf("%s [-r] [pidfile]\n", argv[0]);
			return 0;
		} else if (strcmp(argv[i], "-r") == 0) {
			remove_pidfile = true;
		} else {
			pidfile = argv[i];
			break;
		}
	}

	const struct sigaction act = { .sa_handler = handle_signal };
	if (sigaction(SIGINT, &act, NULL) == -1) {
		perror("cannot set SIGINT handler");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGTERM, &act, NULL) == -1) {
		perror("cannot set SIGTERM handler");
		exit(EXIT_FAILURE);
	}

	const struct sigaction chld_act = {
		.sa_handler = handle_child_signal,
		.sa_flags = SA_NOCLDSTOP,
	};
	if (sigaction(SIGCHLD, &chld_act, NULL) == -1) {
		perror("cannot set SIGCHLD handler");
		exit(EXIT_FAILURE);
	}

	if (pidfile != NULL) {
		writepid(pidfile);
	}

	pause();

	if (pidfile != NULL && remove_pidfile) {
		if (unlink(pidfile) == -1) {
			perror("failed to remove the pid file");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
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
	if (fflush(fp) == EOF) {
		perror("failed to write to the pid file");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
}

void
handle_signal(int _sig)
{
}

void
handle_child_signal(int _sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0) {
	}
}
