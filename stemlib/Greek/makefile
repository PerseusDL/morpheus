CC= gcc
CFLAGS= -O2
LSJDIR=/local/text/lsj

STEMPROG= stemsrc/dopnom stemsrc/stripref stemsrc/zapfirstf stemsrc/headnolen \
	stemsrc/goodstem stemsrc/flatlems

all: $(STEMPROG) ends noms vbs deriv

ends: nends vends

nends:
	buildend nom
	indendtables nom

vends:
	buildend verb
	indendtables verb

compnoms:
	cat stemsrc/nom.* stemsrc/nom[0-9]* > /tmp/nommorph
	indexcomps < /tmp/nommorph | sort | compcomps > /tmp/nom.heads

deriv:
	buildderiv all
	indderivtables

noms:	stemsrc/nom.irreg stemind/nomind

vbs:	stemsrc/lsj.vbs stemsrc/vbs.irreg stemind/vbind

stemind/vbind:
	cat stemsrc/vbs.irreg stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new \
	    > conjfile
	do_conj 
	mv conjfile.short /tmp/vbmorph
	indexvbs

stemsrc/nom.irreg:	stemsrc/irreg.nom.src
	buildword < stemsrc/irreg.nom.src > stemsrc/nom.irreg

stemsrc/vbs.irreg:	stemsrc/irreg.vbs.src
	buildword < stemsrc/irreg.vbs.src > stemsrc/vbs.irreg

stemsrc/lemlist:
	cat stemsrc/nom.* stemsrc/nom[0-9]* stemsrc/vbs.irreg \
	    stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new | fgrep ":le:" | \
	    cut -d":" -f 3 | sort | awk '{print $$1 " "}' > stemsrc/lemlist

stemind/nomind:	stemsrc/dopnom stemsrc/lsj.nom
	cat stemsrc/nom.* stemsrc/nom[0-9]*  stemsrc/lsj.nom \
	    stemsrc/lsj.byhand > /tmp/nommorph
	cat stemsrc/pnom* | stemsrc/dopnom >> /tmp/nommorph
	indexnoms

ia.noms:
	echo "[aehuwo]i h_hs" > /tmp/skip.ia
	echo ":wd:" >> /tmp/skip.ia
	cat stemsrc/nom0[1-6] | fgrep "i h_hs" | \
	    egrep -v -f /tmp/skip.ia > /tmp/ia.noms
	findbase < /tmp/ia.noms > /tmp/ia.base
	fgrep 0 /tmp/ia.base | awk '{print $$1}' | rev | sort -d | \
	    rev > /tmp/ia.failed

stemsrc/lsj.nom stemsrc/lsj.vbs:
	[ -f ${LSJDIR}/lemmata ] && ${MAKE} lsj.morph

lsj.morph:	${LSJDIR}/lemmata
	sed -e 's/\-//' ${LSJDIR}/lemmata | setquant | splitlems | newlems | \
	    fgrep -v "1 " | fgrep -v ": " | newlems2 > /tmp/lsj.morph
	cp /tmp/lsj.vbs stemsrc
	fgrep -v "0:" /tmp/lsj.morph > stemsrc/lsj.nom
	cp /tmp/lsj.morph .
