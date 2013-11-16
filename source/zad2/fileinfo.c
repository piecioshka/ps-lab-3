/**
 * Informacja o pliku
 *  a) Zapoznaj się z programem fileinfo.c z pliku lab3.tar.gz. Uzupełnij program o podawanie nazwy pliku i wszystkich czasów związanych z plikiem.
 *  b) Zmodyfikuj program tak, aby informacja podawana była w bardziej przyjazny sposób:
 * File Name:
 * File Type: (np. zwykły, katalog, ...)
 * Mode: rw-rw-r-- (ósemkowo) Links:
 * UID: ania (UID liczbowy) GID: studenci (GID liczbowy) Size:
 * Accessed: (data ostatniego dostępu) 
 * Modified: (data ostatniej modyfikacji) 
 * Changed: (data ostatniej modyfikacji i-węzła)
 */
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

