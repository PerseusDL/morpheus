INCLUDE=../includes
CFLAGS= -O2   -I${INCLUDE}
MORPHLIB=morphlib.a
RM=rm
CC=cc
CC=gcc

MORPHOBJ= adddomain.o \
addninfix.o \
antepenform.o \
augment.o \
beta2rtf.o \
beta2smarta.o \
cmpend.o \
conjstem.o \
endio.o \
errormess.o \
fixacc.o \
gkstring.o \
gktoasc.o \
indkeys.o \
is_thirdmono.o \
loadeuph.o \
markstem.o \
morphflags.o \
morphkeys.o \
morphpath.o \
morphstrcmp.o \
new_val.o \
nextkey.o \
numovable.o \
penultform.o \
pres_redup.o \
preverb.o \
preverb2.o \
preverb3.o \
retrentry.o \
setlang.o \
smk2beta.o \
sprntGkflags.o \
standphon.o \
trimwhite.o \
ultform.o \
ulttakescirc.o 

${MORPHLIB}: ${MORPHOBJ}
	ar rv ${MORPHLIB} ${MORPHOBJ}
	ranlib ${MORPHLIB}

betasort: betasort.o morphstrcmp.o gktoasc.o
	${CC} -o betasort betasort.o morphstrcmp.o  gktoasc.o

clean:
	rm -f *.o

testkey: tmain.o ${MORPHLIB} ../greeklib/greeklib.a
	${CC} -o testkey tmain.o  ${MORPHLIB} ../greeklib/greeklib.a

printcodes:	printcodes.o
	$(CC) -o $@ printcodes.o morphlib.a ../greeklib/greeklib.a

