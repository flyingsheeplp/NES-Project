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

#define MASKBIT(x) (1<<x)
#define BUFSIZE 16384

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
	unsigned char readbuf[BUFSIZE]={1};
	if((nesfd = open(nesfile,O_RDWR)) == -1)
	{
		perror("OPEN");
		retval = 1;
		goto ret;
	}

	if((readbyte = read(nesfd,readbuf,16)) == -1)
	{
		perror("READ");
		retval = 2;
		goto ret;
	}
	
	if(readbuf[0] != 'N' || readbuf[1] != 'E' || readbuf[2] != 'S' )
	{
		fprintf(stderr,"Wrong file type! :(\n");
		retval = 3;
		goto ret;
	}
		
	printf("Number of 16KB ROM Banks:%d\n",readbuf[4]);
	printf("Number of 8KB Video ROM Banks:%d\n",readbuf[5]);
	printf("BYTE 6:%x\n",readbuf[6]);
	printf("Mirroring type:");
	if(readbuf[6] & MASKBIT(0))
		printf("Vertical\n");
	else
		printf("Horizontal\n");
	if(readbuf[6] & MASKBIT(1))
		printf("Battery backed RAM at 0x6000-0x7000\n");
	if(readbuf[6] & MASKBIT(2))
		printf("512 byte trainer at 0x7000-0x71FF\n");
	if(readbuf[6] & MASKBIT(3))
		printf("Four screen VRAM layout\n");

	lseek(nesfd,16,SEEK_SET);
	if((readbyte = read(nesfd,readbuf,16384)) == -1)
	{
		perror("READ");
		retval = 2;
		goto ret;
	}
	int i,j=0;
	for(i=0;i<200;i++)
	{
		if(j==25)
		{
			printf("\n");
			j=0;
		}
		printf("%x ",readbuf[i]);
		j++;
	}
	printf("\n");
	
	retval = 0;
ret:
	if(nesfd != -1)
		close(nesfd);
	return retval;
}
