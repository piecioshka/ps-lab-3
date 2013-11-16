/**
 * Napisz program, który przegląda wybrany katalog wraz z podkatalogami i wyświetla informację 
 * o liczbie i procentowym udziale plików różnych typów (zwykłe, katalogi, dowiązania 
 * symboliczne, itp.). Do przeglądania katalogu użyj funkcji bibliotecznej nftw().
 */
#include <stdio.h>
#include <ftw.h>
#include "../lib/libutils.c"

void usage() {
    fprintf(stderr, "Print percentage usage of different of file types\n");
    fprintf(stderr, "Usage: [directory]\n");
    exit(1);
}

static unsigned int files = 0;
static unsigned int dirs = 0;
static unsigned int symbolics = 0;
static unsigned int sockets = 0;

int process(const char * fpath, const struct stat *ptr, int flag) {
    if (is_dir((char *) fpath)) {
        dirs++;
    } else if (is_file((char *) fpath)) {
        files++;
    } else if (is_symbolic((char *) fpath)) {
        symbolics++;
    } else if (is_socket((char *) fpath)) {
        sockets++;
    }
    return 0;
}

int main(int argc, char * argv[]) {
    int sum = 0;
    if (argc == 2) {
        if (file_exists(argv[1]) && is_dir(argv[1])) {
            ftw(argv[1], &process, 1);
            sum = files + dirs + symbolics + sockets;
            printf("Sum of items: %d\n", sum);
            printf("---\n");
            printf("File(%d):\t%d%%\n", files, (files * 100 / sum));
            printf("Dirs(%d):\t%d%%\n", dirs, (dirs * 100 / sum));
            printf("Symbolics(%d):\t%d%%\n", symbolics, (symbolics * 100 / sum));
            printf("Sockets(%d):\t%d%%\n", sockets, (sockets * 100 / sum));
        } else {
            fprintf(stderr, "File: '%s' is not a directory\n", argv[1]);
            exit(1);
        }
    } else {
        usage();
    }

    exit(0);
}
