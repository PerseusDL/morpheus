LEXLIB = -lfl

INCLUDE=../includes
#CFLAGS= -O2 -I${INCLUDE} 
CFLAGS= -ggdb3 -I${INCLUDE}
RM=rm
CC=cc
CC=gcc
LEX=flex

ANALLIB=../anal/anal.a
ENDLIB=../gkends/gkends.a
GREEKLIB=../greeklib/greeklib.a
MORPHLIB=../morphlib/morphlib.a
GENERLIB=../gener/gener.a
DICTLIB=../gkdict/gkdict.a
LIBS=${ANALLIB} ${GENERLIB} ${ENDLIB} ${DICTLIB} ${MORPHLIB} ${GREEKLIB}

scando:	scando.o fullquantity.o ${LIBS}
	${CC} -o scando scando.o fullquantity.o ${LIBS}

clean:
	rm -f scando *.o
