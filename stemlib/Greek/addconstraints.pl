#!/usr/bin/perl
open FIN, "< stemsrc/entitylist-byhand.txt";

while(<FIN>) {
	@fields = split /\s+/;
	$curlem = @fields[0];

	$curtype{$curlem} = @fields[1];		
}

while(<>) {

	if( /:le:(.+)/ ) {
		$curlemma = $1;
		$curlemma =~ s#\s+$##g;
	}

	if( /^:no:/ and $curtype{$curlemma} =~ /person/ and ! /pers_name/ ) {
		$sent2 = $_;
		$sent2 =~ s#(.+)#$1 is_group#;
		s#(.+)#$1 pers_name#;
	}

#personal names are by default singular
	if( /pers_name/ and ! /\bsg/  ) {
		s#(pers_name)#$1 sg#g;
	}
	print;

	if(/:no.+pers_name/ ) {
		$groupv = $_;
		$savev = $groupv;
		$groupv =~ s#pers_name#is_group#;
		$groupv =~ s#\bsg\b#pl#;
		print ":le:$curlemma-pl\n$groupv\n$curlemma\n";
	
		$groupv = $savev;
		$groupv =~ s#\bsg\b#dual#;
		print ":le:$curlemma-pl\n$groupv\n$curlemma\n";
	}
}
