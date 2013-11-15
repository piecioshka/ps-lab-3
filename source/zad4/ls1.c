/** ls1.c
 **   Program wyswietla zawartosc katalogu biezacego
 **   lub katalogu wskazanego argumentem
 **/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

char * show_time(int timestamp) {
  struct tm tm;
  static char buffer[255];
  char time_s[255];
  sprintf(time_s, "%i", timestamp);
  strptime(time_s, "%s", &tm);
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &tm);
  return buffer;
}

void mode_to_letters(int mode, char str[]) {
  strcpy(str, "----------"); /* default=no perms */
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

char * getloginbyid(int uid) {
  struct passwd * p = getpwuid(uid);
  return p->pw_name;
}

char * getgroupnamebyid(int gid) {
  struct group * g = getgrgid(gid);
  return g->gr_name;
}

char * bytes_to_human(int bytes) {
    static char human[255];
    if (bytes < 1024) {
        sprintf(human, "%i", bytes);
    } else {
        sprintf(human, "%i KB", bytes / 1024);
    }
    return human;
}

void show_stat_info(char *fname, struct stat *buf) {
  static char mode[255];
  mode_to_letters(buf->st_mode, mode);
  printf("%s %d %s %s %s\t%s %s\n", mode, buf->st_nlink, getloginbyid(buf->st_uid), getgroupnamebyid(buf->st_gid), bytes_to_human(buf->st_size), show_time((int) buf->st_mtime), fname);
}

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
          show_stat_info(direntp->d_name, &info);
        } else {
          starting_dot = strncmp(direntp->d_name, ".", 1);
          if (starting_dot > 0) {
            show_stat_info(direntp->d_name, &info);
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

