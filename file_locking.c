#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>


#include "date.h"
#include "client.h"
#include "file_locking.h"

void lock_files(char type[])
{
	int boolean;

	if(strcmp(type, "1111") == 0)
	{
		boolean = 0;
	}

	else
	{
		boolean = 1;
	}

	char path[100] = "/var/www/html";
	struct stat st;
	stat (path, &st);

	int i = strtol(type, 0, 8);

	if(chmod(path, i) < 0)
	{
		if(boolean == 0)
		{
			message_queue("Files not Locked");
		}

		else
		{
			message_queue("Files not Unlocked!");
		}
		
		openlog("Audit log", LOG_PID | LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not lock files");
    	closelog();
	}


	if(boolean == 0)
	{
		message_queue("Files Locked");
	}

	else
	{
		message_queue("Files Unlocked!");
	}
}
