LSJDIR=/local/text/lsj

all: ends noms vbs deriv

ends: nends vends

nends:
	buildend nom
	indendtables nom

vends:
	buildend verb
	indendtables verb

compnoms:
	cat stemsrc/nom.* stemsrc/nom[0-9]* > /usr/tmp/nommorph
	indexcomps < /usr/tmp/nommorph | sort | compcomps > /usr/tmp/nom.heads

deriv:
	buildderiv all
	indderivtables

noms:stemsrc/nom.irreg stemind/nomind lsj.morph

vbs: stemsrc/vbs.irreg stemind/vbind

stemind/vbind:
	cat stemsrc/vbs.irreg stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new > conjfile
	do_conj 
	mv conjfile.short /usr/tmp/vbmorph
	indexvbs

stemsrc/nom.irreg: stemsrc/irreg.nom.src
	buildword < stemsrc/irreg.nom.src > stemsrc/nom.irreg

stemsrc/vbs.irreg: stemsrc/irreg.vbs.src
	buildword < stemsrc/irreg.vbs.src > stemsrc/vbs.irreg

stemsrc/lemlist:
	cat stemsrc/nom.* stemsrc/nom[0-9]* stemsrc/vbs.irreg stemsrc/vbs.simp.ml stemsrc/vbs.simp.02.new | fgrep ":le:" | cut -d":" -f 3 | sort | awk '{print $$1 " "}' > stemsrc/lemlist
	

stemind/nomind:	
	cat stemsrc/nom.* stemsrc/nom[0-9]*  stemsrc/lsj.nom stemsrc/lsj.byhand > /usr/tmp/nommorph
	cat stemsrc/pnom* | stemsrc/dopnom >> /usr/tmp/nommorph
	indexnoms

ia.noms:
	echo "[aehuwo]i h_hs" > /usr/tmp/skip.ia
	echo ":wd:" >> /usr/tmp/skip.ia
	cat stemsrc/nom0[1-6] | fgrep "i h_hs" | egrep -v -f /usr/tmp/skip.ia > /usr/tmp/ia.noms
	findbase < /usr/tmp/ia.noms > /usr/tmp/ia.base
	fgrep 0 /usr/tmp/ia.base | awk '{print $$1}' | rev | sort -d | rev > /usr/tmp/ia.failed

lsj.morph: ${LSJDIR}/lemmata
	sed -e 's/\-//' ${LSJDIR}/lemmata | setquant | splitlems | newlems | fgrep -v "1 " | fgrep -v ": " | newlems2 > /usr/tmp/lsj.morph
	cp /usr/tmp/lsj.vbs stemsrc
	fgrep -v "0:" /usr/tmp/lsj.morph > stemsrc/lsj.nom
	cp /usr/tmp/lsj.morph .
