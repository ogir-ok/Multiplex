/*
 * Time_server.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: user
*/
#include "mult_serv.h"

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


int main(int argc, const char **argv)
{
	const char* config;
	int nready;

	if (1 < argc)
	{
		config = argv[1];
	}
	else
	{
		config = DEFAULT_CONF_FILE;
	}

	FILE* config_file = fopen(config, "r");
	if (NULL == config_file)
	{
		printf ("can't open configuration file %s: %s\n", config, strerror(errno));
	}

	int sock_number = 0;
	int sock_listener[MAX_SERVER_SOCKETS];
	int log_file_max_size = DEFAULT_LOG_FILE_MAX_SIZE;
	FILE* log_file = NULL;

	while (!feof(config_file))
	{
		char param[256];
		fscanf(config_file, "%s ", param);

		if (strcmp(param, "server_port"))
		{
			++sock_number;
			if (MAX_SERVER_SOCKETS < sock_number)
			{
				printf("server can not listen more than %d sockets.", MAX_SERVER_SOCKETS);
				--sock_number;
			}
			else
			{
				sock_listener[sock_number-1] = socket(AF_INET,SOCK_STREAM,0);

				if (sock_listener < 0)
				{
					printf ("Error: Can't create socket\n");
					--sock_number;
					break;
				}
				int port;
				fscanf (config_file, "%d\n", &port);

				sockaddr_in servaddr;
				servaddr.sin_family = AF_INET;
				servaddr.sin_port = htons(port);
				servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

				if (0 > bind (sock_listener[sock_number-1], (const sockaddr*)(&servaddr), sizeof(servaddr)))
				{
					printf ("port %d is already used by some program or yoh have not permission to use it\n", port);
					--sock_number;
					break;
				}

				if(0> listen (sock_listener[sock_number-1], MAX_CONNECTIONS))
				{
					printf("Can't listen socket on port port %d\n", port);
					--sock_number;
					break;
				}

				printf ("Socket on port %d was opened successfully\n", port);
			}
		}


		if (strcmp(param, "log_file"))
		{
			if (NULL != log_file)
			{
				fclose(log_file);
			}

			char log_path[MAX_PATH_LENGTH];
			fscanf(config_file, "%s\n", log_path);

			log_file = fopen(log_path, "w+");

			if (NULL == log_file)
			{
					printf("Can not open log file.");
			}
		}

		if (strcmp(param, "log_file_max_size"))
		{
			fscanf(config_file, "%d\n", &log_file_max_size);
		}



		while(true)
		{


		}
	}

	/*sock_listener = socket(AF_INET,SOCK_STREAM,0);

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
	}*/
	return 0;
}



