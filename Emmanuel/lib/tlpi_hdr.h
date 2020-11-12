#ifndef TLPI_HDR_H
#define TLPI_HDR_H     /* Evitar la dobre inclusión accidental */

#include <sys/types.h> /* Definiciones de tipos utilizados por muchos programas*/
#include <stdio.h>     /* Funciones de E/S estandar */
#include <stdlib.h>    /* Prototipos de funciones de bibloteca de uso común \
			  más las constantes EXIT_SUCCESS y EXIT_FAILURE */
#include <unistd.h>    /* Prototipo para muchas llamadas al sistema */
#include <errno.h>     /* Declara errno y define las constantes de error */
#include <string.h>    /* Funciones de manejo de cadenas de uso común */

#include "get_num.h"   /* Declara nuestras funciones para manejar argumentos \
			  numerícos (getint() y getlong()) */
#include "error_functions.h" /* Declara nuestras funciones de manejo de error */

typedef enum {FALSE, TRUE} Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif
