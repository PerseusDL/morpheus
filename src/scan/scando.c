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

int	quickflag = 0;	/* required by checkstring */

int fullquantity(char* word, int syll, bool is_ending, bool is_oblique);
void mark_long(char* word);

int main(int argc, char* argv[])
{
	char	buffer[BUFFER_LEN];
	char	work_buffer[BUFFER_LEN];
	char	lemma[BUFFER_LEN];
	char	opt;
	PrntFlags	flags = (PERSEUS_FORMAT | STRICT_CASE);
	int	idx;
	int	quant;
	int	pos;
	gk_word*	base_word = NULL;
	char	scansion[SCANSION_LEN];

	while ((opt = getopt(argc, argv, ARGS)) != -1)
	{
	  switch(opt)
	  {
	    case 'I':
	      fprintf(stderr, "Italian is not supported:  it does not use quantitative meter\n");
	      exit(4);
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

	  base_word = (gk_word*)CreatGkword(1);
	  set_dialect(base_word, ALL_DIAL);
	  set_workword(base_word, buffer);
	  set_prntflags(base_word, flags);
	  set_rawword(base_word, workword_of(base_word));
	  standword(workword_of(base_word));
	  stand_phonetics(base_word);
	  checkstring1(base_word);
	  switch (totanal_of(base_word))
	  {
	    case 1:	/* this is the easy case */
	      strcpy(work_buffer, workword_of(analysis_of(base_word)));
	      strcpy(lemma, lemma_of(analysis_of(base_word)));
	      break;
	    case 0:	/* problem:  not a word? */
	      strcpy(work_buffer, workword_of(base_word));
	      lemma[0] = 0;
	      break;
	    default:	/* problem:  which one is it? */
	      strcpy(work_buffer, workword_of(analysis_of(base_word)));
	      strcpy(lemma, lemma_of(analysis_of(base_word)));
	      break;
	  }
	  fprintf(stderr, "analyzed:  %s from %s\n", work_buffer, lemma);

	  memcpy(scansion, NULL, 0);
	  for (idx = 0, pos = nsylls(work_buffer) - 1;  idx < nsylls(work_buffer);  idx ++, pos --)
	  {
	    quant = fullquantity(work_buffer, idx, NO, NO);
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
