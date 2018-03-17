#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#include "date.h"
#include "backup.h"

void backup()
{
	char * dateBuffer[80];
    char * date = returnDate(dateBuffer);

    char  source[250] = "/var/www/html/intranet";
    char  dest[250] = "/home/daire/Documents/Assignment1/backup/";

    strcat (dest, date);

    char * args[] = {"cp", "-R" , source, dest,  NULL };

    execv("/bin/cp", args);
}