INCLUDE=../includes
MORPHLIB= ../morphlib/morphlib.a
GREEKLIB= ../greeklib/greeklib.a
ENDLIB= ../gkends/gkends.a
GENERLIB= gener.a

GENEROBJ= genwd.o 

#use hc on RT
#CC=hc
CC=cc
CC=gcc
#CFLAGS= -O -I${INCLUDE}   -g
CFLAGS= -O2 -I${INCLUDE}
LINTFLAGS= -I${INCLUDE} -DDEBUG
RM=/bin/rm
CONJOBJ= conjmain.o conjsys.o combconj.o ppasstype.o

ALL=do_conj gener checkstype ${GENERLIB}

all: ${ALL}

install: all
	cp ${ALL} ../../bin

${GENERLIB}: ${GENEROBJ}
	ar rv ${GENERLIB} ${GENEROBJ}
	ranlib ${GENERLIB}

do_conj: ${CONJOBJ} ${ENDLIB} ${MORPHLIB} ${GREEKLIB} 
	${CC} -o do_conj ${CONJOBJ} ${ENDLIB} ${MORPHLIB} ${GREEKLIB}

checkstype: stypemain.o  ${MORPHLIB} ${GREEKLIB}
	${CC} -o checkstype stypemain.o ${MORPHLIB} ${GREEKLIB}

genstem: genstmain.o genstemform.o gensynform.o  genwd.o genmisc.o  ${ENDLIB} ${MORPHLIB} ${GREEKLIB}
	${CC} -o genstem genstmain.o genstemform.o gensynform.o genwd.o genmisc.o  ${ENDLIB} ${MORPHLIB} ${GREEKLIB}

gener: genermain.o gensynform.o  genwd.o genmisc.o  ${ENDLIB} ${MORPHLIB} ${GREEKLIB}
	${CC} -o gener genermain.o gensynform.o genwd.o genmisc.o  ${ENDLIB} ${MORPHLIB} ${GREEKLIB}

clean:
	rm -f *.o

