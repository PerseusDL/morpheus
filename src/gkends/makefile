INCLUDE=../includes
CFLAGS= -O2 -I${INCLUDE}  
RM=rm
ENDLIB=gkends.a
CC=cc
CC=gcc


GREEKLIB=../greeklib/greeklib.a
MORPHLIB=../morphlib/morphlib.a
LIBS=${ENDLIB} ${MORPHLIB} ${GREEKLIB} 
ENDOBJ= acccompos.o \
checkforbreath.o \
contract.o \
countendtables.o \
endindex.o \
euphend.o \
expendtable.o \
fixeta.o \
getcurrend.o \
indexendtables.o \
lcontr.o \
merge.o \
mkend.o \
nextsufftab.o \
retrends.o \
stor.o 

${ENDLIB}: ${ENDOBJ}
	ar -rv ${ENDLIB} ${ENDOBJ}
	ranlib ${ENDLIB}

ALL=buildword buildend indderivtables indendtables buildderiv ${ENDLIB}

all: ${ALL}

install: all
	cp ${ALL} ../../bin


buildword: expwordmain.o ${ENDOBJ} ${LIBS}
	${CC} -o buildword expwordmain.o ${ENDOBJ} ${LIBS}

buildend: expendmain.o ${ENDOBJ} ${LIBS}
	${CC} -o buildend expendmain.o ${ENDOBJ} ${LIBS}

indderivtables: smain.o ${ENDOBJ} ${LIBS}
	${CC} -o indderivtables smain.o ${ENDOBJ} ${LIBS}

indendtables: imain.o ${ENDOBJ} ${LIBS}
	${CC} -o indendtables imain.o ${ENDOBJ} ${LIBS}

buildderiv: expsuffmain.o ${ENDOBJ} ${LIBS}
	${CC} -o buildderiv expsuffmain.o ${ENDOBJ} ${LIBS}

clean:
	rm -f *.o
