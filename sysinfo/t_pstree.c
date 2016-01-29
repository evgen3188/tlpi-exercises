#include <stdlib.h>
#include <dirent.h>

#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    DIR *dirp;
    struct dirent *direntp;

    if (argc == 1) {
        dirp = opendir(".");   
    } else {
        dirp = opendir(argv[1]);
    }

    if (dirp == NULL) {
        errExit("opendir %s", argv[1]);
    }

    while (1)
    {
        errno = 0;

        direntp = readdir(dirp);
        if (direntp == NULL) {
            if (errno != 0) {
                errExit("readdir");
            }

            break;
        }

        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
            printf("%s\n", direntp->d_name);
        }
    }

    if (closedir(dirp) == -1) {
        errExit("closedir");
    }

    exit(EXIT_SUCCESS);
}
