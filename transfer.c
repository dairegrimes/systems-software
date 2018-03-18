#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#include "transfer.h"
#include <setjmp.h>
#include "client.h"

 
void update_website()
{

	char * path = "rsync -r /var/www/html/intranet/ /var/www/html/live";


  	if (system(path) < 0)
  	{
	    openlog("Assignment1", LOG_PID|LOG_CONS, LOG_USER);
	    syslog(LOG_INFO, "Failed to update %s", strerror(errno));
	    closelog();
	}

	message_queue("Transfer Completed");
}

