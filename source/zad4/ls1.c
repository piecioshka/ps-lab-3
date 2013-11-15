/** ls1.c
 **   Program wyswietla zawartosc katalogu biezacego
 **   lub katalogu wskazanego argumentem
 **/
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "../lib/libutils.c"

/*!
 *  wyswietl pliki w katalogu dirname
 */
void do_ls(char dirname[], int show_hidden) {
  DIR *dir_ptr; /* katalog */
  struct dirent *direntp; /* wpis w katalogu */
  int starting_dot;

  if ((dir_ptr = opendir(dirname)) == NULL) {
    fprintf(stderr, "ls1: cannot open %s\n", dirname);
  } else {
    while ((direntp = readdir(dir_ptr)) != NULL) {
      if (show_hidden == 1) {
        printf("%s\n", direntp->d_name);
      } else {
        starting_dot = strncmp(direntp->d_name, ".", 1);
        if (starting_dot > 0) {
          printf("%s\n", direntp->d_name);
        }
      }
    }
    closedir(dir_ptr);
  }
}

/*!
 *  wyswietl pliki w katalogu dirname
 */
void do_long_ls(char dirname[], int show_hidden) {
  DIR *dir_ptr; /* katalog */
  struct dirent *direntp; /* wpis w katalogu */
  int starting_dot;
  struct stat info;

  if ((dir_ptr = opendir(dirname)) == NULL) {
    fprintf(stderr, "ls1: cannot open %s\n", dirname);
  } else {
    while ((direntp = readdir(dir_ptr)) != NULL) {
      if (stat(direntp->d_name, &info) != -1) {
        if (show_hidden == 1) {
          show_stat_info_oneline(direntp->d_name, &info);
        } else {
          starting_dot = strncmp(direntp->d_name, ".", 1);
          if (starting_dot > 0) {
            show_stat_info_oneline(direntp->d_name, &info);
          }
        }
      }
    }
    closedir(dir_ptr);
  }
}

int main(int argc, char *argv[]) {
  char * opts = "l";
  int c;

  if (argc == 1) {
    do_ls(".", 0);
  }

  while((c = getopt(argc, argv, opts)) != -1) {
    switch (c) {
      case 'l':
        do_long_ls(".", 0);
        break;

      case '?':
      default:
        do_ls(".", 0);
    }
  }

  return 0;
}

