#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
//#define PORT 8080

enum suits { SPADES, HEARTS, DIAMONDS, CLUBS };
enum faces { ACE, TWO,THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,\
             JACK, QUEEN, KING, };

struct card{
    char *faces_strTest;
    char suits_strTest[9];
};//https://www.cprogramming.com/tutorial/typedef.html
typedef struct card DeckOfCards;//https://www.educative.io/edpresso/how-to-use-the-typedef-struct-in-c

char suits_str[4][9] = {"SPADES", "HEARTS", "DIAMONDS", "CLUBS"};
char *faces_str[13] = {"ACE","TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",\
            "EIGHT", "NINE","TEN", "JACK", "QUEEN", "KING",};//https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
			//https://www.geeksforgeeks.org/multidimensional-arrays-c-cpp/

void startDeck(DeckOfCards []);
void shuffle_CardDeck(DeckOfCards []);
void showCards(const DeckOfCards[]);

int main(int argc, char const *argv[])
{
	int socketc=0, readValue, inetpton, cconnect;
	struct sockaddr_in serv_addr;
	unsigned int portNumber;
	const char *deal="Deal";
	char serv_res[2000], mess[2000], output[1024];
	
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
	
	while(1)
	{
		printf("Type 'Deal':");
		scanf("%s",mess);

		if(send(socketc, mess, strlen(mess),0) <0)
		{
			printf("send failed");
			return 1;	
		}
	
		if(recv(socketc, serv_res,2000,0)<0)
		{
			printf("recieve failed");
			break;
		}
		else
		{

			puts("Server reply :");
			puts(serv_res);
			int compareStrings=strcmp(mess,deal);
			if(compareStrings==0)
			{
				char nl='\t';
				DeckOfCards startingDeck[52]= {"",""};
				startDeck(startingDeck);
	   	 		printf("shuffling deck...\n");
				while('\t'==nl)
    				{
			        	printf("Here are your cards\n");
			        	shuffle_CardDeck(startingDeck);
			        	showCards(startingDeck);
        				printf("\n Done...Disconnect or type 'Deal' again");
        
        				nl=getchar();//user input to get another shuffle
        				//https://www.geeksforgeeks.org/difference-getchar-getch-getc-getche/
    				}
			}
			else if(compareStrings!=0){
				char str[1024]="Wrong key word.'Deal' is the only key word.";
				sprintf(output,"%s",str);
				printf("%s", output);
			}
		}
		
		
	}
	
	close(socketc);
	return 0;
}
void startDeck(DeckOfCards startingDeck[])
{
    int c=0;
    for(c=0;c<52;c++)
    {
        startingDeck[c].faces_strTest=faces_str[c%13];
        strncpy(startingDeck[c].suits_strTest, suits_str[c/13],52);
    }
}
void shuffle_CardDeck(DeckOfCards startingDeck[])//https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
{
    int swaps=0; //card to switch
    int counter=0; //counter
    DeckOfCards temp={"", ""};//temporary for switch
    //https://www.geeksforgeeks.org/generating-random-number-range-c/
    for(counter=0;counter<52; counter++)
    {
        swaps=rand() % 52;
        temp=startingDeck[counter];
        startingDeck[counter]=startingDeck[swaps];
        startingDeck[swaps]=temp;
    }
}
//https://www.geeksforgeeks.org/const-qualifier-in-c/
void showCards(const DeckOfCards startingDeck[])//https://jameshfisher.com/2016/12/02/c-const/
//https://stackoverflow.com/questions/2812875/how-const-keyword-works-in-c
{
   int display=0;
   for(display=0;display<52;display++)//https://stackoverflow.com/questions/1000556/what-does-the-s-format-specifier-mean
   {//http://www.cplusplus.com/reference/cstdio/printf/
       printf("%5s of %-10s",startingDeck[display].faces_strTest,startingDeck[display].suits_strTest);//https://www.sololearn.com/Discuss/1688189/why-we-use-2d-and-5s-in-c-program
       //https://www.tutorialspoint.com/program-to-print-numbers-columns-wise-in-c
       //https://www.eecis.udel.edu/~sprenkle/cisc105/making_columns.html
       //https://cboard.cprogramming.com/cplusplus-programming/56866-program-prints-numbers-columns.html
       if(((display+1)%3)==0)
       {
           printf("\n");
       }
   }

}