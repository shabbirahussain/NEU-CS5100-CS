#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "structs.h"

int printFile(const char *pathname);

int main(int argc, char const *argv[])
{
	// Parse command line arguments.
	const char *pathname = (argc == 1)? "output.ser" : argv[1];
	
	return printFile(pathname);
}


int printFile(const char *pathname)
{

	FILE *fpOut = fopen(pathname,"r");
	if (fpOut == NULL)
	    exit(EXIT_FAILURE);


	int len = sizeof(struct MemoryRegion);
	struct MemoryRegion *mr=malloc(len);

	int pos = 0;
	ssize_t read;
	long roSize=0, rwSize=0;
	do {
		if ((read = fread(mr, len, 1, fpOut)) != 1) 
			break;

		printStruct(mr);

		long size = (mr -> endAddr - mr ->startAddr);
	    if (mr -> isReadable && !mr -> isWriteable) roSize += size;
	    if (mr ->isReadable && mr -> isWriteable)   rwSize +=size;

		pos += len;
		fseek(fpOut, pos , SEEK_SET);
	} while (!feof(fpOut));
	printf("Process 2:\n \tReadOnly Tot=%ld\n\tReadWrite Tot=%ld\n", roSize, rwSize);

	free(mr);
	fclose(fpOut);
	return 0;
}

