#include <stdio.h>
#include <time.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>

#include "client.h"

void message_queue(char  message[])
{
	mqd_t mq;

	mq = mq_open("/dt228_queue", O_WRONLY);

	mq_send(mq, message, 1024, 0);

	mq_close(mq);
}

