LSDIR=/local/text/ls

all: ends noms vbs deriv

ends: nends vends

nends:
	buildend -L nom
	indendtables -L nom

vends:
	buildend -L verb
	indendtables -L verb

compnoms:
	cat stemsrc/nom.* stemsrc/nom[0-9]* > /tmp/nommorph
	indexcomps < /tmp/nommorph | sort | compcomps > /tmp/nom.heads

deriv:
	buildderiv -L all
	indderivtables -L

noms:	stemsrc/nom.irreg stemind/nomind 

vbs:	stemsrc/vbs.irreg stemind/vbind

VBFILES=stemsrc/vbs.latin.bas stemsrc/vbs.latin.irreg stemsrc/vbs.latin \
	stemsrc/vbs.irreg

stemind/vbind:	stemsrc/vbs.latin
	cat ${VBFILES} | \
	    perl -pe 's/([a-z])([aei])_v[ \t]+perfstem/$$1\t$$2vperf/g;' > \
	    conjfile
	do_conj -L
	mv conjfile.short /tmp/vbmorph
	indexvbs -L

stemsrc/nom.irreg: stemsrc/irreg.nom.src
	buildword -L < stemsrc/irreg.nom.src > stemsrc/nom.irreg

stemsrc/vbs.irreg: stemsrc/irreg.vbs.src
	buildword -L < stemsrc/irreg.vbs.src > stemsrc/vbs.irreg

stemsrc/lemlist:
	cat stemsrc/nom.* stemsrc/nom[0-9]* stemsrc/vbs.irreg \
	    stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new | fgrep ":le:" | \
	    cut -d":" -f 3 | sort | awk '{print $$1 " "}' > stemsrc/lemlist

stemind/nomind:	stemsrc/ls.nom
	cat stemsrc/nom.* stemsrc/ls.nom > /tmp/nommorph
	indexnoms -L

ia.noms:
	echo "[aehuwo]i h_hs" > /tmp/skip.ia
	echo ":wd:" >> /tmp/skip.ia
	cat stemsrc/nom0[1-6] | fgrep "i h_hs" | \
	    egrep -v -f /tmp/skip.ia > /tmp/ia.noms
	findbase < /tmp/ia.noms > /tmp/ia.base
	fgrep 0 /tmp/ia.base | awk '{print $$1}' | rev | sort -d | \
	    rev > /tmp/ia.failed

stemsrc/ls.nom stemsrc/vbs.latin:
	-[ -f ${LSDIR}/lemmata ] && ${MAKE} ls.morph

ls.morph:	${LSDIR}/lemmata
	fgrep ":le:" stemsrc/vbs.latin.bas | cut -d: -f3 | \
	    sort > stemsrc/lemmata
#	sed -e 's/\-//' ${LSDIR}/lemmata |  combitype | splitlat | conj1 | \
#	    fgrep -f vtags | latvb > ls.vbs
#	cat ${LSDIR}/lemmata |  combitype | splitlat | conj1 | \
#	    fgrep -f vtags | latvb | \
#	    perl -pe 's/(^\:le\:[A-Za-z]+)\-([A-Za-z])/$1$2/g' > ls.vbs
	cat ${LSDIR}/lemmata |  combitype | splitlat | conj1 | \
	    fgrep -f vtags | latvb > ls.vbs
	splitlems < ${LSDIR}/lemmata |  fixhesc | fgrep -v -f vtags | \
	    fgrep -v "<pos>P. a.</pos>" |  fixgend | latnom > /tmp/ls.morph
	egrep -e "^:" ls.vbs > stemsrc/vbs.latin
	fgrep -v "0:" /tmp/ls.morph > stemsrc/ls.nom
	cp /tmp/ls.morph .

simp.vbs:
#	sed -e 's/\-//' ${LSDIR}/lemmata |  combitype | splitlat | conj1 | fgrep -f vtags | fgrep -f hyph -v | latvb > ls.simp.vbs
#	sed -e 's/\-//' ${LSDIR}/lemmata |  combitype | splitlat | conj1 | fgrep -f vtags | fgrep -f hyph | latvb | filtcomp > /tmp/ls.cvbs.words
	sed -e 's/\-//' ${LSDIR}/lemmata |  combitype | splitlat | awk '{print $$1}' > /tmp/ls.cvbs.words
	rm -f stemsrc/vbs.cmp.ml
	cruncher -LV /tmp/ls.cvbs
	cvblink < /tmp/ls.cvbs.morph | sort -u > stemsrc/vbs.cmp.ml

/tmp/nt: latnom splitlems
	splitlems < /local/text/ls/lemmata | latnom > /tmp/lat
	getitype < /tmp/lat | sort | uniq -c | sort -rn > /tmp/nt
