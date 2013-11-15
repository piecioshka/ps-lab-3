#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
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
  printf("   mode: %s\n", mode); /* type + mode */
  printf("  links: %d\n", buf->st_nlink); /* # links */
  printf("   user: %s\n", getloginbyid(buf->st_uid)); /* user name */
  printf("  group: %s\n", getgroupnamebyid(buf->st_gid)); /* group name */
  printf("   size: %s\n", bytes_to_human(buf->st_size)); /* file size */
  printf("accessed: %s\n", show_time((int) buf->st_atime)); /* accessed */
  printf("modified: %s\n", show_time((int) buf->st_mtime)); /* modified */
  printf("changed: %s\n", show_time((int) buf->st_ctime)); /* changed */
}

int main(int argc, char *argv[]) {
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
