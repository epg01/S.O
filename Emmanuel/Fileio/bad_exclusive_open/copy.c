#include <sys/stat.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"


int
main(int argc, char *argv[])
{
#define  BUF_SIZE 10

	int Fd_input, Fd_output, OpenFlags;
	mode_t Mode;
	ssize_t NumRead;
	char buf[10];

	if (argc < 3 || (strcmp(argv[1], "--help") == 0))
		usageErr("usage: %s old_file new_file\n", argv[0]);

	OpenFlags = O_CREAT | O_WRONLY;
	Mode = S_IRUSR | S_IWUSR | S_IRGRP |
		S_IWGRP | S_IROTH | S_IWOTH;

	Fd_input = open(argv[1], O_RDONLY);

	if (Fd_input == -1)
		errExit("open Fd_input");

	Fd_output = open(argv[2], OpenFlags, Mode);

	if (Fd_output == -1)
		errExit("Open Fd_output");

	while (NumRead = read(Fd_input, buf, BUF_SIZE))
		if (write(Fd_output, buf, NumRead) != NumRead)
			fatal("write read/write parcial");

	if (NumRead == 0)
		printf("Escritura del archivo %s al archivo %s completado\n",
		       argv[1], argv[2]);

	if (close(Fd_input) == -1)
		errExit("close, Fd_input");

	if (close(Fd_output) == -1)
		errExit("close, Fd_output");

	exit(EXIT_SUCCESS);
}
