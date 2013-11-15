#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../lib/libutils.c"

#define BUFFERSIZE  4096
#define COPYMODE  0644

void err(char *s1, char *s2) {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}

int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    char * opts = "i";
    int op;

    while ((op = getopt(argc, argv, opts)) != -1) {
        switch (op) {
            case 'i':
                printf("selected option: i\n");
                break;
            case '?':
            default:
                printf("selected option: none\n");
        }
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s source destination\n", *argv);
        exit(1);
    }

    if ((in_fd = open(argv[1], O_RDONLY)) == -1) {
        err("Cannot open: ", argv[1]);
    }

    if ((out_fd = creat(argv[2], COPYMODE)) == -1) {
        err("Cannot creat: ", argv[2]);
    }

    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
        if (write(out_fd, buf, n_chars) != n_chars) {
            err("Write error to: ", argv[2]);
        }
    }

    if (n_chars == -1) {
        err("Read error from: ", argv[1]);
    }

    if (close(in_fd) == -1 || close(out_fd) == -1) {
        err("Error closing files", "");
    }

    header("Summary");
    show_properties(argv[1]);
    show_properties(argv[2]);

    exit(0);
}

