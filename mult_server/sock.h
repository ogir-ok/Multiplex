/*
 * socket.h
 *
 *  Created on: Aug 25, 2011
 *      Author: user
 */

#ifndef SOCK_H_
#define SOCK_H_
//Include to use sockets
#include <sys/types.h>
#include <sys/socket.h>

//Include to use sockaddr_in
#include <netinet/in.h>

//to use inet_*
#include <arpa/inet.h>

static const int MAX_LINE = 128; 		// max length of line, that could be sent

#endif /* SOCK_H_ */
