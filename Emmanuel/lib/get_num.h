#ifndef GET_NUM_H

#define GET_NUM_H
#define GN_NONNEG 01             /* El valor debe ser >= 0 */
#define GN_GT_0 02               /* El valor debe ser > 0 */

                                /* Por defecto, los entero son decimales */
#define GN_ANY_BASE 0100              /* Podemos usar cuálquie base - como strtol(3) */
#define GN_BASE_8 0200                /* El valor es expresado en octal */
#define GN_BASE_16 0400               /* El valor es expresado en decímal */

long getLong(const char *arg, int flags, const char *name);
int getInt(const char *arg, int flags, const char *name);

#endif
