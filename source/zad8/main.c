/*
 * Napisz program, który jest uproszczoną wersją polecenia du:
 *  a) działa tylko we wskazanym katalogu,
 *  b) wyświetla albo wielkości poszczególnych plików albo ich sumę
 *  c) wielkości mogą być wyświetlane w różnych jednostkach (patrz polecenie du) w zależności od podanej opcji
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ftw.h>
#include "../lib/libutils.c"

void usage() {
    fprintf(stderr, "Program to calculate size of directories\n");
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "\t-s\tsummary - calculate only current directory\n");
    fprintf(stderr, "\t-g\tcalculate as giga byte\n");
    fprintf(stderr, "\t-m\tcalculate as mega byte\n");
    fprintf(stderr, "\t-k\tcalculate as kilo byte\n");
    fprintf(stderr, "\t-h\tprint this help\n");
    exit(1);
}

int file_byte(char * filename) {
    struct stat file;
    stat(filename, &file);
    return file.st_size;
}

int is_dot(char * name) {
    int single = strcmp(name, ".") == 0;
    int dbl = strcmp(name, "..") == 0;
    // printf("File: '%s' is single: %d or double: %d\n", name, single, dbl);
    return single || dbl;
}

int is_dir(char * filename) {
    struct stat file;
    stat(filename, &file);
    return file.st_mode & S_IFDIR;
}

int is_file(char * filename) {
    struct stat file;
    stat(filename, &file);
    return file.st_mode & S_IFREG;
}

void do_ls(char dirname[], int size) {
    DIR * dir_ptr; /* katalog */
    struct dirent * direntp; /* wpis w katalogu */

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "Cannot open: %s\n", dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            char combo[255];
            sprintf(combo, "%s/%s", dirname, direntp->d_name);
            // printf("%s\n", combo);

            if (is_dir(combo) && !is_dot(direntp->d_name)) {
                do_ls(combo, size);
            // } else if (is_file(combo) || is_dot(direntp->d_name)) {
                // printf("%d\t%s\n", file_byte(combo), combo);
            } else {
                // fprintf(stderr, "File: %s can't get size\n", combo);
            }
        }
        closedir(dir_ptr);
    }

    printf("%d\t%s\n", file_byte(dirname) / size, dirname);
}

static unsigned int total = 0;

int sum_single(const char *fpath, const struct stat *sb, int typeflag) {
    total += sb->st_size;
    return 0;
}

int sum_size(char * directory) {
    if (!is_dir(directory)) { 
        fprintf(stderr, "Path: '%s' is not a directory", directory);
        exit(1);
    }

    ftw(directory, &sum_single, 1);
    return total;
}

int main(int argc, char * argv[]) {
    char * opts = "sgmkh";
    int c;

    if (argc == 1) {
        do_ls(".", 1);
    } else {
        while ((c = getopt(argc, argv, opts)) != -1) {
            switch (c) {
                case 's': // summary
                    printf("%d\t%s\n", sum_size("."), ".");
                    break;
                case 'g': // giga byte
                    do_ls(".", 1073741824);
                    break;
                case 'm': // mega byte
                    do_ls(".", 1048576);
                    break;
                case 'k': // kilo byte
                    do_ls(".", 1024);
                    break;
                case ':':
                    err("give more params", "");
                    break;
                case '?':
                case 'h':
                default:
                    usage();
            }
        }
    }

    exit(0);
}
