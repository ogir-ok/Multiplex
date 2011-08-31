/*
 * datetime_client.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: user
 */


#include "mult_cli.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc < 2)
	{
		std::cout<<"using "<<DEFAULT_IP<<" as <IPaddress>"<<std::endl;
		argv[1] = DEFAULT_IP;
	}
	if (argc < 3)
	{
		std::cout<<"using "<<DEFAULT_PORT<<" as <port>"<<std::endl;
		argv[2] = DEFAULT_PORT;
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout<<"Error: can not create socket"<<std::endl;
		return 1;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons( atoi(argv[2]) );

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
			std::cout<<"inet_pton error for "<<argv[1]<<std::endl;
			return 1;
	}

	printf("Connecting..");

	if (connect(sockfd, (sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
				std::cout<<"Error: can not connect to server"<<std::endl;
				return 1;
	}

	char input[MAX_LINE];
	std::cout<<std::endl;
	do
	{
		std::cout<<">";

		if (NULL == fgets(input, sizeof(input), stdin))
		{
			break;
		}
		write (sockfd, input, sizeof(input));
	}
	while (0 != strcmp(input, QUIT_LINE));

	close(sockfd);

	return 0;
}
