# wait-forever

wait-forever is a program that blocks until it receives SIGINT or SIGTERM.
It also handles SIGCHLD and reaps child processes.

## Usage

Run wait-forever where you want to do.

    $ wait-forever

To stop waiting, kill the process.

Optionally, you can specify the path of the pid file:

    $ wait-forever /tmp/wait.pid

In this case, wait-forever writes its own process ID to /tmp/wait.pid, so you
can kill the process as follows.

    $ kill $(cat /tmp/wait.pid)

With -r option, the pid file is removed on exit.

    $ wait-forever -r /tmp/wait.pid
