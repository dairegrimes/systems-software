#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>

#include "transfer.h"
#include <setjmp.h>

 
void update_website()
{
	char * source = "/var/www/html/intranet/";
	char * dest = "/var/www/html/live";


	char * args[] = { "cp", "-R", source, dest ,NULL};
	execv ("/bin/cp", args);
}

