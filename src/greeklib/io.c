#include <stdio.h>
typedef unsigned int int32;
main()
{
        FILE * f;
        int32 tmp = 0;
        int32 i;
        unsigned short x;
        int c;
        char bufc[4];
        int n = 1;

        f=fopen("fred","wb");



        for(i=0;i<4;i++) {
                tmp += (1+i) << (8 * i);
                x += (1+(short)i) << (8 * i);
printf("%o %o\n", tmp , x);
        }
        x = tmp;
/*
        fwrite(&tmp,sizeof tmp,1,f);
        fwrite(&x,sizeof x,1,f);
*/
        put_int32(&tmp,f);
        put_short(&x,f);
        fclose(f);

        f=fopen("fred","rb");
        get_int32(&tmp,f);
        get_short(&x,f);
	printf("%o %o\n", tmp , x );
        fclose(f);
	

}
