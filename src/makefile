all:
	cd greeklib; make greeklib.a
	cd morphlib; make morphlib.a
	cd gkdict; make all
	cd gkends; make all
	cd gener; make all
	cd anal; make all

install:
	cd gkdict; make install
	cd gkends; make install
	cd gener; make install
	cd anal; make install

clean:
	cd anal; make clean
	cd gener; make clean
	cd gkdict; make clean
	cd gkends; make clean
	cd greeklib; make clean
	cd morphlib; make clean

libs:
	cd gener; make gener.a
	cd gkdict; make gkdict.a
	cd gkends; make gkends.a
	cd greeklib; make greeklib.a
	cd morphlib; make morphlib.a
