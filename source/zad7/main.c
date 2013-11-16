/**
 * Polecenie tee czyta ze standardowego wejścia do napotkania końca pliku, zapisuje kopię wejścia na standardowe wyjście i do pliku podanego w wierszu wywołania.
 * Domyślnie polecenie tee nadpisuje ten plik, jeśli istnieje.
 * Napisz program, który
 *  a) działa zgodnie z domyślnym zachowaniem polecenia tee
 *  b) obsługuje opcję –a plik , która powoduje dopisanie wczytywanych danych do końca pliku, jeśli ten istnieje.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/libutils.c"

void usage() {
    fprintf(stderr, "Usage: [-a program]");
    exit(1);
}

void process_reading() {
    int c = fgetc(stdin);
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}

void append_file_content(char * filename, int cnt) {
    FILE *fp;
    if ((fp = fopen(filename, "a+")) == NULL) {
        fprintf(stderr, "Can not open file: %s\n", filename);
        exit(1);
    }
    fputc(cnt, fp);
    fclose (fp);
}

void process_save_reading(char * filename) {
    int c = fgetc(stdin);
    while (c != EOF) {
        putchar(c);
        append_file_content(filename, c);
        c = getchar();
    }
}

int main(int argc, char * argv[]) {
    char * opts = "a:";
    int c;

    if (argc == 1) {
        process_reading();
    } else {
        while ((c = getopt(argc, argv, opts)) != -1) {
            switch (c) {
                case 'a':
                    if (!file_exists(optarg)) {
                        fprintf(stderr, "File: '%s' doesn't exists\n", optarg);
                        exit(1);
                    }
                    printf("Save to file: %s\n", optarg);
                    process_save_reading(optarg);
                    break;
                case ':':
                    err("Give more params", "");
                    break;
                case '?':
                default:
                    usage();
            }
        }
    }

    exit(0);
}

