morpheus
========

Morpheus parser code.

Compiling and installing morpheus
---------------------------------

By default morpheus installs into bin/
```
  cd src
  make
  make install
```
Compiling a stem library
------------------------
```
  cd stemlib/Latin
  export PATH=$PATH:../../bin
  MORPHLIB=.. make
```
Running the cruncher
--------------------
```
MORPHLIB=stemlib bin/cruncher < wordlist > crunched
```
