#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE                /* Permitir que "cc -D" anule la definición */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
	int InputFd, OutputFd, OpenFlags;

	mode_t  FilePerms;
	ssize_t NumRead;
	char Buf[BUF_SIZE];

	/* Salida del error: usage: ./copy old-file new-file */
	if (argc != 3 || (strcmp(argv[1], "--help") == 0))
		usageErr("%s old-file new-file\n", argv[0]);

	/* Abrir entrada y salida de archivos */

	InputFd = open(argv[1], O_RDONLY);

	/* Salida del error: ERROR [N°ERROR stdrerror(errno)] opening file argv[1] */
	if (InputFd == -1)
		errExit("opening file %s", argv[1]);

	OpenFlags = O_CREAT | O_WRONLY | O_TRUNC;

	/* FilePerms = rw-rw-rw- */
	FilePerms =  S_IRUSR | S_IWUSR | S_IRGRP |
		     S_IROTH | S_IWOTH;

	OutputFd = open(argv[2], OpenFlags, FilePerms);

	if (OutputFd == -1)
	       errExit("opening file %s", argv[2]);

 /* Transferir datos hasta que encontremos el final de la entrada o un error */
	while((NumRead = read(InputFd, Buf, BUF_SIZE)) > 0)
		if ((NumRead = write(OutputFd, Buf, NumRead)) != NumRead)
			fatal("Couldn't write whole buffer");

	if (NumRead == -1)
		errExit("Read");

	if (close(InputFd) == -1)
		errExit("Close input");

	if (close(OutputFd) == -1)
		errExit("Cose output");

	exit(EXIT_SUCCESS);
}
