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

#include "date.h"
#include "backup.h"
#include "fileAudit.h"
#include "client.h"

void file_audit()
{
	char * dateBuffer[80];
    char * date = returnDate(dateBuffer);
    char * file = ".txt";

    char * path = "ausearch -f /var/www/html/ > /home/daire/Documents/Assignment1/accesslog/accesslog.txt";

    // int bufferSize = strlen(path) + strlen(file) + strlen(date) + 1;
    // char * buffer = (char *) malloc (bufferSize);

    // strcpy(buffer, path);
    // strcat(buffer, date);
    // strcat(buffer, file);


    if(system (path) < 0)
    {
        message_queue("Could not audit");
    	openlog("Assignment1", LOG_PID | LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not audit: %s", strerror(errno));
    	closelog();
    }

}
