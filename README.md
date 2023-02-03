## UID: 105817312
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

## Pipe Up

C implementation of the pipe (|) operator in shells.

## Building

Run the following commands to build and run the pipe executable:

    make
    ./pipe argv[1], argv[2], ... // argv[i] is a command argument

## Running

Show an example run of your program, using at least two additional arguments, and what to expect.

Your output should be the same as if you were to use | between each program in your shell.

    > ls
    Makefile pipe pipe.c pipe.o README.md
    > ls | cat | wc
        5   5   38
    > ./pipe ls
    Makefile pipe pipe.c pipe.o README.md
    > ./pipe ls cat wc
        5   5   38

## Cleaning up

Run the following command in the terminal:

    make clean

This cleans up all the binary files existing in the current directory of pipe.c and you can now build pipe again.
