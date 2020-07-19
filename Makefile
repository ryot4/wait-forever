CFLAGS=-std=gnu99

wait-forever: wait-forever.c
	cc -o $@ ${CFLAGS} wait-forever.c

clean:
	rm -f wait-forever

.PHONY: clean
