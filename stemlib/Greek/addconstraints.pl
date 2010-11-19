#!/usr/bin/perl

while(<>) {

#personal names are by default singular
	s#(pers_name)#$1 sg#g;
	print;
}
