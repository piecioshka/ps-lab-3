#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void check_file_exists(char * filename) {
  /*check if file exists */
  int prawa = access(filename, F_OK);

  if (prawa == 0) {
    printf (" >> plik %s istnieje\n", filename);
  } else {
    if (errno == ENOENT) {
      printf(" >> plik %s nie istnieje\n", filename);
    } else if (errno == EACCES) {
      printf(" >> plik %s jest niedostepny\n", filename);
    } else {
      printf(" >> problem z dotarciem do pliku\n");
    }
    exit(1);
  }
}

void check_read_perms(char * filename) {
  /* check if process could read from file */
  int prawa = access(filename, R_OK);
  struct stat info;
  stat(filename, &info);

  if (prawa == 0) {
    printf ("%s: prawa do czytania\n", filename);
  } else {
    printf ("%s: brak praw do czytania\n", filename); 
  }
  /* user have perms */
  if ( info.st_mode & S_IWUSR ) printf(" - user\n");
  /* group have perms */
  if ( info.st_mode & S_IRGRP ) printf(" - group\n");
  /* others have perms */
  if ( info.st_mode & S_IROTH ) printf(" - others\n");
}

void check_write_perms(char * filename) {
  /* check if process could write to file */
  int prawa = access(filename, W_OK);
  struct stat info;
  stat(filename, &info);

  if (prawa == 0) {
    printf ("%s: prawa do pisania\n", filename);
  } else if (errno == EACCES) {
    printf ("%s brak praw do pisania (odmowa dostepu)\n", filename);
  } else if (errno == EROFS) {
    printf ("%s brak praw do pisania (zamontowany tylko do czytania)\n", filename);
  }
  /* user have perms */
  if ( info.st_mode & S_IWUSR ) printf(" - user\n");
  /* group have perms */
  if ( info.st_mode & S_IWGRP ) printf(" - group\n");
  /* others have perms */
  if ( info.st_mode & S_IWOTH ) printf(" - others\n");
}

void check_execute_perms(char * filename) {
  /* check if process could execute file */
  int prawa = access(filename, X_OK);
  struct stat info;
  stat(filename, &info);

  if (prawa == 0) {
    printf("%s: prawa do wykonywania\n", filename);
  } else {
    printf ("%s brak praw do wykonywania\n", filename);
  }
  /* user have perms */
  if ( info.st_mode & S_IXUSR ) printf(" - user\n");
  /* group have perms */
  if ( info.st_mode & S_IXGRP ) printf(" - group\n");
  /* others have perms */
  if ( info.st_mode & S_IXOTH ) printf(" - others\n");
}

void print_usage(char * program) {
  printf("\nUzycie %s\n", program);
  printf("\n\tr filename\tcheck if program have access to read this");
  printf("\n\tw filename\tcheck if program have access to write this");
  printf("\n\tx filename\tcheck if program have access to run thisi\n\n");
}

int main (int argc, char * argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
  }

  char * opts = "r:w:x:";
  int c;

  while((c = getopt(argc, argv, opts)) != -1) {
    switch (c) {
      case 'r':
        check_file_exists(optarg);
        check_read_perms(optarg);
        break;

      case 'w':
        check_file_exists(optarg);
        check_write_perms(optarg);
        break;

      case 'x':
        check_file_exists(optarg);
        check_execute_perms(optarg);
        break;

      case '?':
      default:
        print_usage(argv[0]);
    }
  }
  return 0;
}

