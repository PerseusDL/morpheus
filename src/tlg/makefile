BINDIR=/greek/tar/tlgsend/bin
CC=gcc
GREEKLIB=../greeklib/greeklib.a
RM=/bin/rm
#note that you need to define SYS5 if you are compiling under
#system 5.
#CFLAGS=-O -DSYS5

tlg_wsplit: tlg_wsplit.o ${GREEKLIB}
	${CC} -o tlg_wsplit tlg_wsplit.o ${GREEKLIB}

clean:
	${RM}  -f tlg_wsplit tlg_wsplit.o

install: tlg_wsplit
	cp tlg_wsplit ${BINDIR}
