#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tantalus.h"

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

FILE *OutputFile;
FILE **InputFiles;
int InputFilesCount = 0;

int main(int argc, char **argv) {
    bool setOut = false, checkFormat = false;
    
    // check arguments
    for (register int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (setOut) {
                    printf("\t\033[0;31mError, can't have more then one output.\n\033[0;0m");
                    fclose(OutputFile);
                    return 1;
                }

                if (i + 1 >= argc || argv[i + 1][0] == '-') {
                    printf("\t\033[0;31mError, an output must be a file.\n\033[0;0m");
                    return 1;
                }

                OutputFile = fopen(argv[++i], "w");
                setOut = true;
            } else if (strcmp(argv[i], "-f") == 0) {
                if (checkFormat) {
                    printf("\t\033[0;31mError, format cannot be changed twice.\n\033[0;0m");
                    if (OutputFile != NULL)
                        fclose(OutputFile);

                    return 1;
                }

                // check format later
                i++;
                checkFormat = true;
            } else if (strcmp(argv[i], "-?") == 0) {
                return 0;
            }

            for (register int j = i + 1; j < argc; j++)
                argv[j - 2] = argv[j];

            argc -= 2;
            i -= 2;
        } else {
            // exit if the file doesn't exist
            if (access(argv[i], F_OK) != 0) {
                printf("\t\033[0;31mError, file '%s' doesn't exists.\n\033[0;0m", argv[i]);
            }
        }
    }

    // allocate space
    InputFilesCount = argc - 1;
    InputFiles = (FILE **)malloc(sizeof(FILE *) * InputFilesCount);

    // load files
    for (register int i = 0; i < InputFilesCount; i++)
        InputFiles[i] = fopen(argv[i + 1], "rb");
    
    exitProgram(0);
    return 0;
}

// function to clear the memory and close the files
void exitProgram(int exitCode) {
    fclose(OutputFile);

    for (register int i = 0; i < InputFilesCount; i++)
        fclose(InputFiles[i]);

    free(InputFiles);
    exit(exitCode);
}
