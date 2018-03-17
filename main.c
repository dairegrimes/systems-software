#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#include "transfer.h"
#include "backup.h"
#include "date.h"
#include "file_locking.h"
#include "fileAudit.h"

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

    // Implementation for Singleton Pattern if desired (Only one instance running)

    // Create a child process      
    int pid = fork();
 
    if (pid > 0) {
        // if PID > 0 :: this is the parent
        // this process performs printf and finishes

        sleep(10);  // uncomment to wait 10 seconds before process ends
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
       // Step 1: Create the orphan process
       printf("\nProcess running ...");
       
       // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
       // This command runs the process in a new session
       if (setsid() < 0) { exit(EXIT_FAILURE); }

       // We could fork here again , just to guarantee that the process is not a session leader
       int pid = fork();
       if (pid > 0) {
          exit(EXIT_SUCCESS);
       } else {
       
          // Step 3: call umask() to set the file mode creation mask to 0
          // This will allow the daemon to read and write files 
          // with the permissions/access required 
          umask(0);

          // Step 4: Change the current working dir to root.
          // This will eliminate any issues of running on a mounted drive, 
          // that potentially could be removed etc..
          if (chdir("/") < 0 ) { exit(EXIT_FAILURE); }

          // Step 5: Close all open file descriptors
          /* Close all open file descriptors */
          int x;
          for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
          {
             close (x);
          } 


          int fd;
          char * fifoFile = "tmp/fifoFile";
          char buf[MAX_BUF];
            
         
          while(1) 
          {
                sleep(1);
                
                fd = open (fifoFile, O_RDONLY);
                read (fd, buf, MAX_BUF);

                if(strcmp(buf, "1") == 0)
                {
                    lock_files("1111");
                    backup();
                    lock_files("0777");
                }

                else if(strcmp(buf, "2") == 0)
                {
                    lock_files("1111");
                    update_website();
                    lock_files("0777");
                }
                close(fd);
                

                time(&now);
                seconds = difftime(now,mktime(&newyear));

                if (seconds == 0) 
                {
                    lock_files("1111");
                    file_audit();
                    backup();
                    update_website();
                    lock_files("0777");
                }
          }
       }
    }
 
    return 0;
}