
np_scan: getmtok.o t.y
	yacc -d t.y
	cc -o np_scan y.tab.c getmtok.o ../greeklib/greeklib.a -ly 
