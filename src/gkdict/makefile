LEX=flex
INCLUDE=../includes
MORPHLIB= ../morphlib/morphlib.a
GREEKLIB= ../greeklib/greeklib.a
GKENDS=../gkends/gkends.a
DICTLIB=gkdict.a

DICTOBJ=dictio.o derivio.o compnoun.o

#use hc on RT
#CC=hc
CC=cc
CC=gcc
#CFLAGS= -O -I${INCLUDE}   -g
#CFLAGS= -O -I${INCLUDE}   -Wstrict-prototypes   -Wmissing-prototypes
CFLAGS= -O2 -I${INCLUDE}   
LINTFLAGS= -I${INCLUDE} -DDEBUG
RM=/bin/rm -f

LOADLIBES= -lfl

ALL=gkdict.a indexcomps indexnoms indexvbs  newlems newlems2 setquant splitlems splitlat latvb conj1 combitype latnom fixhesc fixgend

lexer= combitype fixhesc latnom setquant splitlems conj1 getitype latvb splitlat fixgend

all: ${ALL}

install: ${ALL}
	cp  ${ALL} ../../bin

indexcomps:  indcomps.o  ${MORPHLIB} ${GREEKLIB}
	${CC} -o indexcomps  indcomps.o  ${MORPHLIB} ${GREEKLIB}

indexnoms:	indexnoms.main.o indexstems.o  ${MORPHLIB} ${GREEKLIB}
	${CC} ${CFLAGS} -o indexnoms indexnoms.main.o indexstems.o ${MORPHLIB} ${GREEKLIB}

indexvbs:	indexvbs.main.o indexstems.o ${MORPHLIB} ${GREEKLIB}
	${CC} -o indexvbs indexvbs.main.o indexstems.o ${MORPHLIB} ${GREEKLIB}

newlats:	newlats.o  ${MORPHLIB} ${GREEKLIB} ${GKENDS}
	${CC} -o newlats newlats.o  ${GKENDS} ${MORPHLIB} ${GREEKLIB} 

newlems:	newlems.o  ${MORPHLIB} ${GREEKLIB} ${GKENDS}
	${CC} -o newlems newlems.o  ${GKENDS} ${MORPHLIB} ${GREEKLIB} 

newlems2:	newlems2.o  ${MORPHLIB} ${GREEKLIB}
	${CC} -o newlems2 newlems2.o  ${MORPHLIB} ${GREEKLIB}

xx:	x.o  ${MORPHLIB} ${GREEKLIB}
	${CC} -o xx x.o  ${MORPHLIB} ${GREEKLIB}

${DICTLIB}: ${DICTOBJ}
	ar rv ${DICTLIB} ${DICTOBJ}
	ranlib ${DICTLIB}

clean:
	rm -f *.o ${ALL}

/tmp/nt: latnom splitlems
	splitlems < /local/text/ls/lemmata | fixhesc | fgrep -v vtags  | latnom > /tmp/lat
	getitype < /tmp/lat | sort | uniq -c | sort -rn > /tmp/nt

