CC := gcc
OPTIONS = -g -Wall
OBJS = tp12.o portlib.o

tp12: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o tp12

tp12.o: tp12.c portlib.h
	${CC} ${OPTIONS} -c  tp12.c

portlib.o: portlib.c portlib.h
	${CC} ${OPTIONS} -c portlib.c

clean: 
	rm *.o