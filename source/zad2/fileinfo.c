#include <stdio.h>
#include "../lib/libutils.c"

int main(int argc, char * argv[]) {
  struct stat info;
  if (argc > 1) {
    printf(" >> Czytamy plik: %s\n", argv[1]);

    if (stat(argv[1], &info) != -1) {
      show_stat_info( argv[1], &info);
      return 0;
    } else {
      /* not exists, throw error */
      perror(argv[1]);
    }
  } else {
    printf("Uzycie: %s nazwa_pliku\n", argv[0]);
  }
  return 1;
}
