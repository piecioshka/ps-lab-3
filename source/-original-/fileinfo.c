#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void show_stat_info(char *fname, struct stat *buf);

int main(int argc, char *argv[])
{
    struct stat info;   
    if (argc>1) {
      if( stat(argv[1], &info) != -1 ){
            show_stat_info( argv[1], &info );
            return 0;
      }
    }
    else
      printf("Uzycie: %s nazwa_pliku\n",argv[0]);  
    return 1;
}
void show_stat_info(char *fname, struct stat *buf)
{
    printf("   mode: %o\n", buf->st_mode);         /* type + mode */
    printf("  links: %d\n", buf->st_nlink);        /* # links     */
    printf("   user: %d\n", buf->st_uid);          /* user id     */
    printf("  group: %d\n", buf->st_gid);          /* group id    */
    printf("   size: %ld\n", buf->st_size);         /* file size   */
    printf("modtime: %ld\n", buf->st_mtime);        /* modified    */
}
