all:
	cd greeklib; $(MAKE) greeklib.a
	cd morphlib; $(MAKE) morphlib.a
	cd gkends; $(MAKE) all
	cd gkdict; $(MAKE) all
	cd gener; $(MAKE) all
	cd anal; $(MAKE) all

install:
	[ -d ../bin ] || mkdir ../bin
	cd gkdict; $(MAKE) install
	cd gkends; $(MAKE) install
	cd gener; $(MAKE) install
	cd anal; $(MAKE) install

clean:
	cd anal; $(MAKE) clean
	cd gener; $(MAKE) clean
	cd gkdict; $(MAKE) clean
	cd gkends; $(MAKE) clean
	cd greeklib; $(MAKE) clean
	cd morphlib; $(MAKE) clean

libs:
	cd gener; $(MAKE) gener.a
	cd gkdict; $(MAKE) gkdict.a
	cd gkends; $(MAKE) gkends.a
	cd greeklib; $(MAKE) greeklib.a
	cd morphlib; $(MAKE) morphlib.a
