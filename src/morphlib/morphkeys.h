#include "gkstring.h"
#include "morphargs.h"
#include "libfiles.h"

struct {
	char 	class_name[MAXWORDSIZE];
	long 	class_num;
	}  arg_stemclass[] = {
		
		"adj1",	 		ADJSTEM|DECL1|DECL2,
		"adj2",			ADJSTEM|DECL1|DECL2,
		"adj3",			ADJSTEM|DECL3,
		"noun1",	 		NOUNSTEM|DECL1,
		"noun2",			NOUNSTEM|DECL2,
		"noun3",			NOUNSTEM|DECL3,
		"noun4",			NOUNSTEM|DECL4,
		"noun5",			NOUNSTEM|DECL5,
		"indecl1",		INDECL|NOUNSTEM|DECL1,
		"indecl2",		INDECL|NOUNSTEM|DECL2,
		"indecl3",		INDECL|NOUNSTEM|DECL3,
		"pron1",		INDECL|NOUNSTEM|DECL1|DECL2,
		"pron3",		INDECL|NOUNSTEM|DECL3,
		"pp_pr",		PP_PR,
		"pp_fu",		PP_FU,
		"pp_ao",		PP_AO,
		"pp_pf",		PP_PF,
		"pp_pp",		PP_PP,
		"pp_ap",		PP_AP,
		"pp_fp",		PP_FP,
		"pp_p4",		PP_SU,
		"pp_va",		PP_VA,
		"pp_vn",		PP_VN,
		"verbstem",		VERBSTEM,
		"prim_deriv",	(VERBSTEM|PRIM_CONJ),
		"reg_deriv",	(VERBSTEM|REG_CONJ),
		"indecl",		INDECL,
		0,
};

Morph_args arg_degree[] = {
	"comp",		COMPARATIVE, new_degree,
	"comparative",	COMPARATIVE, new_degree,
	"superl",	SUPERLATIVE, new_degree,
	"superlative",	SUPERLATIVE, new_degree,
	0,
};

Morph_args arg_person[] = {
	"1st",		PERS1, new_person,
	"first",	PERS1, new_person,
	"pers1",	PERS1, new_person,
	"2nd",		PERS2, new_person,
	"second",	PERS2, new_person,
	"pers2",	PERS2, new_person,
	"3rd",		PERS3, new_person,
	"third",	PERS3, new_person,
	"pers3",	PERS3, new_person,
	0,
};

Morph_args arg_morphflags[] = {
	"syll_augment",	SYLL_AUGMENT,	new_morphflags,
	"syll_aug",	SYLL_AUGMENT,	new_morphflags,
	"comp_only",	COMP_ONLY,	new_morphflags,
	"not_in_comp",	NOT_IN_COMPOSITION,	new_morphflags,
	"enclitic",	ENCLITIC,	new_morphflags,
	"proclitic",	PROCLITIC,	new_morphflags,
	"iterative",	ITERATIVE,	new_morphflags,
	"ant_acc",	ANT_ACC,	new_morphflags,
	"stem_acc",	STEM_ACC,	new_morphflags,
	"pen_acc",	STEM_ACC,	new_morphflags,
	"suff_acc",	SUFF_ACC,	new_morphflags,
	"ult_acc",	SUFF_ACC,	new_morphflags,
	"rec_acc",	REC_ACC,	new_morphflags,
	"needs_acc",	NEEDS_ACCENT,	new_morphflags,
	"contr",	CONTRACTED,	new_morphflags,
	"contracted",	CONTRACTED,	new_morphflags,
	"uncontr",		UNCONTR_END,	new_morphflags,
	"uncontr_end",		UNCONTR_END,	new_morphflags,
	"uncontracted",	UNCONTR_END,	new_morphflags,
	"uncontr_stem",		UNCONTR_STEM,	new_morphflags,
	"pers_name",	PERS_NAME,	new_morphflags,
	"prevb_aug",	PREVB_AUGMENT,	new_morphflags,
	"prevb_augment",	PREVB_AUGMENT,	new_morphflags,
	"double_aug",	DOUBLE_AUGMENT,	new_morphflags,
	"double_augment",	DOUBLE_AUGMENT,	new_morphflags,
	"no_comp",	NO_COMP,	new_morphflags,
	"irreg_comp",	IRREG_COMP,	new_morphflags,
	"irrcomp",	IRREG_COMP,	new_morphflags,
	"irreg_superl",	IRREG_SUPERL,	new_morphflags,
	"irrsuperl",	IRREG_SUPERL,	new_morphflags,
	"short_pen",	SHORT_PEN,	new_morphflags,
	"long_pen",	LONG_PEN,	new_morphflags,
	"r_e_i_alpha",	R_E_I_ALPHA,	new_morphflags,
	"unaugmented",	UNAUGMENTED,		new_morphflags,
	"apocope",	APOCOPE,		new_morphflags,
	"has_augment",	HAS_AUGMENT,	new_morphflags,
	"nu_movable",	NU_MOVABLE,		new_morphflags,
	"interv_s_to_h",	INTERV_S_TO_H,	new_morphflags,
	"poetic",			POETIC,					new_morphflags,
	"dissimilation", 	DISSIMILATION, 			new_morphflags,
	"metath", 			METATHESIS, 			new_morphflags,
	"metathesis", 		METATHESIS,			 	new_morphflags,
	"elide_preverb",	ELIDE_PREVERB,			new_morphflags,
	"root_preverb",		ROOT_PREVERB,			new_morphflags,
	"diminutive", 		DIMINUTIVE,				new_morphflags,
	"early", 			EARLY,					new_morphflags,
	"late", 			LATE,					new_morphflags,
	"rare", 			RARE,					new_morphflags,
	"raw_preverb", 		RAW_PREVERB,			new_morphflags,
	"short_subj", 		SHORT_SUBJ,				new_morphflags,
	"unasp_preverb", 	UNASP_PREVERB,			new_morphflags,
	"redupl", 			REDUPL,					new_morphflags,
	"attic_redupl", 	ATTIC_REDUPL,			new_morphflags,
	"is_deriv", 		IS_DERIV,				new_morphflags,
	"no_redupl", 		NO_REDUPL,				new_morphflags,
	"n_infix", 			N_INFIX,				new_morphflags,
	"syncope", 			SYNCOPE,				new_morphflags,
	"impersonal", 		IMPERSONAL,				new_morphflags,
/*
 * the following keywords was commented out and we could not generate
 * indeclinables! i did not explain why the line was commented out. for now, i put
 * it back and hope for the best.
 *
 * grc 5/16/92
 */
	"indeclform",		INDECLFORM,				new_morphflags,

	"needs_rbreath",	NEEDS_RBREATH,				new_morphflags,
	"no_circumflex",	NO_CIRCUMFLEX,				new_morphflags,
	"causal",			CAUSAL,					new_morphflags,
	"intrans",			INTRANS,					new_morphflags,
	"tmesis",			TMESIS,					new_morphflags,
	"raw_sonant",			RAW_SONANT,	new_morphflags,
	"prodelision",			PRODELISION,					new_morphflags,
	"frequentat",			FREQUENTAT,					new_morphflags,
	"frequentative",			FREQUENTAT,					new_morphflags,
	"desiderative",			DESIDERATIVE,					new_morphflags,
	"impers",			IMPERSONAL,					new_morphflags,
	"later",			LATER,					new_morphflags,
	"double_redupl",			DOUBLE_REDUPL,					new_morphflags,
	"pres_redupl",			PRES_REDUPL,					new_morphflags,
	"ends_in_dig",			ENDS_IN_DIGAMMA,					new_morphflags,
	"ends_in_digamma",			ENDS_IN_DIGAMMA,					new_morphflags,
	"geog_name",			GEOG_NAME,					new_morphflags,
	"doubled_cons",			DOUBLED_CONS,					new_morphflags,
	"iota_intens",			IOTA_INTENS,					new_morphflags,
	"sig_to_ci",			SIG_TO_CI,					new_morphflags,
	"short_eis",			SHORT_EIS,					new_morphflags,
	"pros_to_poti",			PROS_TO_POTI,		new_morphflags,
	"pros_to_proti",			PROS_TO_PROTI,		new_morphflags,
	"meta_to_peda",			META_TO_PEDA,		new_morphflags,
	"upo_to_upai",			UPO_TO_UPAI,		new_morphflags,
	"para_to_parai",		PARA_TO_PARAI,		new_morphflags,
	"uper_to_upeir",		UPER_TO_UPEIR,		new_morphflags,
	"en_to_eni",			EN_TO_ENI,		new_morphflags,
	"a_priv",			A_PRIV,		new_morphflags,
	"a_copul",			A_COPUL,	new_morphflags,
	"metrical_long",			METRICAL_LONG,	new_morphflags,
	0,
};


Morph_args arg_gender[] = {
	"masc",		MASCULINE,		new_gender,
	"masculine",	MASCULINE,	new_gender,
	"fem",		FEMININE,		new_gender,
	"feminine",	FEMININE,		new_gender,
	"neut",		NEUTER,		new_gender,
	"neuter",	NEUTER,		new_gender,
	"masc/neut",	MASCULINE|NEUTER,		new_gender,
	"masc/fem",	MASCULINE|FEMININE,		new_gender,
	"masc/fem/neut",	MASCULINE|FEMININE|NEUTER,		new_gender,
	"common",		MASCULINE|FEMININE|NEUTER,		new_gender,
	"adverbial",	ADVERBIAL,		new_gender,
	0,
};

Morph_args arg_case[] = {
	"nom/voc",	NOMINATIVE|VOCATIVE,		new_case,
	"nom/acc",	NOMINATIVE|ACCUSATIVE,		new_case,
	"nom/voc/acc",	NOMINATIVE|VOCATIVE|ACCUSATIVE,		new_case,
	"gen/dat",	GENITIVE|DATIVE,		new_case,
	"nom",		NOMINATIVE,		new_case,
	"nominative",	NOMINATIVE,		new_case,
	"gen",		GENITIVE,		new_case,
	"genitive",	GENITIVE,		new_case,
	"abl/dat",	ABLATIVE|DATIVE,	new_case,
	"dat/abl",	ABLATIVE|DATIVE,	new_case,
	"ablative/dative",	ABLATIVE|DATIVE,	new_case,
	"dative/ablative",	ABLATIVE|DATIVE,	new_case,
	"abl",		ABLATIVE,		new_case,
	"ablative",	ABLATIVE,		new_case,
	"dat",		DATIVE,			new_case,
	"dative",	DATIVE,			new_case,
	"acc",		ACCUSATIVE,		new_case,
	"accusative",	ACCUSATIVE,		new_case,
	"voc",		VOCATIVE,		new_case,
	"voctive",	VOCATIVE,		new_case,
	0,
};

Morph_args arg_number[] = {
	"sg",		SINGULAR,	new_number,
	"sing",		SINGULAR,	new_number,
	"singular",	SINGULAR,	new_number,
	"pl",		PLURAL,	new_number,
	"plural",	PLURAL,	new_number,
	"dual",		DUAL,	new_number,
	0,
};

Morph_args arg_tense[] = {
	"pres",			PRESENT,	new_tense,
	"present",		PRESENT,	new_tense,
	"fut",			FUTURE,	new_tense,
	"future",		FUTURE,	new_tense,
	"aor",			AORIST,	new_tense,
	"aorist",		AORIST,	new_tense,
	"perf",			PERFECT,	new_tense,
	"perfect",		PERFECT,	new_tense,
	"imperf",		IMPERF,	new_tense,
	"imperfect",		IMPERF,	new_tense,
	"plup",			PLUPERF,	new_tense,
	"pluperfect",		PLUPERF,	new_tense,
	"futperf",		FUTPERF,	new_tense,
	"futperfect",		FUTPERF,	new_tense,
	"pastabs",		PASTABSOLUTE,	new_tense,
	"pastabsolute",		PASTABSOLUTE,	new_tense,
	0,
};

Morph_args arg_voice[] = {
	"mid",			MIDDLE,		new_voice,
	"middle",		MIDDLE,		new_voice,
	"act",			ACTIVE,		new_voice,
	"active",		ACTIVE,		new_voice,
	"pass",			PASSIVE,	new_voice,
	"passive",		PASSIVE,	new_voice,
	"dep",			ACTIVE|MIDDLE,	new_voice,
	"mp",			MEDIO_PASS,	new_voice,
	"medio_pass",		MEDIO_PASS,	new_voice,
	"medio-pass",		MEDIO_PASS,	new_voice,
	0,
};

Morph_args arg_mood[] = {
	"ind",			INDICATIVE,			new_mood,
	"indic",		INDICATIVE,			new_mood,
	"indicative",		INDICATIVE,			new_mood,
	"subj",			SUBJUNCTIVE,			new_mood,
	"subjunc",		SUBJUNCTIVE,			new_mood,
	"subjunctive",		SUBJUNCTIVE,			new_mood,
	"part",			PARTICIPLE,			new_mood,
	"partic",		PARTICIPLE,			new_mood,
	"participle",		PARTICIPLE,			new_mood,
	"opt",			OPTATIVE,			new_mood,
	"optat",		OPTATIVE,			new_mood,
	"optative",		OPTATIVE,			new_mood,
	"imperat",		IMPERATIVE,			new_mood,
	"imperative",		IMPERATIVE,			new_mood,
	"inf",			INFINITIVE,			new_mood,
	"infin",		INFINITIVE,			new_mood,
	"infinitive",		INFINITIVE,			new_mood,
	"gerundive",		GERUNDIVE,			new_mood,
	"supine",		SUPINE,				new_mood,
	"cond",		CONDITIONAL,				new_mood,
	"conditional",		CONDITIONAL,				new_mood,
	0,

};

/* dialects */

Morph_args arg_dialect[] = {
	"attic",		ATTIC,		new_dialect,
	"att",			ATTIC,		new_dialect,
	"epic",			EPIC,		new_dialect,
	"homeric",		HOMERIC,		new_dialect,
	"non_homeric_epic",	NON_HOMERIC_EPIC,		new_dialect,
	"doric",		DORIC,		new_dialect,
	"ionic",		IONIC,		new_dialect,
	"aeolic",		AEOLIC,		new_dialect,
	"parad_form",	PARADIGM,	new_dialect,
	"all_dial",		ALL_DIAL,		new_dialect,
/*	"need_not_aug",		HOMERIC,		new_dialect,*/
	"ionic/homeric",	IONIC|HOMERIC,		new_dialect,
/*
	"eo_eu_dial",		IONIC|HOMERIC,		new_dialect,
	"eo_ou_dial",		ATTIC,		new_dialect,
	"no_contr_fut",		HOMERIC|IONIC,		new_dialect,
	"ee_ee_dial",		(~ATTIC),		new_dialect,
	"eo_eo_dial",		(~ATTIC),		new_dialect,
	"eou_eou_dial",		(~ATTIC),		new_dialect,
	"ew_ew_dial",		(~ATTIC),		new_dialect,
	"un_contr",		(~ATTIC),		new_dialect,
	"a_no_contr",		HOMERIC|DORIC,		new_dialect,
*/
	"prose",		PROSE,		new_dialect,
/*
	"laconian",		LACONIAN,		new_dialect,
*/
	0,
};

/* Geographical Regions */

Morph_args arg_geogregion[] = {
	"phocis",		PHOCIS,		new_region,
	"locris",		LOCRIS,		new_region,
	"elis",	  		ELIS,		new_region,
	"locris", 		LOCRIS,		new_region,
	"laconia",		LACONIA,	new_region,
	"heraclea",		HERACLEA,	new_region,
	"megarid",		MEGARID,	new_region,
	"argolid",		ARGOLID,	new_region,
	"rhodes",		RHODES,		new_region,
	"cos",			COS,		new_region,
	"thera",		THERA,		new_region,
	"cyrene",		CYRENE,		new_region,
	"crete",		CRETE,		new_region,
	"arcadia",		ARCADIA,	new_region,
	"cyprus",		CYPRUS,		new_region,
	"boeotia",		BOEOTIA,		new_region,
	0,

};


Morph_args * arg_stemtype = NULL;
Morph_args * arg_derivtype = NULL;
Morph_args * arg_domain = NULL;

Morph_args *MatchMorphKey(char *);
Morph_args *InitStemSuffs(char *, void (*curfunc )(), Stemtype (*classfunc )(), int *);
int keycomp2(char *, Morph_args **);
int add_keyarr(Morph_args **, Morph_args *);
