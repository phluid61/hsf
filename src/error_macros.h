#ifndef _ERROR_MACROS_H_
#define _ERROR_MACROS_H_

/* FIXME: __cascade could be better ... */
#define __cascade(v,x)  { if ((int*)0 != (v) && 0 != *(v)) return x; }
#define __clear(v)      { if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR; }
#define __raise(v,code) { if ((int*)0 != (v)) *(v) = (code); }

#endif
