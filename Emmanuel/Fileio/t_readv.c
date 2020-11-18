#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"


int
main(int argc, char *argv[])
{
	int Fd;
	struct iovec Iov[3];
	struct stat MyStruct;                /* Primer Búfer */
	int x;                               /* Segundo Búfer */
	ssize_t NumberRead, TotalRequired;
	mode_t FilePerms;
#define STR_SIZE 3000
	char str[STR_SIZE];                  /* Tercer Búfer */

	if (argc != 3 || (strcmp(argv[1], "--help") == 0))
		usageErr("%s file\n", argv[0]);

	Fd = open(argv[1], O_RDONLY);

	if (Fd == -1)
		errExit("open");

	TotalRequired = 0;

	Iov[0].iov_base = &MyStruct;
	Iov[0].iov_len  = sizeof(struct stat);
	TotalRequired  += Iov[0].iov_len;

	Iov[1].iov_base = &x;
	Iov[1].iov_len = sizeof(x);
	TotalRequired += Iov[1].iov_len;

	Iov[2].iov_base = str;
	Iov[2].iov_len  = STR_SIZE;
	TotalRequired  += Iov[2].iov_len;

	NumberRead = readv(Fd, Iov, 3);

	if (NumberRead == -1)
		errExit("readv");

	if (NumberRead < TotalRequired)
		printf("Se leyó menos bytes de los solicitados\n");

	printf("Total the bytes required: %ld; bytes read: %ld\n",
	       (long) TotalRequired, (long) NumberRead);

	if (close(Fd) == -1)
		errExit("close");

	FilePerms = O_WRONLY | O_CREAT | O_APPEND | O_TRUNC;
	Fd = open(argv[2], FilePerms, S_IRUSR | S_IWUSR);

	if (Fd == -1)
		errExit("open");

	if (writev(Fd, Iov, 3) != TotalRequired)
		fatal("Write parcil/memory\n");

	if (close(Fd) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);
}
