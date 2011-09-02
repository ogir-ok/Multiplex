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
#include <errno.h>

#include <poll.h>

#include "sock.h"

const int MAX_CONNECTIONS = 128; // number of connections to the server in the same time

const int MAX_PATH_LENGTH = 256;

const char* DEFAULT_CONF_FILE = "/home/user/.mult_serv.conf";
const int DEFAULT_LOG_FILE_MAX_SIZE = 1024;
const int MAX_SERVER_SOCKETS = 128; //max number of sockets, that server will listen in the same time
#endif /* TIME_SERVER_H_ */
