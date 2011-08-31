/*
 * Time_server.h
 *
 *  Created on: Aug 25, 2011
 *      Author: user
 */

#ifndef TIME_SERVER_H_
#define TIME_SERVER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include <pthread.h>

#include <syslog.h>

#include <sys/stat.h>

#include "sock.h"
#include "log_file.h"
#include "daemonize.h"

static const int MAX_CONNECTIONS = 128; // number of connections to the server in the same time
static const int MAX_LOG_LINE = 256;
//static const char* LOG_PATH = "/var/log/time_server.log";
#endif /* TIME_SERVER_H_ */
