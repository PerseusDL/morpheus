#include <greek.h>
#include <prntflags.h>

char* get_all_syllables(char* word, int which);
int basic_quantity(char* word, char* p_syll);

/* get quantities of all the syllables in a word, not just 
   the ones relevant to Greek accentuation */
int fullquantity(char* word, int syll, bool is_ending, bool is_oblique)
{
	char*	p_syll;

	p_syll = get_all_syllables(word, syll);

	if (p_syll == P_ERR)
	  return (I_ERR);

	p_syll++;
	if (*p_syll && Is_quant(*p_syll))
	{
	  if ( (*p_syll) == HARDLONG)
	    return (LONG);
	  else if ( (*p_syll) == HARDSHORT)
	    return (SHORT);
	  else
	    return(-1);		/* should not happen */
	}
	else
	{
	  -- p_syll;	/* back to the vowel */
	  return(basic_quantity(word, p_syll));
	}
}

void mark_long(char* word)
{
	char* p_pos = word;
	for ( ; *p_pos;  p_pos ++)
	{
	  if (*p_pos == CIRCUMFLEX)
	    *p_pos = HARDLONG;
	}
}

char* get_all_syllables(char* word, int which)
{
	char*	p_pos;
	int	syllcount = 0;

	for (p_pos = lastn(word, 1); p_pos >= word; p_pos--)
	{
	  if (Is_vowel(*p_pos))
	  {
	    if (syllcount == which)
	    {
	      return(p_pos);
	    }
	    if (! is_diphth(*p_pos, word))
	      ++ syllcount;
	  }
	}
	return(P_ERR);	/* out of range */
}

int basic_quantity(char* word, char* p_syll)
{
	char*	p_pos;
	int	cons_count = 0;

	if (p_syll == P_ERR)
	  return(I_ERR);

	p_pos = p_syll;
	while (*p_pos && !Is_cons(*p_pos))
	{
	  if (*p_pos == HARDLONG)
	    return(LONG);
	  else if (*p_pos == HARDSHORT)
	    return(SHORT);
	  ++ p_pos;
	}

	if (long_by_isub(p_syll))
	  return(LONG);

/* for metrical purposes, even short final -ai can be long */
	if (is_diphth(p_syll, word))
	  return(LONG);

	if (cur_lang() == GREEK && Is_lvwl(*p_syll))
	  return(LONG);
	else if (Is_shvwl(*p_syll))
	{
	  if (*(p_syll + 1) == SUBSCR)
	    return (LONG);
	  else
	  {
	    p_pos = p_syll + 1;	/* next after the vowel */
	    while (*p_pos)
	    {
	      if (Is_accent(*p_pos) || Is_breath(*p_pos))
	      {
		++ p_pos;
		continue;
	      }
	      if (Is_cons(*p_pos))
	      {
		++ cons_count;
		if (cur_lang() == GREEK)
		{
		  if (*p_pos == 'c' || *p_pos == 'y')
	  	    ++ cons_count;	/* double consonant in one letter */
		}
		else if (cur_lang() == LATIN)
		{
		   if (*p_pos == 'x')
		      ++ cons_count;
		}
	      }
	      else
		break;
	      ++ p_pos;
	    }
	    if (cons_count >= 2)
	      return (LONG);
	    else
	      return (SHORT);
	  }
	}
	return(I_ERR);
}
