#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	mode_t FilePerms;
	int Fd;

	if (argc < 2 || (strcmp(argv[1], "--help") == 0))
		usageErr("%s Filename\n", argv[0]);

	if (argc > 3)
		FilePerms = O_WRONLY | O_CREAT | O_APPEND;
	else
		FilePerms = O_WRONLY | O_APPEND;

	Fd = open(argv[1], FilePerms, S_IRUSR | S_IWUSR);

	if (Fd == -1)
		errExit("open");

	if ((lseek(Fd, 0, SEEK_END)) == -1)
		errExit("Issek");

	if (argc > 3)
	{
		printf("[PID %ld] Que sobre escribirá el archivo \"%s\"\n",
		       (long) getpid(), argv[1]);
		sleep(5);          /* Se colocó en espera para que el otro proceso
				      Utlice los recursos de la CPU */
		printf("[PID %ld]Termino de Dormir, ahora tendra los recursos de la CPU\n",
		       (long) getpid());
		if (write(Fd, argv[2], strlen(argv[2])) != strlen(argv[2]))
			fatal("Fallo parcial de escriturá\n");

		return (0);
	}
	printf("[PID %ld] Escribiré en el archivo \"%s\"\n",
	       (long) getpid(), argv[1]);

	if (write(Fd, argv[2], strlen(argv[2])) != strlen(argv[2]))
		fatal("Fallo parcial de escriturá\n");
	return (0);
}
