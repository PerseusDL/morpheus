morpheus
========

Tufts University holds the overall copyright to the Perseus Digital Library; the materials therein 
(including all texts, translations, images, descriptions, drawings, etc.) are provided for the 
personal use of students, scholars, and the public. 

Materials within the Perseus DL have varying copyright status: please contact the project for more information 
about a specific component or object.  Copyright is protected by the copyright laws of the United States and 
the Universal Copyright Convention. 

Unless otherwise indicated, all contents of this repository are licensed under a 
Creative Commons Attribution-ShareAlike 3.0 United States License. You must offer Perseus
any modifications you make. 

Morpheus parser code.
====================

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
