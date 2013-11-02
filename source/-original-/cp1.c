#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFERSIZE  4096
#define COPYMODE  0644

void err(char *, char *);

int main(int ac, char *av[])
{
  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
  if ( ac != 3 ){
    fprintf( stderr, "usage: %s source destination\n", *av);
    exit(1);
  }
  if ( (in_fd=open(av[1], O_RDONLY)) == -1 )
    err("Cannot open ", av[1]);

  if ( (out_fd=creat( av[2], COPYMODE)) == -1 )
    err( "Cannot creat", av[2]);

  while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 )
    if ( write( out_fd, buf, n_chars ) != n_chars )
       err("Write error to ", av[2]);
	if ( n_chars == -1 )
          err("Read error from ", av[1]);

  if ( close(in_fd) == -1 || close(out_fd) == -1 )
    err("Error closing files","");
  exit(0);
}

void err(char *s1, char *s2)
{
  fprintf(stderr,"Error: %s ", s1);
  perror(s2);
  exit(1);
}
