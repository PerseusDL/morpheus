
/* vaxwords.c */
int get_int32(int32 *, FILE *);
int put_int32(int32 *, FILE *);
int get_double(double *, int, FILE *);
int put_double(double *, int, FILE *);
int get_short(unsigned short *, FILE *);
int put_short(short *, FILE *);
int vax_fread(char *, size_t, int, FILE *);
int vax_fwrite(char *, size_t, int, FILE *);
