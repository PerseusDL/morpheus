/* metrical scanner mainline */
#include <stdio.h>

#include <gkstring.h>

#define ARGS "IL"
#define BUFFER_LEN 256
#define SCANSION_LEN 30

#define BREVE 'u'
#define MACRON '-'
#define ANCEPS 'x'
#define UNDETERMINED '?'

int fullquantity(char* word, int syll, bool is_ending, bool is_oblique);
void mark_long(char* word);

int main(int argc, char* argv[])
{
	char	buffer[BUFFER_LEN];
	char	opt;
	int	idx;
	int	quant;
	int	pos;
	char	scansion[SCANSION_LEN];

	while ((opt = getopt(argc, argv, ARGS)) != -1)
	{
	  switch(opt)
	  {
	    case 'I':
	      set_lang(ITALIAN);
	      break;
	    case 'L':
	      set_lang(LATIN);
	      break;
	    default:
	      break;	/* ignore if unrecognized */
	  }
	}

	while (fgets(buffer, BUFFER_LEN, stdin))
	{
	  trimwhite(buffer);
	  if (isspace(buffer[0]))
	    continue;
	  if (buffer[0] == '#')
	  {
	    fprintf(stdout, "%s\n", buffer);
	    continue;
	  }

	  mark_long(buffer);
	  memcpy(scansion, NULL, 0);
	  for (idx = 0, pos = nsylls(buffer) - 1;  idx < nsylls(buffer);  idx ++, pos --)
	  {
	    quant = fullquantity(buffer, idx, NO, NO);
	    switch (quant)
	    {
	      case LONG:
		scansion[pos] = MACRON;
		break;
	      case SHORT:
		scansion[pos] = BREVE;
		break;
	      case I_ERR:
	      default:
		scansion[pos] = UNDETERMINED;
		break;
	    }
	  }
	  scansion[idx] = 0;
	  fprintf(stdout, "scansion:  %s\n", scansion);
	}

	exit(0);
}
