#include <sys/stat.h>  /* Aquí se encuentras las banderas de:
		          + Modo de acceso, + de creación de archivo,
		          + Estado de archivo abierto. */
#include <fcntl.h>     /* Aquí se encuentra la función open() --> Llamada al sys*/
#include "../../lib/tlpi_hdr.h"


int
main(int argc, char *argv[])
{
	int Fd;        /* Descriptor de archivo, número pequeño que representa
			  un archivo abierto. */
	int OpenFlags; /* Mascara de bits que reprenseta las banderas con las
			  que se abrirá el archivo, para la creación y para
		          el estado de archivo abierto. */
	mode_t Mode;   /* Los permisos con los que se abrira el archivo:
			  + Permisos de usuario, + Permisos de grupo,
			  + Permisos de otros */

/* Verificamos un posible error en la línea de comandos */

	if (argc == 1 || (argc < 3 && (strcmp(argv[1], "--help") == 0)))
		usageErr("%s file\n", argv[0], argv[0]);

	/* Abrimos el archivo con la llamada al sistema open(),
	   como este retorda un Descriptor de archivo que represente por así
	   decirlo un archivo abierto lo capturamos con Fd. */

	Fd = open(argv[1], O_WRONLY);

	if (Fd != -1)
	{
		printf("[PID %ld] File \"%s\" already exists\n",
		       (long) getpid(), argv[1]);

		if (close(Fd) == -1)
			errExit("close, already existis");
	} else {
		if (errno != ENOENT) {         /* Fallo por motivo inesperado */
			errExit("open");
		} else {
			/* Ventana para fallo */
			OpenFlags = O_RDWR | O_CREAT;
			Mode = S_IRUSR | S_IWUSR | S_IRGRP |
				S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */

			Fd = open(argv[1], OpenFlags, Mode);

			if (Fd == -1)
				errExit("open");

			printf("[PID %ld] Created file \"%s\" exclusively\n",
			       (long) getpid(), argv[1]);   /* Puede no ser verdad*/
		}
	}
	exit(EXIT_SUCCESS);
}
