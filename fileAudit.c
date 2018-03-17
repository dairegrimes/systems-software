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

void file_audit()
{
	char * dateBuffer[80];
    char * date = returnDate(dateBuffer);
    char * file = ".txt";

    char * path = "ausearch -f /var/www/html/ > /home/daire/Documents/Assignment1/audit_logs/";

    int bufferSize = strlen(path) + strlen(file) + strlen(date) + 1;
    char * buffer = (char *) malloc (bufferSize);


    strcpy(buffer, path);
    
    strcat(buffer, date);
    
    strcat(buffer, file);

    

    if(system (buffer) < 0)
    {
    	openlog("Audit log", LOG_PID | LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not audit: %s", strerror(errno));
    	closelog();
    }
    free(buffer);
}
