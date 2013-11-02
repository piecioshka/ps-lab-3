CC = gcc
CFLAGS = -Wall -Werror -pedantic -pedantic-errors
TARGET = bin/
SRC = source/

zad1:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad2:
	${CC} ${CFLAGS} ${SRC}$@/fileinfo.c -o ${TARGET}$@/fileinfo.o

zad3:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

clean:
	find . -name "*.o" | xargs rm

