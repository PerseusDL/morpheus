INCLUDE=.
#use hc on RT
#CC=hc
CC=cc
CC=gcc
#CFLAGS= -O -I${INCLUDE}   -g
CFLAGS= -O -I${INCLUDE}  
LINTFLAGS= -I${INCLUDE} -DDEBUG
LIBS=../curses/libcurses -ltermcap
LIB= gen.a
RM=/bin/rm

ALLSRC=	ssbuffer.c ssearch.c token.c queue.c stack.c rstack.c dassign.c

ALL=	ssbuffer.o ssearch.o token.o queue.o stack.o rstack.o dassign.o

MALL=	m_ssbuffer m_ssearch m_token m_queue m_stack m_rstack m_dassign

GK_SRC= gk_sprint.c troff_greek.c avt_greek.c \
	mact_greek.c gkkey_greek.c signf_greek.c beta_tab.c ileaf_greek.c \
	hft_greek.c nb_greek.c macint_greek.c

GK_SPRINT= gk_sprint.o troff_greek.o avt_greek.o \
	mact_greek.o gkkey_greek.o signf_greek.o beta_tab.o ileaf_greek.o \
	hft_greek.o nb_greek.o rtf_greek.o macint_greek.o

install: ${LIB}

${LIB}:	${ALL} ${GK_SPRINT}
	${RM}  -f ${LIB} 
	ar rv ${LIB} ${ALL} ${GK_SPRINT}
#make sure that you use ranlib if compiling under BSD
#	ranlib ${LIB}
	touch ${MALL}

lint:
	${RM}  -f lintlog
	lint ${LINTFLAGS} ${ALLSRC} ${GK_SRC} > lintlog

gk_sprint: test.o gen.a
	${CC} -o gk_sprint test.o gen.a

beta_troff: beta_troff.o gen.a
	${CC} -o beta_troff beta_troff.o gen.a

m_ssbuffer:	ssbuffer.o
	ar rv ${LIB} ssbuffer.o
	touch m_ssbuffer

m_ssearch:	ssearch.o
	ar rv ${LIB} ssearch.o
	touch m_ssearch

l_ssearch:
	lint ${LINTFLAGS} ssearch.c

m_token:	token.o
	ar rv ${LIB} token.o
	touch m_token

m_queue:	queue.o
	ar rv ${LIB} queue.o
	touch m_queue

m_stack:	stack.o
	ar rv ${LIB} stack.o
	touch m_stack

m_rstack:	rstack.o
	ar rv ${LIB} rstack.o
	touch m_rstack

m_dassign:	dassign.o
	ar rv ${LIB} dassign.o
	touch m_dassign

ttest:	ttest.o m_token m_queue
	${CC} -o ttest ttest.o ${LIB}

qtest:	qtest.o m_queue
	${CC} -o qtest qtest.o ${LIB}

rstest:	rstest.o m_rstack
	${CC} -o rstest rstest.o ${LIB}

stest:	stest.o m_stack
	${CC} -o stest stest.o ${LIB}
print:
	src_print ${INCLUDE}/*.h ${ALLSRC} | fpc

clean:
	${RM}  -f *.o *.a gk_sprint


ssbuffer.o:	${INCLUDE}/ssearch.h

ssearch.o:	${INCLUDE}/datatypes.h ${INCLUDE}/usual.h ${INCLUDE}/token.h \
		${INCLUDE}/ssearch.h

token.o:	${INCLUDE}/datatypes.h ${INCLUDE}/usual.h ${INCLUDE}/token.h

queue.o:	${INCLUDE}/datatypes.h ${INCLUDE}/usual.h

stack.o:	${INCLUDE}/datatypes.h ${INCLUDE}/usual.h

rstack.o:	${INCLUDE}/datatypes.h ${INCLUDE}/usual.h

dassign.o:	${INCLUDE}/datatypes.h
