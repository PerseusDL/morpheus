INCLUDE=../includes
CFLAGS= -O2 -I${INCLUDE}
LIB=greeklib.a
RM=rm
CC=cc
CC=gcc

GRKLIBOBJ = Fclose.o \
addaccent.o \
addbreath.o \
aspirate.o \
beta_tolower.o \
binlook.o \
checkaccent.o \
cinsert.o \
do_dissim.o \
endsinstr.o \
getaccent.o \
getaccp.o \
getbreath.o \
getquantity.o \
getsyll.o \
gkstrlen.o \
hasaccent.o \
hasdiaer.o \
hasquant.o \
isblank.o \
isdiphth.o \
issubstring.o \
keyio.o \
longbyposition.o \
naccents.o \
normucase.o \
nsylls.o \
quantprim.o \
shortanalog.o \
standalpha.o \
standword.o \
stripacc.o \
stripacute.o \
stripbreath.o \
stripchar.o \
stripdiaer.o \
stripmeta.o \
stripquant.o \
stripstemsep.o \
stripzeroend.o \
strsqz.o \
subchar.o \
vaxwords.o \
sprntGkflags.o \
xstrings.o \
zap2ndbreath.o 

${LIB}: ${GRKLIBOBJ}
	ar rv ${LIB} ${GRKLIBOBJ}
	ranlib ${LIB}

clean:
	rm -f *.o


iotest: io.o vaxwords.o
	${CC} -o iotest io.o vaxwords.o
