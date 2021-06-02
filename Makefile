CC := gcc
OPTIONS = -g -Wall
OBJS = ej6tp10.o portlib.o

ej6tp10: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o ej6tp10

ej6tp10.o: ej6tp10.c portlib.h
	${CC} ${OPTIONS} -c  ej6tp10.c

portlib.o: portlib.c portlib.h
	${CC} ${OPTIONS} -c portlib.c

clean: 
	rm *.o