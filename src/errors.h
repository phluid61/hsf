#ifndef _SH_ERRORS_H_
#define _SH_ERRORS_H_

/*
 * item                             0x0010____
 * integer                          0x0011____
 * decimal                          0x0012____
 * string                           0x0013____
 * token                            0x0014____
 * bytesequence                     0x0015____
 * boolean                          0x0016____
 *
 * key                              0x0020____
 *
 * list                             0x0030____
 *
 * sys err                          0x8000____
 */

#define SH_E_NO_ERROR               0x00000000

#define SH_E_NULL_POINTER           0x00000001

#define SH_E_ITEM_WRONG_TYPE        0x00100001
#define SH_E_PARAMETERS_OVERFLOW    0x00100002

#define SH_E_INTEGER_OUT_OF_BOUNDS  0x00110001

#define SH_E_DECIMAL_OUT_OF_BOUNDS  0x00120001

#define SH_E_STRING_TOO_LONG        0x00130001
#define SH_E_STRING_BAD_CHAR        0x00130002

#define SH_E_TOKEN_TOO_LONG         0x00140001
#define SH_E_TOKEN_BAD_CHAR         0x00140002

#define SH_E_BYTESEQUENCE_TOO_LONG  0x00150001

#define SH_E_KEY_TOO_LONG           0x00200001
#define SH_E_KEY_BAD_CHAR           0x00200002

#define SH_E_LIST_OVERFLOW          0x00300001

/* errno */
#define SH_E_MALLOC_ERROR           0x80000001

#endif
/* vim: set ts=4 sts=4 sw=4: */
