/*
 * Time_server.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: user
*/
#include "time_server.h"

void* sock_work_func(void * arg)
{
	int* sock_worker = (int*)arg;
	time_t cur_time = time(NULL);
	char buff[MAX_LINE];
	snprintf(buff, sizeof(buff), "%24s\er\en",ctime(&cur_time));
	write(*sock_worker, buff, sizeof(buff));
	close(*sock_worker);
	delete sock_worker;
	return(void*)0;
}


int main()
{
	daemonizer* d = new daemonizer();
	// initializing like daemon

	d->setname("time_server");
	d->ALLOW_MULTIPLY_INSTANCES = false;
	d->daemonize();

	delete d;

	int sock_listener;
	sock_listener = socket(AF_INET,SOCK_STREAM,0);
	if (sock_listener < 0)
	{
		syslog(LOG_ERR, (char*)"Error: Can't create socket for listening\n");
		return 1;
	}
	sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (0 > bind (sock_listener, (const sockaddr*)(&servaddr), sizeof(servaddr)))
	{
		servaddr.sin_port = htons(13123);
			if (0 > bind (sock_listener, (const sockaddr*)(&servaddr), sizeof(servaddr)))
			{
				servaddr.sin_port = htons(0);
				if (0 > bind (sock_listener, (const sockaddr*)(&servaddr), sizeof(servaddr)))
					{
						syslog(LOG_ERR, (char*)"Error: Can't bind socket. there is no free ports \n");
						return 1;
					}
			}
			char line[1024];
			int len_inet = sizeof (servaddr);
			getsockname(sock_listener,(sockaddr*) &servaddr,(socklen_t*)&len_inet);
			syslog(LOG_ERR, "Warning: Can't bind socket on port 13. using port %d \n", ntohs(servaddr.sin_port));
	}

	if(0> listen (sock_listener, MAX_CONNECTIONS))
	{
		syslog(LOG_ERR, (char*)"Error: Can't listen socket\n");
		return 1;
	}

	syslog(LOG_ERR, (char*)"Server started\n");
	while (true)
	{
		int* sock_worker = new int();
		*sock_worker= accept(sock_listener,(sockaddr*)NULL, NULL);
		syslog(LOG_USER, (char*)"Client connected\n");
		pthread_t* sock_worker_thread = new pthread_t();
		pthread_create(sock_worker_thread, NULL, sock_work_func, (void*)sock_worker);
		pthread_detach(*sock_worker_thread);
		delete sock_worker_thread;
	}
	return 0;
}



