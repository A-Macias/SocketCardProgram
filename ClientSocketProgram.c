#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
//#define PORT 8080

int main(int argc, char const *argv[])
{
	int socketc=0, readValue, inetpton, cconnect;
	struct sockaddr_in serv_addr;
	unsigned int portNumber;
	const char *deal="Deal";
	char serv_res[1024];
	
	if(argc<=1)
	{
		printf("Not enough arguements");
		exit(1);
	}

	socketc=socket(AF_INET, SOCK_STREAM, 0);
	if(socketc<0)
	{
		printf("\n creation error \n");
		exit(1);
	}

	portNumber=atoi(argv[1]);

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(portNumber);
	
	inetpton= inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr);
	if(inetpton<=0)
	{
		printf("Error in ip-address");
		exit(1);
	}

	cconnect=connect(socketc,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (cconnect < 0)
	{
		printf("\nConnection Error \n");
		exit(1);
	}
	
	recv(socketc, &serv_res, sizeof(serv_res),0);

	printf("server sent data %s\n", serv_res);
	
	close(socketc);

	return 0;
}
