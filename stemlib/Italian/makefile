SGMLPATH= $(dir $(SGML_CATALOG_FILES))/..
VPATH=.:$(SGMLPATH)/texts/MPI/baretti:$(SGMLPATH)/texts/MPI/florio
LSDIR=/local/text/ls
LOADLIBES= -lfl

all: ends noms vbs deriv

ends: nends vends

nends:
	buildend -I nom
	indendtables -I nom

vends:
	buildend -I verb
	indendtables -I verb

compnoms:
	cat stemsrc/nom.* stemsrc/nom[0-9]* > /tmp/nommorph
	indexcomps < /tmp/nommorph | sort | compcomps > /tmp/nom.heads

deriv:
	buildderiv -I all
	indderivtables -I

noms:	stemind/nomind 

#vbs:	stemsrc/vbs.irreg stemind/vbind
vbs:	stemind/vbind

VBFILES=stemsrc/vbs.latin.bas stemsrc/vbs.latin.irreg stemsrc/vbs.latin \
	stemsrc/vbs.irreg stemsrc/vbs.mpi

stemind/vbind:	stemsrc/vbs.basic stemsrc/vbs.italian
	cat stemsrc/vbs.basic stemsrc/vbs.italian > conjfile
	do_conj -I 
	mv conjfile.short /tmp/vbmorph
	indexvbs -I

stemsrc/nom.irreg: stemsrc/irreg.nom.src
	buildword -I < stemsrc/irreg.nom.src > stemsrc/nom.irreg

stemsrc/vbs.irreg: stemsrc/irreg.vbs.src
	buildword -I < stemsrc/irreg.vbs.src > stemsrc/vbs.irreg

stemsrc/vbs.italian:	baretti.sgml barmorph vbsep
	./barmorph $< | ./vbsep 'vb' > $@

stemsrc/nom.italian:	baretti.sgml barmorph vbsep
	./barmorph $< | ./vbsep 'no' > $@

#stemsrc/vbs.italian: florio.sgml getmorph getverb
#	getmorph < $<  | getverb > $@

#stemsrc/nom.italian: florio.sgml getmorph getverb
#	getmorph < $<  | getverb noun > $@

stemsrc/lemlist:
	cat stemsrc/nom.* stemsrc/nom[0-9]* stemsrc/vbs.irreg \
	    stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new | fgrep ":le:" | \
	    cut -d":" -f 3 | sort | awk '{print $$1 " "}' > stemsrc/lemlist

stemind/nomind:	stemsrc/nom.it.irreg stemsrc/nom.italian
	cat stemsrc/nom.* > /tmp/nommorph
	indexnoms -I

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
	cruncher -IV /tmp/ls.cvbs
	cvblink < /tmp/ls.cvbs.morph | sort -u > stemsrc/vbs.cmp.ml

/tmp/nt: latnom splitlems
	splitlems < /local/text/ls/lemmata | latnom > /tmp/lat
	getitype < /tmp/lat | sort | uniq -c | sort -rn > /tmp/nt
