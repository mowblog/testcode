CC=gcc
INCLUDE=-I.

all: tcpc tcps udps udpc

tcpc: tcpc.c myunp.c myunp.h
	${CC} -o tcpc tcpc.c myunp.c ${INCLUDE}
	
tcps: tcps.c myunp.c myunp.h
	${CC} -o tcps tcps.c myunp.c ${INCLUDE}

udps: udps.c myunp.c myunp.h
	${CC} -o udps udps.c myunp.c ${INCLUDE}

udpc: udpc.c myunp.c myunp.h
	${CC} -o udpc udpc.c myunp.c ${INCLUDE}
	
clean:
	rm tcpc tcps udpc udps
