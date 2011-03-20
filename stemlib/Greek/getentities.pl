#!/usr/bin/perl

open FIN, "< stemsrc/entitylist-byhand.txt";

while(<FIN>) {
	@fields = split /\s+/;
	$curlem = @fields[0];

	if( /ethnic/ ) {
		$is_ethnicname{$curlem}++;
	}

	if( /person|pers_name/ ) {
		$is_persname{$curlem}++;
	}
	
	if( /geogname|geog_name|place/ ) {
		$is_geogname{$curlem}++;
	}
	
	if( /groupname|group_name|group\b/ ) {
		$is_groupname{$curlem}++;
	}
	
	if( /month/ ) {
print STDERR "month $curlem\n";
		$is_monthname{$curlem}++;
	}
	
	if( /festival/ ) {
		$is_festival{$curlem}++;
	}

	if( /buildingname|building_name/ ) {
		$is_buildingname{$curlem}++;
	}

	if( /constellation/ ) {
		$is_constellation{$curlem}++;
	}

	$totalkeys{$curlem}++;
}

close FIN;

$/ = ":le";

while(<>) {
	next unless /^:(.+)/;
	$curlem = $1;
	$curlem =~ s#,.+##g;

	if( /ethnic/ ) {
		$is_ethnicname{$curlem}++;
	}

	if( /person|pers_name/ ) {
		$is_persname{$curlem}++;
	}
	
	if( /geogname|geog_name/ ) {
		$is_geogname{$curlem}++;
	}
	
	if( /groupname|group_name/ ) {
		$is_groupname{$curlem}++;
	}
	
	if( /month/ ) {
		$is_month{$curlem}++;
	}
	
	if( /buildingname|building_name/ ) {
		$is_buildingname{$curlem}++;
	}
	if( /constellation/ ) {
		$is_constellation{$curlem}++;
	}
	if( /festival/ ) {
		$is_festival{$curlem}++;
	}

	$totalkeys{$curlem}++;
	
}

foreach my $tmps (sort keys % totalkeys) {
		next unless ($is_persname{$tmps} or $is_geogname{$tmps} or $is_ethnicname{$tmps} or $is_groupname{$tmps} or $is_buildingname{$tmps} or $is_monthname{$tmps} or $is_festival{$tmps} or $is_constellation{$tmps});

		print "$tmps";
		if( $is_persname{$tmps} ) {
			print "\tperson";
		}

		if( $is_ethnicname{$tmps} ) {
			print "\tethnic";
		}

		if(  $is_geogname{$tmps} ) {
			print "\tplace";
		}

		if(  $is_groupname{$tmps} ) {
			print "\tgroup";
		}

		if(  $is_buildingname{$tmps} ) {
			print "\tbuilding";
		}

		if(  $is_monthname{$tmps} ) {
			print "\tmonth";
		}

		if(  $is_festival{$tmps} ) {
			print "\tfestival";
		}

		if(  $is_constellation{$tmps} ) {
			print "\tconstellation";
		}
		print "\n";
}
