/** ls1.c
 **   Program wyswietla zawartosc katalogu biezacego
 **   lub katalogu wskazanego argumentem
 **/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

void do_ls(char []);

int main(int argc, char *argv[])
{
  if ( argc == 1 )
    do_ls( "." );
  else
    while ( --argc ){
      printf("%s:\n", *++argv );
      do_ls( *argv );
    }
  return 0;
}

void do_ls( char dirname[] )
/*
 *  wyswietl pliki w katalogu dirname
 */
{
  DIR *dir_ptr;    /* katalog */
  struct dirent *direntp;    /* wpis w katalogu */

  if ( ( dir_ptr = opendir( dirname ) ) == NULL )
    fprintf(stderr,"ls1: cannot open %s\n", dirname);
  else
  {
    while ( ( direntp = readdir( dir_ptr ) ) != NULL )
      printf("%s\n", direntp->d_name );
    closedir(dir_ptr);
  }
}
