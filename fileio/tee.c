#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE  1024
#endif

int main(int argc, char* argv[])
{
  int fd = -1;
  int openFlags;
  Boolean appendFlag = FALSE;
  int opt;
  ssize_t numRead;
  char buf[BUF_SIZE];

  while ((opt = getopt(argc, argv, "ah")) != -1)
  {
    switch (opt)
    {
      case 'a':
        appendFlag = TRUE;
        break;

      case 'h':
      case '?':
        usageErr("%s [-a] [FILE]", argv[0]);
        break;

      default:
        fatal("Unexpected case in switch: %d", opt);
    }
  }

  if (optind < argc) {
    openFlags = O_CREAT | O_WRONLY | (appendFlag ? O_APPEND : O_TRUNC);

    fd = open(argv[optind], openFlags,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
      errExit("opening file %s", argv[optind]);
  }

  while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
  {
    if (write(STDOUT_FILENO, buf, numRead) != numRead)
      errExit("write to standart output");
    if (fd != -1 && write(fd, buf, numRead) != numRead)
      errExit("write to file %s", argv[optind]);
  }

  if (numRead == -1)
    errExit("read");

  if (fd == STDIN_FILENO) {
    if (close(fd) == -1)
      errExit("closing file %s", argv[optind]);
  }

  exit(EXIT_SUCCESS);
}
