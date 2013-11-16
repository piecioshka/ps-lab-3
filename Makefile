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

zad4:
	${CC} ${CFLAGS} ${SRC}$@/ls1.c -o ${TARGET}$@/ls1.o

zad5:
	${CC} ${CFLAGS} ${SRC}$@/cp1.c -o ${TARGET}$@/cp1.o

zad6:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad7:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad8:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad9:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad10:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

clean:
	find . -name "*.o" | xargs rm

