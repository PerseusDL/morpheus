#if using CD ROM define the CDFS driver to be used:
#Simulate/driver.o for testing, Real/driver.o for real
#CDFSDVR=/usr/CDFS/Real/driver.o
RM=/bin/rm
#use hc on RT
#CC=hc
CC=cc
CC=gcc
INSTALL=cp
TLGBIN=../../bin

UTILS=sopfuncs.o 

UTILSRC=sopfuncs.c 

DUMPWORD=${UTILS} marker.o dumpword.o showword.o

SRCHLIB=srch.a
AUTOLIB=../auto/gen.a
CDFSLIB=/usr/CDFS/cdfs.a
GREEKLIB=../greeklib/greeklib.a
LIBS=${SRCHLIB} ${AUTOLIB} ${CDFSDVR} ${CDFSLIB} ${GREEKLIB}

SRCHOBJ= \
errmess.o \
filefuncs.o \
getgrec.o \
gkcomp.o \
putrec.o \
reffuncs.o \
scanindex.o \
scanauthor.o \
picksearch.o \
linear.o \
grklist.o \
marker.o \
strings.o \
stripdiacrit.o \
iscommon.o \
worksetup.o

CIRCOBJ=circle.o \
context.o \
initwords.o \
betaform.o 

ALL=tlg_sel

all=${ALL}

install: tlg_sel
	${INSTALL} ${ALL} ${TLGBIN}

#if using the automaton functions make sure that your CFLAGS includes
#this option
#CFLAGS=-I../auto -I.

#make sure that you use ranlib if running under Berkeley 4.X
${SRCHLIB}: ${SRCHOBJ} ${CIRCOBJ}
	${RM} -f ${SRCHLIB} 
	ar rv ${SRCHLIB} ${SRCHOBJ} ${CIRCOBJ}
# 	ranlib ${SRCHLIB}


getref: getref.o refmain.o ${UTILS} ${SRCHLIB} 
	${CC} -o getref getref.o refmain.o ${UTILS} ${SRCHLIB} ../auto/gen.a


#tlg_sel with cdfs
#CFLAGS=-I. -I../auto -DAUTOMATON=1 -DCDFS=1 
#tlg_sel: ${UTILS} selmain.o ${LIBS}
#	${CC} -o tlg_sel ${UTILS} selmain.o ${LIBS}

#tlg_sel without cdfs
CFLAGS=-I. -I../auto -DAUTOMATON=1 -DCDFS=0
tlg_sel: ${UTILS} selmain.o ${SRCHLIB} ../auto/gen.a 
	${CC} -o tlg_sel ${UTILS} selmain.o ${SRCHLIB} ../auto/gen.a ${GREEKLIB}

tlg_spell: ${UTILS} spellmain.o ${SRCHLIB} ../auto/gen.a 
	${CC} -o tlg_spell ${UTILS} spellmain.o ${SRCHLIB} ../auto/gen.a 

getfld: ${UTILS} getfld.o ${SRCHLIB} ../auto/gen.a 
	${CC} -o getfld ${UTILS} getfld.o ${SRCHLIB} ../auto/gen.a 


#
# shortsel is a simple version of tlg_sel that uses neither the 
# CDFS code, nor the routines in ../auto/gen.a. it is useful if
# you want to port to a new  environment and don't want to solve 
# every problem at once.
#     to create this, first get rid of all your object files 
# ("make clean" should do the trick). make sure you have
# the appropriate CFLAGS set
#
#CFLAGS=-DAUTOMATON=0 -DCDFS=0
shortsel:${UTILS} selmain.o ${SRCHOBJ} 
	${CC} -o shortsel ${UTILS} selmain.o ${SRCHOBJ}

#
# autosel is an intermediate version of tlg_sel: it uses ../auto/gen.a,
# but *not* the CDFS code. to compile it, run "make clean",
#
#CFLAGS=-I. -I../auto -DAUTOMATON=1 -DCDFS=0
autosel: ${UTILS} selmain.o ${SRCHOBJ} ${CIRCOBJ} ../auto/gen.a 
	${CC} -o autosel ${UTILS} selmain.o ${SRCHOBJ} ${CIRCOBJ} ../auto/gen.a 


dumpword: ${DUMPWORD} ${LIBS}
	${CC} -o dumpword ${DUMPWORD} ${LIBS}

grktest: grktest.o grklist.o
	${CC} -o grktest grktest.o grklist.o

worktest: worktest.o ${UTILS}
	${CC} -o worktest worktest.o ${UTILS}

clean:
	${RM}  -f *.o ${SRCHLIB} tlg_sel shortsel autosel getref *.bak 
