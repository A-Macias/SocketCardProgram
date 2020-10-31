
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //random number generator functions
//the max number of cards is 52
// number of each suit is 13 
// there are 4 suits:diamond, spade, club, hearts 

//https://www.programiz.com/c-programming/c-enumeration
//https://www.geeksforgeeks.org/enumeration-enum-c/
//https://stackoverflow.com/questions/3168306/print-text-instead-of-value-from-c-enum
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
            "EIGHT", "NINE","TEN", "JACK", "QUEEN", "KING",};
            
void startDeck(DeckOfCards []);
void shuffle_CardDeck(DeckOfCards []);
void showCards(const DeckOfCards[]);


int main()
{
    char nl='\n';
    DeckOfCards startingDeck[52]= {"",""};
    startDeck(startingDeck);
    printf("shuffling deck...\n");
    
    
    while('\n'==nl)
    {
        printf("Here are your cards\n");
        shuffle_CardDeck(startingDeck);
        showCards(startingDeck);
        printf("\n Done...Press any key to end except 'Enter'");
        
        nl=getchar();//user input to get another shuffle
        //https://www.geeksforgeeks.org/difference-getchar-getch-getc-getche/
    }
    
    
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
       printf("%5s of %-12s",startingDeck[display].faces_strTest,startingDeck[display].suits_strTest);//https://www.sololearn.com/Discuss/1688189/why-we-use-2d-and-5s-in-c-program
       //https://www.tutorialspoint.com/program-to-print-numbers-columns-wise-in-c
       //https://www.eecis.udel.edu/~sprenkle/cisc105/making_columns.html
       //https://cboard.cprogramming.com/cplusplus-programming/56866-program-prints-numbers-columns.html
       if(((display+1)%3)==0)
       {
           printf("\n");
       }
   }

}
