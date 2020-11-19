CC = cc
DEBUG = -g
CFLAGS = ${DEBUG} -std=c99 -pedantic -Wall

PREFIX = /usr/local

SRC = args.c lspac.c
OBJ = ${SRC:.c=.o}

all: lspac 

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: args.h lspac.h

lspac: ${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS}

clean:
	rm -f lspac ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f fntfs ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/lspac

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/lspac

.PHONY: all clean install uninstall

