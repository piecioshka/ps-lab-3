#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../lib/libutils.c"

#define BUFFERSIZE  4096
#define COPYMODE  0644

void copy_file(char * s_name, char * t_name) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    printf("[+] Copy: %s -> %s\n", s_name, t_name); 

    if ((in_fd = open(s_name, O_RDONLY)) == -1) {
        err("Cannot open: ", s_name);
    }

    if ((out_fd = creat(t_name, COPYMODE)) == -1) {
        err("Cannot creat: ", t_name);
    }

    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
        if (write(out_fd, buf, n_chars) != n_chars) {
            err("Write error to: ", t_name);
        }
    }

    if (n_chars == -1) {
        err("Read error from: ", s_name);
    }

    if (close(in_fd) == -1 || close(out_fd) == -1) {
        err("Error closing files", "");
    }
}

void copy(char * s, char * t) {
    copy_file(s, t);

    printf("Print summary? (0/1): ");
    int show_summary;
    scanf("%d", &show_summary);

    switch (show_summary) {
        case 1:
            show_properties(s);
            show_properties(t);
            break;
        default:
            printf("Bye!\n");
    }
}

void usage() {
    fprintf(stderr, "Usage: [-i] source destination\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    char * opts = "i";
    int op;

    printf("\n");

    if (argc < 3 || argc > 4) usage();

    while ((op = getopt(argc, argv, opts)) != -1) {
        switch (op) {
            case 'i':
                if (file_exists(argv[3])) {
                    printf("File: %s exists, rewrite them? (0/1): ", argv[3]);
                    int prompt;
                    scanf("%d", &prompt);

                    switch (prompt) {
                        case 1: copy(argv[2], argv[3]); break;
                        case 0:
                        default: printf("Escape.\n");
                    }
                }
                exit(0);
                break;
            case '?':
            default:
                usage();
        }
    }

    copy(argv[1], argv[2]);

    exit(0);
}

