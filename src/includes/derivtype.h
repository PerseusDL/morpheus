
typedef unsigned int Derivtype;

#define Is_primconj(gstr)  (derivtype_of(gstr) & PRIM_DERIV)
#define Is_regconj(gstr)  (derivtype_of(gstr) & REG_DERIV)
