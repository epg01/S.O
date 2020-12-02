#include <sys/stat.h>             /* Para las constantes de bandera:
				     + Modo de acceso, + Creción de archivo y
				     + estado de archivo abierto. */
#include <fcntl.h>                /* llamada al sistema open() */
#include <string.h>
#include "../../lib/tlpi_hdr.h"


int
main(int argc, char *argv[])
{
	int Fd;                   /* Descriptor de archivo */
	int OpenFlags;            /* Banderas de la llamada al sistema open() */
	mode_t  Mode;             /* Permisos de archivo */
	size_t Size;
	int ap;

	if (argc < 3 || (strcmp(argv[1], "--help")) == 0)
		usageErr("%s file {C|W<str>} & %s file {W<str>} or vice versa\n",
			 argv[0], argv[0]);

	OpenFlags = O_WRONLY | O_CREAT;
	Mode = S_IRUSR | S_IWUSR | S_IRGRP |
		S_IRGRP;  /* RW-RW----*/

	Fd = open(argv[1], OpenFlags, Mode);

	if (Fd == -1)
		errExit("open");

	if (lseek(Fd, 0, SEEK_END) == -1)
		errExit("lseek");

	printf("[PID %ld] Aun no se ha escrito nada en el archivo: \"%s\"\n",
	       (long) getpid(), argv[1]);

	for (ap = 2; ap < argc; ap++){
		switch (argv[ap][0]){
		case 'C':
			sleep(5);
			printf("[PID %ld] Done sleep\n", (long) getpid());
		case 'W':
			Size = strlen(&argv[ap][1]);
			if (write(Fd, &argv[ap][1], Size) != Size)
				fatal("Partial/failre write");
		}
	}
	exit(EXIT_SUCCESS);
}
