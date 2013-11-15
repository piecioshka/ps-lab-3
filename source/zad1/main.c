/**
 * Prawa dostępu
 * Napisz funkcję, która tłumaczy prawa dostępu do pliku zapisane w postaci binarnej
 * na prawa zapisane w postaci symbolicznej. Prawa do pliku pobierz za pomocą funkcji stat().
 */
#include <stdio.h>
#include "../lib/libutils.c"

int main(int argc, char * argv[]) {
  struct stat info;
  static char perms[255];
  if (argc > 1) {
    printf(" >> Czytamy plik: %s\n", argv[1]);

    /* check if file exists */
    if (stat(argv[1], &info) != -1 ) {
      /* exists */
      /* show_stat_info( argv[1], &info ); */
      mode_to_letters(info.st_mode, perms);
      printf("Prawa dostepu dla pliku: %s\n", perms);
      return 0;
    } else {
      /* not exists, throw error */
      perror(argv[1]);
    }
  } else {
    fprintf(stderr, "Podaj plik do analizy!\n");
  }
  return 1;
}
