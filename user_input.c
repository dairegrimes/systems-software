#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>



#include "date.h"
#include "backup.h"
#include "transfer.h"

#define MAX_BUF 1024

int main()
{
	int fd;
	//char * fifoFile = "/home/daire/Documents/Assignment1/src/namedPipe1.txt";
	char * fifoFile = "/tmp/fifoFile";
	int option = 0;

	mkfifo (fifoFile, 0666);
	
	while(option != 3)
	{
		
		printf("\nPlease choose an option");
		printf("\n1 : Backup");
		printf("\n2 : Transfer");
		printf("\n3 : Exit\n");


		scanf("%d", &option);
		getchar();

		switch(option)
		{
			case 1:
			{
				
				fd = open (fifoFile, O_WRONLY);

				write(fd, "1", sizeof("1") );
				close(fd);
	
				printf("\nBackup Completed");
			}break;

			case 2:
			{

				fd = open (fifoFile, O_WRONLY);

				write(fd, "2", sizeof ("2"));
				close(fd);

				printf("\nTransfer Completed");
			}break;

			case 3:
			{
				exit(0);
			}break;

			default:
			{
				printf("\n Invalid input");
			}break;
		}
	}
	return 0;
}



