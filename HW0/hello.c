#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "structs.h"

struct MemoryRegion * parseLine(char *line);
int processFile(const char *pathname);
void split(char * line, const char* delimiter, char * res[]);


int main(int argc, char const *argv[])
{
	// Parse command line arguments.
	const char *pid = (argc == 1)? "self" : argv[1];

	// Build file name of the proc maps.
	char *pathname = (char*)malloc(100 * sizeof(char));
	sprintf(pathname, "/proc/%s/maps", pid);
	
	return processFile(pathname);
}


int processFile(const char *pathname)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(pathname, "r");
	if (fp == NULL)
	    exit(EXIT_FAILURE);

	FILE *fpOut = fopen("output.ser","wb");
	while ((read = getline(&line, &len, fp)) != -1) {
	    printf("\n\n%s", line);
	    struct MemoryRegion *mr  = parseLine(line);

		if (fwrite(mr, sizeof(struct MemoryRegion),1, fpOut) == 1) // success
		{	
			printf("Struct written");
		}
	}

	free(line);
	fclose(fp);
	return 0;
}

struct MemoryRegion * parseLine(char * line)
{
	struct MemoryRegion *p;
   	p = (struct MemoryRegion *) malloc(sizeof(struct MemoryRegion));

	char * res[10];
	split(line, " ", res);	// Split on space.

	char * res1[2];
	split(res[0], "-", res1); // Split on memory address.
	p -> startAddr = (void *) res1[0];
	p -> endAddr   = (void *) res1[1];

	p -> isReadable  = (res[1][0] == 'r')? 1 : 0;
	p -> isWriteable = (res[1][1] == 'w')? 1 : 0;
	p -> isExecutabl = (res[1][2] == 'x')? 1 : 0;

	return p;
}


void split(char * line, const char* delimiter, char * res[])
{
	int i = 0;
	res[i++] = strtok (line, delimiter);
	while (res[i-1] != NULL)
	{
		res[i++] = strtok (NULL, delimiter);
	}
}









// int processFile1(const char *pathname)
// {
// 	int fd = open(pathname, O_RDONLY);
// 	char buf[256];
// 	for(;;) {
// 		int i;
// 		int n = read(fd, buf, 256); 
// 		if ( n <= 0 ) exit(-n); 
// 		printf("%s\n", buf);
// 	}
// 	close(fd);
// 	return 0;
// }

