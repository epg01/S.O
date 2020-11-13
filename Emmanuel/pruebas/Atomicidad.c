#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	int Fd;       /* Descriptor de archivo: Número pequeño */
	mode_t FilePerms;     /* Entero: Permiso y tipo de archivos */

	if (argc > 1)
	{
        /* Mostrará un mensaje del tipo:
                    usage: argv[0] NameFile.txt */
		if (argc >= 2 && (strcmp(argv[1], "--help") == 0))
			usageErr("%s NameFile.txt\n", argv[0]);

        /* Abrimos el archivo si existe */
		Fd = open(argv[1], O_WRONLY);

	/* Mostrará un mensaje del tipo:
                    ERROR [NAME_ERRNO stderror(errno)] open */

		if (Fd == -1 && errno != ENOENT)
			errExit("open");
		else if (Fd != -1)
		{
			printf("[PID %ld] File \"%s\" already exists\n",
			       (long) getpid(), argv[1]);

		/* Mostrará un mensaje del tipo:
		       ERROR [NAME_ERRNO stderror(errno)] close */
			if (close(Fd) == -1)
				errExit("close");
		}
		else
		{
			/* Mostrará un mensaje del tipo:
			         ERROR [NAME_ERRNO stderror(errno)] open */
			if (errno != ENOENT)
				errExit("open");
			else
			{
//				printf("[PID %ld] File \"%s\" doesn't exist yet\n", (long) getpid(), argv[1]);
//				if (argc > 2) { /* Esperando entre la verificación y la creción */
//					sleep(5); /* Suspendiendo la ejecución por 5 seg */
//					printf("[PID %ld] Sueño terminado\n", (long) getpid());
//				}

				/* WINDOW  FOR FAILURE*/
				FilePerms = O_RDWR | O_CREAT | O_APPEND;

				Fd = open(argv[1], FilePerms,  S_IRUSR | S_IWUSR);

				/* Mostrará un mensaje del tipo:
				   ERROR [NAME_ERRNO stderror(errno)] open */
				if (Fd == -1)
					errExit("open");

				/* Puede no ser cierto : condición de carrera */
				printf("Condición de carrera\n");
				printf("[PID %ld] Created file \"%s\" exclusively\n",
				       (long) getpid(), argv[1]);

				exit(EXIT_SUCCESS);
			}
		}
	}
	else
	{
		printf("Ingrese un parámetro\n");
		return (-1);
	}
}
