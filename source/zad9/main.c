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
    if (argc == 2) {
        if (file_exists(argv[1]) && is_dir(argv[1])) {
            ftw(argv[1], &process, 1);
            printf("File: %d\n", files);
            printf("Dirs: %d\n", dirs);
            printf("Symbolics: %d\n", symbolics);
            printf("Sockets: %d\n", sockets);
        } else {
            fprintf(stderr, "File: '%s' is not a directory\n", argv[1]);
            exit(1);
        }
    } else {
        usage();
    }

    exit(0);
}
