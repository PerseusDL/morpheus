#include <stdio.h>
#include "beta_smk.h"

main()
{
	int c;
	char line[256];
	char result[256];

	while((c=getchar()) != EOF ) {
		if( c == '\r' ) {
			putchar('\n');
			continue;
		}
		smk2beta(c,result);
		printf("%s", result );
	}
}

static int smkinited = 0;
char Xlit_table[257][6];

smk2beta(c,result)
int c;
char * result;
{
	if( !smkinited ) {
		smkinited++;
		init_smk();
	}
	strcpy(result,Xlit_table[c]);
}

init_smk()
{
	int i;
	char tmp[80];

	for(i=0;i<sizeof Beta_SMK/sizeof Beta_SMK[0];i++) {
		strcpy(Xlit_table[Beta_SMK[i].keycode],Beta_SMK[i].keystring);
printf("%d) Xlit_table [%s]\n", Beta_SMK[i].keycode , Xlit_table[Beta_SMK[i].keycode] );
	}
		
	for(i=0;i<256;i++) {
		if( ! Xlit_table[i][0] )
			sprintf(Xlit_table[i] , "%c", i );
	}

}
