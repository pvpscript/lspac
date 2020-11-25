VERSION = 1.0.0

SRC_DIR = src
OBJ_DIR = obj
MAN_DIR = doc
INC_DIR = include

CC = cc
DEBUG = -g
LIBS = -l alpm
CMPTIME = -DVERSION=\"${VERSION}\"
CFLAGS = ${CMPTIME} ${DEBUG} ${LIBS} -I${INC_DIR} -std=c99 -pedantic -Wall

BIN = lspac

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

SRC = ${wildcard ${SRC_DIR}/*.c}
OBJ = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

all: ${OBJ_DIR} ${BIN} 

${OBJ_DIR}:
	mkdir -p $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} $< -o $@

${BIN}: ${OBJ}
	${CC} ${CFLAGS} ${LIBS} -o $@ ${OBJ}

clean:
	rm -rf ${BIN} ${OBJ_DIR}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/${BIN}
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f ${MAN_DIR}/${BIN}.1 ${DESTDIR}${MANPREFIX}/man1/${BIN}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${BIN}.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${BIN}
	rm -f ${DESTDIR}${MANPREFIX}/man1/${BIN}.1

.PHONY: all clean install uninstall

