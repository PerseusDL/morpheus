#include <gkstring.h>

set_sampleform(keys)
char * keys;
{
	word_form wf;
	gk_string * gstr;
	gk_string * avoidgstr;
	
	gstr = CreatGkString(1);
	avoidgstr = CreatGkString(1);
	
	ScanAsciiKeys(keys,gstr,avoidgstr,NULL,NULL);
	wf = forminfo_of(avoidgstr);
	if( person_of(wf) || number_of(wf) || mood_of(wf) || tense_of(wf) || voice_of(wf) || case_of(wf) )
		return;
		
	wf = forminfo_of(gstr);
	
	if( Is_verbform(gstr) ) {
		if( ! person_of(wf) ) {
			strcat(keys," 1st");
		if( ! number_of(wf) )
			strcat(keys," sing");
		if( ! mood_of(wf) )
			strcat(keys," ind");
		if( ! voice_of(wf) )
			strcat(keys," act");
	}
	if( ! tense_of(wf) ) {
			switch(stemtype_of(gstr) ) {
				case W_STEM:
				case EW_PR:
				case AW_PR:
				case OW_PR:
				case EMI_PR:
				case AMI_PR:
				case OMI_PR:
				case UMI_PR:
					strcat(keys," pres");
					break;
				case AOR_PASS:
				case AOR2_PASS:
				case AOR1:
				case AOR2:
				case EMI_AOR:
				case AMI_AOR:
				case OMI_AOR:
				case UMI_AOR:
					strcat(keys," aor");
					break;
				case	PERF_ACT:
				case	PERF2_ACT:
				case	PERFP_G:
				case	PERFP_GX:
				case	PERFP_L:
				case	PERFP_MP:
				case	PERFP_N:
				case	PERFP_P:
				case	PERFP_S:
				case	PERFP_VOW:
				case	PERF_ACT:
				case	PERFP_R:
				case PERF_ACT:
					strcat(keys," perf");
					break;
			    default:
			    		break;
			    }
		}
}
