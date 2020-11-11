#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"  /* Defines ename and MAX_ENAME */

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif

static void
terminate(Boolean useExit3)
{
	char *s;

	/* Volcar el núcleo si la variable de entorno EF_DUMPCORE está definida
	   y es una cade no vacía; de lo contrario llame a exit(3) o _exit(2),
	   dependiendo el valor de 'useExit3' */

	s = getenv("EF_DUMPCORE");

	if (s != NULL && *s != '\0')
		abort();

	else if (useExit3)
		exit(EXIT_FAILURE);
	else
		_exit(EXIT_FAILURE);
}

static void
outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap)
{
#define BUF_SIZE 500

	char  buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

	vsnprintf(userMsg, BUF_SIZE, format, ap);

	if (useErr)
		snprintf(errText, BUF_SIZE, " [%s %s]", (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOW?", strerror(err));
	else
		snprintf(errText, BUF_SIZE, ":");

	snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

	if (flushStdout)
		fflush(stdout);         /* Elimina cualquier salida estandar pendiente */

	fputs(buf, stderr);             /* Imprimir en la salida del error */
	fflush(stderr);                 /* En caso de que stderr no tenga búfer de línea */
}


void
errMsg(const char *format, ...)
{
	va_list arg_List;
	int savedErrno;

	savedErrno = errno;            /* En caso de que lo combianos aquí */

	va_start(arg_List, format);
	outputError(TRUE, errno, TRUE, format, arg_List);
	va_end(arg_List);

	errno = savedErrno;
}

void
errExit(const char *format, ...)
{
	va_list arg_List;

	va_start(arg_List, format);
	outputError(TRUE, errno, TRUE, format, arg_List);
	va_end(arg_List);

	terminate(TRUE);
}

void
err_exit(const char *format, ...)
{
	va_list arg_List;

	va_start(arg_List, format);
	outputError(TRUE, errno, FALSE, format, arg_List);
	va_end(arg_List);


	terminate(FALSE);
}

void
errExitEN(int errnum, const char *format, ...)
{
	va_list arg_List;

	va_start(arg_List, format);
	outputError(TRUE, errnum, TRUE, format, arg_List);
	va_end(arg_List);

	terminate(TRUE);
}

void
fatal(const char *format, ...)
{
	va_list arg_List;

	va_start(arg_List, format);
	outputError(FALSE, 0, TRUE, format, arg_List);
	va_end(arg_List);

	terminate(TRUE);
}

void
usageErr(const char *format, ...)
{
	va_list arg_List;

	fflush(stdout);    /* Vacíe cualquier salida estandar pendiente */

	fprintf(stderr, "usage: ");
	va_start(arg_List, format);
	vfprintf(stderr, format, arg_List);
	va_end(arg_List);

	fflush(stderr);    /* Enc caso de que stderr no tenga búfer de línea*/
	exit(EXIT_FAILURE);
}

void
cmdLineErr(const char *format, ...)
{
	va_list arg_List;

	fflush(stdout);     /* Vacíe cualquier salida estándar pendiente */

	fprintf(stderr, "Command-line usage error: ");

	va_start(arg_List, format);
	vfprintf(stderr, format, arg_List);
	va_end(arg_List);

	fflush(stderr);   /* En caso de que stderr no tenga bufer de línea */
	exit(EXIT_FAILURE);
}
