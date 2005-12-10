#!/usr/bin/perl

while(<>) {
	if( /<head>([^<]+)/ ) {
		$curlemma = $1;
		$curlemma =~ s#\s+#-#g;
	}
	if( /<p>(:(aj|no):.+)/ ) {
		print "\n:le:$curlemma\n$1\n";
	}
}
