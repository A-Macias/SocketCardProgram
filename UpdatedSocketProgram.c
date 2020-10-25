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
	char buffer[1024];
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
	
	while(1){

		new_socket=accept(sf,(struct sockaddr*)&srvaddr, (socklen_t*)&addrlen);
		if(new_socket<0){
			printf("accept error");
			exit(1);
		}	
		readvalue=read(new_socket,buffer,sizeof(buffer));

		int comparingString=strcmp(buffer,deal);

		if(comparingString==0){
			sprintf(buffer,"Server Deal has begun\n");
			send(new_socket,buffer,strlen(buffer),0);

			for(int c=0;c<52;c++){
				deckOfCards[c]=c+1;
				}

			randperm(deckOfCards,52);

			for(int d=0;d<52;d++){
				sprintf(buffer, "Card %d %d\r\n",d+1, deckOfCards[d]);
				send(new_socket,buffer, strlen(buffer), 0);
				}
		}

		else{
			sprintf(buffer,"Server is not responding\n");
			send(new_socket,buffer,strlen(buffer),0);
			}
	
		}
	
	return 0;
}
