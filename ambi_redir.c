#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() 
{
	char *fname = NULL;  
	int fd = open(fname, O_RDONLY);
	if (fd == -1) 
	{
		perror("open");
		printf("errno: %d (%s)\n", errno, strerror(errno));
	}
	return 0;
}

