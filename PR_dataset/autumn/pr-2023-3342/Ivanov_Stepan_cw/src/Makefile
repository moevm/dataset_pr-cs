PROJECT = cw

CORE = src/
HEADERS = ./headers/
TMP = .tmp/

CC = gcc
CFLAGS = -w -I${HEADERS} -std=c99

SRC_CORE = $(wildcard ${CORE}*.c)
SRC_TOOLS = $(wildcard ${CORE}tools/*.c)
SRC_HANDLE_FUNCTS = $(wildcard ${CORE}handle_functs/*.c)

OBJ_SRC = $(patsubst ${CORE}%.c, ${TMP}%.o, ${SRC_CORE})
OBJ_TOOLS = $(patsubst ${CORE}tools/%.c, ${TMP}%.o, ${SRC_TOOLS})
OBJ_HANDLE_FUNCTS = $(patsubst ${CORE}handle_functs/%.c, ${TMP}%.o, ${SRC_HANDLE_FUNCTS})

OBJECTS = ${OBJ_SRC} ${OBJ_TOOLS} ${OBJ_HANDLE_FUNCTS} ${TMP}main.o


all: setup ${PROJECT} clean


setup:
	@ mkdir ${TMP}

${PROJECT}: ${OBJECTS}
	@ ${CC} ${CFLAGS} $^ -o $@

${TMP}%.o: %.c
	@ ${CC} ${CFLAGS} -c $< -o $@

${TMP}%.o: ${CORE}%.c
	@ ${CC} ${CFLAGS} -c $< -o $@

${TMP}%.o: ${CORE}tools/%.c
	@ ${CC} ${CFLAGS} -c $< -o $@

${TMP}%.o: ${CORE}handle_functs/%.c
	@ ${CC} ${CFLAGS} -c $< -o $@


clean:
	@ rm -rf ${TMP}
