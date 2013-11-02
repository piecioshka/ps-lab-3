CC = gcc
CFLAGS = -Wall -Werror -pedantic -pedantic-errors
TARGET = bin/
SRC = source/

zad1:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

