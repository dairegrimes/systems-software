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
#include "backup.h"
#include "client.h"

void backup()
{

	char * dateBuffer[80];
    char * date = returnDate(dateBuffer);



    char * path = "cp -R /var/www/html/intranet /home/daire/Documents/Assignment1/backup/";


    int bufferSize = strlen(path) + strlen(date) + 1;
    char * buffer = (char *) malloc (bufferSize);

    strcpy(buffer, path);
    strcat(buffer, date);

    if (system(buffer) < 0)
    {
    	message_queue("Could not backup");
    	openlog("Assignment log", LOG_PID|LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not backup %s", strerror(errno));
    	closelog();
  	}

    
    message_queue("Backup Completed");
	free(buffer);


}