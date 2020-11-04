#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#define PORT 5000 (needs to be user input)

extern int randperm(int *, int);

int main (int argc, char const *argv[])
{

	int sf, new_socket,readvalue, deckOfCards[52];
	char buffer[2000];
	unsigned int portNumber;
	struct sockaddr_in srvaddr;
	int addrlen=sizeof(srvaddr);
	const char *deal="Deal";
	
	if(argc<=1){
		printf("Not enough arguements");
		exit(1);
	}
	portNumber=atoi(argv[1]);//uses atoi function to convert from a string of digits to an integer.
	
	sf= socket (AF_INET, SOCK_STREAM,0);
	if (sf<0){
		printf("ERROR");//print error message to stderr.
		exit(1);
	}
	
	
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_addr.s_addr=INADDR_ANY;
	srvaddr.sin_port= htons( portNumber );
	
	if(bind(sf, (struct sockaddr *)&srvaddr, sizeof(srvaddr))<0){
		printf("bind failed");
		exit(1);
	}
	if(listen (sf,5)<0){
		printf("listen error");
		exit(1);
	}
	fprintf(stdout,"Connecting.\n");

	new_socket=accept(sf,(struct sockaddr*)&srvaddr, (socklen_t*)&addrlen);
	if(new_socket<0){
		printf("accept error");
		exit(1);
	}
	puts("Connected");
	
	while((readvalue=recv(new_socket, buffer, 2000, 0))>0){
		write(new_socket, buffer, strlen(buffer));
	}
	if(readvalue==0){
		puts("Disconnected");
		fflush(stdout);
	}
	else if(readvalue==-1){
		sprintf(buffer, "Error in reading on server side");
		printf("readvalue error");
	}
	
	return 0;
}
