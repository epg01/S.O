#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/ename.c.inc"

void OutputError(Boolean useErr, int err, Boolean fushStdout, const char *format, va_list ap)
{
#define MAX_SIZE 500

	char buf[MAX_SIZE], userMsg[MAX_SIZE], errTxt[MAX_SIZE];

	vsnprintf(userMsg, MAX_SIZE, format, ap);

	if (useErr)
		snprintf(errTxt, MAX_SIZE, " [%s %s]", 
			 (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKONW?", strerror(errno));
	else
		snprintf(errTxt, MAX_SIZE, ":");

	snprintf(buf, MAX_SIZE, "ERROR%s %s\n", errTxt, userMsg);

	if (fushStdout)
		fflush(stdout);

	fputs(buf, stderr);
	fflush(stderr);
}

void MuestreError(const char *format, ...)
{
	va_list arg_List;

	va_start(arg_List, format);
	OutputError(TRUE, errno, TRUE, format, arg_List);
	va_end(arg_List);
}

int
main(int argc, char *argv[])
{
	int Fd, AccessMode, Flags;

	if (argc >= 2)
	{

		Fd = open(argv[1], O_WRONLY);

		if (Fd == -1)
		{
			MuestreError("open");
			if (errno == ENOENT)
			{
				mode_t FilePerms;

				printf("Creamos la carpeta\n");
				FilePerms = O_WRONLY | O_CREAT | O_APPEND;
				Fd = open(argv[1], FilePerms);

				if (Fd == -1)
					errExit("segundo Open");

				Flags = fcntl(Fd, F_GETFL); /* Third argument is not required */
				if (Flags == -1)
					errExit("fcntl");

				if (Flags & O_APPEND)
				{
					printf("Existe una bandera de estado de archivo abierto\n");
					printf("Es O_APPEND\n");
				}
			}
		}
	}
}

