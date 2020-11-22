CC = cc
DEBUG = -g
LIBS=-l alpm
CFLAGS = ${DEBUG} ${LIBS} -Iinclude -std=c99 -pedantic -Wall

BIN = lspac

PREFIX = /usr/local

SRC_DIR = src
OBJ_DIR = obj

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

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${BIN}

.PHONY: all clean install uninstall

