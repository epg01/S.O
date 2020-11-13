#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"


int
main(int argc, char *argv[])
{
	size_t len;
	off_t offset;
	int fd, ap, j;
	char *buf;
	ssize_t numRead, numWritten;
	mode_t FilePerms;

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n",
			 argv[0]);

	FilePerms = S_IRUSR | S_IWUSR | S_IRGRP |
          	    S_IWGRP | S_IROTH | S_IWOTH;

	fd = open(argv[1], O_RDWR | O_CREAT, FilePerms);  /* rw-rw-rw */

/* Mostrará un error de salida: ERROR [N°ERROR stderror(errno)] open */
	if (fd == -1)
		errExit("open");


	for (ap = 2; ap < argc; ap++) {
		switch (argv[ap][0]) {
		case 'r': /* Mostrar bytes en el desplazamiento actual, como texto */
		case 'R': /* Mostrar bytes en el desplazamiento actual, en hexadecimal */
			len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
			buf = malloc(len);
			if (buf == NULL)
				errExit("malloc");

			numRead = read(fd, buf, len);
			if (numRead == -1)
				errExit("read");
			if (numRead == 0) {
				printf("%s: end-of-file\n", argv[ap]);
			} else {
				printf("%s: ", argv[ap]);
				for (j = 0; j < numRead; j++) {
					if (argv[ap][0] == 'r')
						printf("%c", isprint((unsigned char) buf[j]) ?
						       buf[j] : '?');
					else
						printf("%02x ", (unsigned int) buf[j]);
				}
				printf("\n");
			}

			free(buf);
			break;
		case 'w': /* Write string at current offset */
			numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
			if (numWritten == -1)
				errExit("write");
			printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
			break;
		case 's': /* Change file offset */
			offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
			if (lseek(fd, offset, SEEK_SET) == -1)
				errExit("lseek");
			printf("%s: seek succeeded\n", argv[ap]);
			break;
		default:
			cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
		}
	}
	exit(EXIT_SUCCESS);
}
