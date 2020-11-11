#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifdef __GNUC__

/* Esta macro detiene "gcc -Wall" quejándose de que
   'el control llega al fin de la función no nula' si usamos
   las siguientes funciones para terminar main() o alguna
   otra función no nula */

#define NORETURN __attribute__ ((__noreturn__))

/* Este atributo le dice al compilador que la función nunca
   regresará, y esto se puede usar para suprimir errores sobre
   rutas de código que no se alcanzan.*/

#else
#define NORETURN
#endif

void errExit(const char *format, ...) NORETURN ;
void err_exit(const char *format, ...) NORETURN ;
void errExitEN(int errnum, const char *format, ...) NORETURN ;
void fatal(const char *format, ...) NORETURN ;
void usageErr(const char *format, ...) NORETURN ;
void cmdLineErr(const char *format, ...) NORETURN ;

#endif
