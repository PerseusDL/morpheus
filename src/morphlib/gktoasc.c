char gktoasc[]= {
/*	alpha */	'a',	'a' + 01,
/*	beta */		'b',	'a' + 02,
/*	gamma */	'g',	'a' + 03,
/*	delta */	'd',	'a' + 04,
/*	epsilon */	'e',	'a' + 05,
/*	zeta */		'z',	'a' + 06,
/* 	eta */		'h',	'a' + 07,
/*	theta */	'q',	'a' + 010,
/*	iota */		'i',	'a' + 011,
/*	iota sub */	'|',	'a' + 012,
/*	kappa */	'k',	'a' + 013,
/*	lambda */	'l',	'a' + 014,
/*	mu */		'm',	'a' + 015,
/*	nu */		'n',	'a' + 016,
/* 	xi */		'c',	'a' + 017,
/* 	omicron */	'o',	'a' + 020,
/*	pi */		'p',	'a' + 021,
/*	rho */		'r',	'a' + 022,
/*	terminal sigma */	'v',	'a' + 023,
/*	medial sigma */	's',	'a' + 024,
/*	lunate sigma */	'j',	'a' + 025,
/*	tau */		't',	'a' + 026,
/*	upsilon */	'u',	'a' + 027,
/*	phi */		'f',	'a' + 030,
/*	chi */		'x',	'a' + 031,
/*	psi */		'y',	'a' + 032,
/*	omega */	'w',	'a' + 033,
};


set_gkorder( s )
register char * s;
{
	int i;

	for(i=0;i< sizeof gktoasc;) {
		s[ gktoasc[ i ] ] = gktoasc[ i+1 ] ;
		i += 2;
	}
}
		
