/********************************************************************************
 *                     readnes.c                                                *
 *         binary util to read the nes file structure                           *
 *          usage: readnes <filename>                                           *
 *          author:Li Peng                                                      *
 *                                                                              *
 ********************************************************************************/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"usage:%s <nes-file>\n",argv[0]);
		return 1;
	}

	readnes(argv[1]);
	return 0;
}

int readnes(char* nesfile)
{
	int retval = 0;
	int nesfd;
	int readbyte = 0;
	char readbuf[100];
	if((nesfd = open(nesfile,O_RDWR)) == -1)
	{
		perror("OPEN");
		retval = 1;
		goto ret;
	}

	readbyte = read(nesfd,readbuf,16);
	if(readbuf[0] != 'N' || readbuf[1] != 'E' || readbuf[2] != 'S' )
	{
		fprintf(stderr,"Wrong file type! :(\n");
		retval = 2;
		goto ret;
	}
		
	printf("Number of 16KB ROM Banks:%d\n",readbuf[4]);
	printf("Number of 8KB ROM Banks:%d\n",readbuf[5]);
	printf("Mirroring type:");
	if(readbuf[6] & 1)
		printf("Vertical\n");
	else
		printf("Horizontal\n");

	
	retval = 0;
ret:
	if(nesfd != -1)
		close(nesfd);
//	if(neshdr)
//		munmap(neshdr,nesstat.st_size);
	return retval;
}
