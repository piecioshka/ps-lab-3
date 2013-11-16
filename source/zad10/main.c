/**
 * Napisz program, który monitoruje i rejestruje zmiany wielkości pliku przez jedną godzinę.
 * Po zakończeniu monitorowania program powinien pokazać prosty histogram pokazujący 
 * wszystkie zmiany w tym czasie.
 */
#include <stdio.h>
#include "../lib/libutils.c"

#define TIME 20

void usage() {
    fprintf(stderr, "Show histogram of file size changes.\n");
    fprintf(stderr, "Usage: program\n");
    exit(1);
}

char * stars(int num) {
    char * buffer = malloc(num);
    for (int i = 0; i < num; i++) {
        strcat(buffer, "*");
    }
    return buffer;
}

void print_histogram(int data[]) {
    for (int i = 0; i < TIME; i++) {
        printf("%d sek:\t%s\n", (i + 1), stars(data[i] / 10));
    }
}

void file_analyze(char * filename) {
    time_t start, end;
    int dif;
    int changes[TIME];

    time(&start);

    while (1) {
        time(&end);
        dif = difftime(end, start);

        changes[dif] = file_byte(filename);

        if (dif >= TIME) {
            // printf ("After %d seconds to run.\n", dif );
            print_histogram(changes);
            break;
        }
    }
}

int main(int argc, char * argv[]) {
    if (argc != 2) usage();

    if (!file_exists(argv[1]) || !is_file(argv[1])) {
        fprintf(stderr, "File: '%s' doesn't exists!\n", argv[1]);
        exit(1);
    }

    printf("Analyze file: '%s'\n", argv[1]);
    file_analyze(argv[1]);

    exit(0);
}
