CFLAGS=-std=c11

wait-forever: wait-forever.c
	cc -o $@ ${CFLAGS} wait-forever.c

clean:
	rm -f wait-forever

.PHONY: clean
