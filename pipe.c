#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>


#include "date.h"
#include "backup.h"
#include "transfer.h"

#define MAX_BUF 1024

int main()
{
	time_t now;
    struct tm newyear;
    double seconds;
    time(&now);  /* get current time; same as: now = time(NULL)  */
    newyear = *localtime(&now);
    newyear.tm_hour = 21; 
    newyear.tm_min = 23; 
    newyear.tm_sec = 0;
    /*newyear.tm_mon = 0;  
    newyear.tm_mday = 1;*/



    time(&now);
    seconds = difftime(now,mktime(&newyear));
    printf("\n%.f\n\n", seconds);
    if (seconds == 0) 
    {
        printf("\n\nhello world\n");
	}
	return 0;
}



