/* morphological peculiarities */

/*typedef unsigned long MorphFlags;*/
typedef unsigned char MorphFlags;
#define MORPHFLAG_BYTES 12
#define MORPHFLAG_MASK			0377

#define	SYLL_AUGMENT		1
#define	COMP_ONLY			2
#define	ENCLITIC			3
#define	ITERATIVE			4
/* 5-8 */
#define SUFF_ACC			5
#define STEM_ACC			6
#define CONTRACTED 			7
#define PERS_NAME			8
/* 9-12 */
#define ANT_ACC				9
#define IRREG_SUPERL		10
#define IRREG_COMP			11
#define NO_COMP				12
/* 13-16 */
#define SHORT_PEN			13
#define LONG_PEN			14
#define REC_ACC				15
#define ACCENT_OPTIONAL		16
/* 17-20 */
#define NEEDS_ACCENT		17
#define R_E_I_ALPHA			18
#define NOT_IN_COMPOSITION	19
#define HAS_PREVERB			20
/* 21-24 */
#define UNAUGMENTED			21
#define	DISSIMILATION		22
#define PROCLITIC			23
#define APOCOPE				24
/* 25-28 */
#define IRREGFORM			25
#define HAS_AUGMENT			26
#define QUANT_METATHESIS	27
#define NU_MOVABLE			28
/* 29 */
#define INTERV_S_TO_H		29
#define PREVB_AUGMENT		30
#define POETIC				31
#define UNCONTR_STEM		32
/* 33 - 36 */
#define METATHESIS			33
#define ELIDE_PREVERB		34
#define INDECLFORM			35
#define ROOT_PREVERB		36
#define DIMINUTIVE			37
#define LATE				38
#define RARE				39
#define RAW_PREVERB			40
#define EARLY				41
#define SHORT_SUBJ			42
#define UNASP_PREVERB		43
#define REDUPL				44
#define UNCONTR_END			45
#define IS_DERIV			46
#define ATTIC_REDUPL		47
#define NO_REDUPL			48
#define N_INFIX				49
#define SYNCOPE				50
#define IMPERSONAL			51
#define NEEDS_RBREATH		52
#define NO_CIRCUMFLEX		53
#define CAUSAL				54
#define INTRANS				55
#define TMESIS				56
#define RAW_SONANT			57
#define PRODELISION			58
#define FREQUENTAT			59
#define LATER				60
#define DOUBLE_AUGMENT		61
#define DOUBLE_REDUPL		62
#define DESIDERATIVE		63
#define PRES_REDUPL			64
#define ENDS_IN_DIGAMMA		65
#define GEOG_NAME			66
#define DOUBLED_CONS		67
#define IOTA_INTENS			68
#define LOST_ACC			69
#define SIG_TO_CI			70
#define SHORT_EIS			71
#define PROS_TO_POTI		72
#define META_TO_PEDA		73
#define PROS_TO_PROTI		74
#define UPO_TO_UPAI			75
#define PARA_TO_PARAI		76
#define UPER_TO_UPEIR		77
#define EN_TO_ENI			78
#define A_PRIV			79
#define A_COPUL			80
#define METRICAL_LONG		81
#define D_PREVB		82
#define T_PREVB		83

#define morphflags_of( X ) (X)->gs_morphflags


#define syll_augment(X) (has_morphflag(X,SYLL_AUGMENT))
#define skip_augment(X) (has_morphflag(X,UNAUGMENTED))
#define Is_rho_eta_form(gs) (has_morphflag(gs,R_E_I_ALPHA))
/*#define Set_rho_eta_form(gs) (add_morphflag(gs,R_E_I_ALPHA))*/
#define Is_enclitic(gs) (has_morphflag(gs,ENCLITIC))
#define Is_proclitic(gs) (has_morphflag(gs,PROCLITIC))
#define Comp_only(gs) (has_morphflag(gs,COMP_ONLY))
#define Not_in_compos(gs) (has_morphflag(gs,NOT_IN_COMPOSITION))
#define Has_preverb(gs) (has_morphflag(gs,HAS_PREVERB))
#define Has_augment(gs) (has_morphflag(gs,HAS_AUGMENT))
#define Is_antepen_accent(gs) (has_morphflag(gs,ANT_ACC))
#define Is_penult_accent(gs) (has_morphflag(gs,STEM_ACC))
#define Is_ultima_accent(gs) (has_morphflag(gs,SUFF_ACC))
#define Is_pers_name(gs) (has_morphflag(gs,PERS_NAME))
#define Is_geog_name(gs) (has_morphflag(gs,GEOG_NAME))
#define Needs_accent(gs) (has_morphflag(gs,NEEDS_ACCENT))

#define Is_irregcomp(gs) (has_morphflag(gs,IRREG_COMP))
#define Is_irregsuperl(gs) (has_morphflag(gs,IRREG_SUPERL))
#define Is_irregform(gs) (has_morphflag(gs,IRREGFORM))
#define Is_indeclform(gs) (has_morphflag(gs,INDECLFORM))
#define Has_nocomp(gs)  (has_morphflag(gs,NO_COMP))
#define Accent_optional(gs) (has_morphflag(gs,ACCENT_OPTIONAL))
#define Has_apocope(gs) (has_morphflag(gs,APOCOPE))

#define Is_contracted(gs) (has_morphflag(gs,CONTRACTED))
#define has_long_pen(gs) (has_morphflag(gs,LONG_PEN))
#define has_short_pen(gs) (has_morphflag(gs,SHORT_PEN))

#define has_prevb_augment(gs) (has_morphflag(gs,PREVB_AUGMENT))
#define has_dissimilation(gs) (has_morphflag(gs,DISSIMILATION))
#define elide_preverb(gs) (has_morphflag(gs,ELIDE_PREVERB))

#define Has_numovable(gs) (has_morphflag(gs,NU_MOVABLE))
#define Keep_rawpreverb(gs) (has_morphflag(gs,RAW_PREVERB))

#define Has_unasp_preverb(gs) (has_morphflag(gs,UNASP_PREVERB))

#define Is_deriv(gs) (has_morphflag(gs,IS_DERIV))

