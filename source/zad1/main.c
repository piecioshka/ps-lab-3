#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void mode_to_letters( int mode, char str[] ) {
  strcpy( str, "----------" ); /* default=no perms */
  if (S_ISDIR(mode) ) str[0] = 'd'; /* directory? */
  if (S_ISCHR(mode) ) str[0] = 'c'; /* char devices */
  if (S_ISBLK(mode) ) str[0] = 'b'; /* block device */
  if (mode & S_IRUSR ) str[1] = 'r'; /* 3 bits for user */
  if (mode & S_IWUSR ) str[2] = 'w';
  if (mode & S_IXUSR ) str[3] = 'x';
  if (mode & S_IRGRP ) str[4] = 'r'; /* 3 bits for group */
  if (mode & S_IWGRP ) str[5] = 'w';
  if (mode & S_IXGRP ) str[6] = 'x';
  if (mode & S_IROTH ) str[7] = 'r'; /* 3 bits for other */
  if (mode & S_IWOTH ) str[8] = 'w';
  if (mode & S_IXOTH ) str[9] = 'x';
}

int main(int argc, char * argv[]) {
  struct stat info;
  static char perms[255];
  if (argc > 1) {
    printf("czytamy plik: %s\n", argv[1]);

    /* check if file exists */
    if (stat(argv[1], &info) != -1 ) {
      /* exists */
      /* show_stat_info( argv[1], &info ); */
      mode_to_letters(info.st_mode, perms);
      printf("prawa dostepu dla pliku: %s\n", perms);
      return 0;
    } else {
      /* not exists, throw error */
      perror(argv[1]);
    }
  } else {
    fprintf(stderr, "Podaj plik do analizy\n");
  }
  return 1;
}
