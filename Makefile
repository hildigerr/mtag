CC = g++
CFLAGS = -Wall
LDFLAGS = -ltag

mtag: mtag.cpp
	${CC} ${CFLAGS} -o $@ $? ${LDFLAGS}

