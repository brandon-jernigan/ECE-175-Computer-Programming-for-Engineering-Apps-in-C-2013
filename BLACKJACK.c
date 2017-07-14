//  Created by Jernigan, Brandon Douglas - (brandonjernigan) on 11/22/13.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>


typedef struct card_s {
    char suit[9];
    char name;
    int value;
    struct card_s *pt;
} card;

//Major functions

void StartScreen();//Game start screen
void Initialize_Deck(card **head); //Sets initial values for cards in the deck
void Hand(card **deck, card **handHead, card **handLast);//creates hands and frees deck cards
void ShuffleCards(card **head);//Shuffles Cards
void RefreshDisplay(card *dealHead, card *playHead, card *deckHead, int money, int bet, int win, int gamesPlayed, int pWins, int flipCard);//creates new instance of display screen



//Minor functions
void deleteList(card **head);//deletes a given list
void pause();//stalls additional computation using for loop
void DisplayDealer(card *dealHead, card *deckHead, int gamesPlayed, int flipCard);//display dealer cards
void DisplayBet(int bet, int win, int gamesPlayed, int pWins);//display bet and winnings
void DisplayPlayer(card * playHead, int money, int gamesPlayed);//display player cards
void DisplayInfo(int games, int draws, int pwins, int dwins, int twentyones, int aceTwentyones, char print);//display stats and print to file
void Switch_cards(card *first, card *second);//switches two cards
int RandomNumber(int s);//produces random number from 1-52
void Card_InsertAfter(card *prev, card *next); //Inserts a card into a list




int main(void)
{
	int i;
    int p = 6;//length of pauses
    char c = 'h';//initialize player response to 'hit'
    char play = 'y';//initialize player response to 'yes'
	card *mainHead;//deck list
	card *playerHead = NULL, *playerLast = NULL;//player hand list
	card *dealerHead = NULL, *dealerLast = NULL;//dealer hand list
	card *temp1;//for traversing lists without affecting the list itself
	int playerTot1 = 0;//total player points
	int dealerTot1 = 0;//total deal points
    int moneyTot = 1000;//total money
    int bet = 0;//amount of money bet
    int winnings = 0;//amount of money won
    int games = 0;//number of games
    int pwins = 0;//player wins
    int dwins = 0;//dealer wins
    int draws = 0;//draws
    int twentyones = 0;//number of 21s overall
    int aceTwentyones = 0;//dealer aces resulting in 21
    int pAces = 0;//player aces
    int dAces = 0;//dealer aces
    int flipCard = 0;//flag whether dealer 2nd card face down or up, here it is face down
    char print;//determines if stats printed to file
    int flagDD = 0;
    int flagWin = 0;
    int flagLose = 0;
    int flagDraw = 0;

	
    Initialize_Deck(&mainHead);
    ShuffleCards(&mainHead);
    
    
    
    StartScreen();
    
    //while player still wants to play this loop will execute
    while(play == 'y' || play == 'Y'){
        //ask player how much to bet
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    printf("How much you wanna bet?: ");
    scanf("%d", &bet);
    fflush(stdin);
        
        //stay within this loop until a valid bet is placed
        while(bet < 20 || bet > 200 || bet > moneyTot){

        
        
            if(bet > moneyTot){
                bet = 0;
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
                printf("Nice try guy, you only got $%d. ", moneyTot);
                printf("How much you wanna bet?: ");
                scanf("%d", &bet);
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            }
            if(bet < 0){
                bet = 0;
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
                printf("That doesn't make any sense. ");
                printf("How much you wanna bet?: ");
                scanf(" %d", &bet);
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            }

            if(bet < 20 && bet >= 0){
                bet = 0;
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
                printf("Serious players only, please. $20, minimum. ");
                printf("How much you wanna bet?: ");
                scanf(" %d", &bet);
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            }

            if(bet > 200 && bet <= moneyTot){
                bet = 0;
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
                printf("Whoa there! The maximum bet is $200. ");
                printf("How much you wanna bet?: ");
                scanf(" %d", &bet);
                RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            }
        }
    
    //set money to value after bet
    moneyTot = moneyTot - bet;
    
        
        
    //this entire sequence initializes the player and dealer's first cards in the proper order
    //and produces and shuffles a deck when cards run out
    Hand(&mainHead, &playerHead, &playerLast);
    RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    for(i = 0; i < p/2; i++){
        pause();
    }

    if(mainHead == NULL){
        Initialize_Deck(&mainHead);
        ShuffleCards(&mainHead);
    }
    Hand(&mainHead, &dealerHead, &dealerLast);
    RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    for(i = 0; i < p/2; i++){
        pause();
    }
    if(mainHead == NULL){
        Initialize_Deck(&mainHead);
        ShuffleCards(&mainHead);
    }
    Hand(&mainHead, &playerHead, &playerLast);
    RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    for(i = 0; i < p/2; i++){
        pause();
    }
    if(mainHead == NULL){
        Initialize_Deck(&mainHead);
        ShuffleCards(&mainHead);
    }
    Hand(&mainHead, &dealerHead, &dealerLast);
    RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    for(i = 0; i < p/2; i++){
        pause();
    }
    if(mainHead == NULL){
        Initialize_Deck(&mainHead);
        ShuffleCards(&mainHead);
    }
    
    
    
    //find player hand value and count aces, making the first ace worth 11 if it the total hand remains less than 22
    //later code repeats the revaluing process when the total hand value changes
    temp1 = playerHead;
    while(temp1 != NULL){
        playerTot1 = playerTot1 + temp1->value;
        temp1 = temp1->pt;
    }
    temp1 = playerHead;
    while(temp1 != NULL){
        if(temp1->name == 'A'){
            pAces = 1;
        }
        temp1 = temp1->pt;
    }
    if(pAces == 1){
        if((10 + playerTot1 < 22)){
            playerTot1 = playerTot1 + 10;
        }
    }
    for(i = 0; i < p; i++){
        pause();
    }

    
        
        
    //this loop works the entire time the player is issuing commands to the dealer
    //it implements the rules for hitting, standing and doubling down
	while((c != 's' && c != 'S') && playerTot1 < 21){
        if(bet <= moneyTot && flagDD == 0){
            RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            printf("Hit(h),  Stay(s), or Double Down(d)?: ");
            fflush(stdin);
            scanf(" %c", &c);
        //when the player can't double down
        } else {
            RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            printf("Hit(h) or Stay(s)?: ");
            fflush(stdin);
            scanf(" %c", &c);
            if(c == 'd' || c == 'D'){
                continue;
            }
        }
        //if nonsense is entered
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
		if(c != 'h' && c != 'H' && c != 's' && c != 'S' && c != 'd' && c != 'D'){
			printf("Huh? ");
			continue;
		}
        //implemented only once for doubling down, as many times as allowed for hitting
		if(c == 'h' || c =='H' || c == 'd' || c =='D' ){
            //add new card to hand
			Hand(&mainHead, &playerHead, &playerLast);
            if(mainHead == NULL){
                Initialize_Deck(&mainHead);
                ShuffleCards(&mainHead);
            }
            temp1 = playerHead;
            playerTot1 = 0;
            while(temp1 != NULL){
                playerTot1 = playerTot1 + temp1->value;
                temp1 = temp1->pt;
            }
            //adjust money for double down
            if((c == 'd' || c == 'D') && bet <= moneyTot){
                flagDD = 1;
                moneyTot = moneyTot - bet;
                bet = bet * 2;
            }
            for(i = 0; i < p/2; i++){
                pause();
            }

            RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);


            //reevaluate ace valuing
            temp1 = playerHead;
            while(temp1 != NULL){
                if(temp1->name == 'A'){
                    pAces = 1;
                }
                temp1 = temp1->pt;
            }
            if(pAces == 1){
                if((10 + playerTot1 < 22)){
                    playerTot1 = playerTot1 + 10;
                }
            }
            //break from loop if doubled down
            if(c == 'd' || c == 'D'){
                break;
            }
        }
	}
    
    //check valuing of aces for the dealer
    temp1 = dealerHead;
    while(temp1 != NULL){
        dealerTot1 = dealerTot1 + temp1->value;
        temp1 = temp1->pt;
    }
    temp1 = dealerHead;
    while(temp1 != NULL){
        if(temp1->name == 'A'){
            dAces = 1;
        }
        temp1 = temp1->pt;
    }
    if(dAces == 1){
        if((10 + dealerTot1 < 22)){
            dealerTot1 = dealerTot1 + 10;
        }
    }
        
    //turn card over in display
    flipCard = 1;
    RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
        
        
        
    //this loop implements the dealer's rules
	while(dealerTot1 < 17){
        //add cards, initialize new deck and shuffle if no more cards in deck
        Hand(&mainHead, &dealerHead, &dealerLast);
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
        for(i = 0; i < p/2; i++){
            pause();
        }
        if(mainHead == NULL){
            Initialize_Deck(&mainHead);
            ShuffleCards(&mainHead);
        }
        
        //reevaluate total score and ace values
        temp1 = dealerHead;
        dealerTot1 = 0;
        while(temp1 != NULL){
            dealerTot1 = dealerTot1 + temp1->value;
            temp1 = temp1->pt;
        }
        while(temp1 != NULL){
            if(temp1->name == 'A'){
                dAces = 1;
            }
            temp1 = temp1->pt;
        }
        if(dAces == 1){
            if((10 + dealerTot1 < 22)){
                dealerTot1 = dealerTot1 + 10;
            }
        }
        
        //update screen
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
    }

        
        
        //implements rules on money betted
        if(playerTot1 == 21 && dealerTot1 != 21){
            winnings = bet * 1.5;
            pwins++;
            flagWin = 1;
        } else if((playerTot1 > dealerTot1 && playerTot1 < 22) || (playerTot1 < 22 && dealerTot1 >= 22)){
            winnings = bet;
            pwins++;
            flagWin = 1;
        } else if ((playerTot1 == dealerTot1) && playerTot1 < 22){
            draws++;
            flagDraw = 1;
        } else {
            dwins++;
            bet = 0;
            flagLose = 1;
        }
        
        //update display with bet result information
        for(i = 0; i < p; i++){
            pause();
        }
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);

        for(i = 0; i < p/2; i++){
            pause();
        }
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
        
        //calculate ace stats
        if(dealerTot1 == 21){
            twentyones++;
            if(dealerHead->name == 'A'){
                aceTwentyones++;
            }
        }
        if(playerTot1 == 21){
            twentyones++;
        }
        
        
        
        //ask to play again, or buy back in when low
        if(flagWin == 1){
            if(playerTot1 ==21){
                printf("Blackjack! ");
            }
            printf("You won! ");
        }
        if(flagLose == 1){
            printf("You lost! ");
        }
        if(flagDraw == 1){
            printf("It's a draw! ");
        }
        if(moneyTot >= 20){
        printf("Play again?(y/n):");
        scanf(" %c", &play);
        RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
        } else{
            printf("You're getting low. Buy back in for $1000 and play again?(y/n):");
            scanf(" %c", &play);
            RefreshDisplay(dealerHead, playerHead, mainHead, moneyTot, bet, winnings, games, pwins, flipCard);
            if(play == 'y'){
                moneyTot = moneyTot + 1000;
            }
        }
        
        
        //reset game counters and flags, delete hands, count number of games
        moneyTot = moneyTot + bet + winnings;
        bet = 0;
        winnings = 0;
        pAces = 0;
        dAces = 0;
        playerTot1 = 0;
        dealerTot1 = 0;
        c = 'h';
        flipCard = 0;
        flagDD = 0;
        flagWin = 0;
        flagLose = 0;
        flagDraw = 0;
        games++;
        deleteList(&dealerHead);
        deleteList(&playerHead);
        ShuffleCards(&mainHead);

        
    }

    
    //when quitting game, delete deck, print stats to file and display stats
    printf("Print stats to file?(y/n):");
    scanf(" %c", &print);
    deleteList(&mainHead);
    DisplayInfo(games, draws, pwins, dwins, twentyones, aceTwentyones, print);

    return 0;
}



void deleteList(card **head){
    card **temp1 = head;
    
    while(*head != NULL){
        temp1 = head;
        //free(*head);//This line worked in Xcode, but not in Visual Studio!
        *head = (*temp1)->pt;
    }
    head = NULL;
}



void Hand(card **deck, card **handHead, card **handLast){
	card  *temp1,  *t2;
    
    
    //create head of hand if none exists
	if(*handHead == NULL){
        *handHead = (card*) malloc(sizeof(card));
		(*handHead)->name = (*deck)->name;
		strcpy((*handHead)->suit, (*deck)->suit);
		(*handHead)->value = (*deck)->value;
        (*handHead)->pt = NULL;
        *handLast = *handHead;
    //add to existing hand head
	} else{
		t2 = (card*) malloc(sizeof(card));
		t2->name = (*deck)->name;
		strcpy(t2->suit, (*deck)->suit);
		t2->value = (*deck)->value;
        t2->pt = NULL;
        (*handLast)->pt = t2;
        *handLast = t2;
	}
    
    //free memory, reassign deck head to what it pointed to
	temp1 = (*deck)->pt ;
	free(*deck);
    *deck = NULL;
    *deck = temp1;
    
}


void Initialize_Deck(card **head)
{
    card *current, *last;
    int i, n;
    
    //initialize head of deck
    *head = (card*) malloc(sizeof(card));
    (*head)->name = 'A';
    strcpy((*head)->suit, "Spades");
    (*head)->value =  1;
    (*head)->pt = NULL;
    last = *head;
    
    //Initialize details of cards in list
    for(i = 2, n = 2; i < 53; i++, n++){
        current = (card*) malloc(sizeof(card));
        
        //Set suit
        if(i < 14) strcpy(current->suit, "Spades");
        if(i >= 14 && i < 27) strcpy(current->suit, "Hearts");
        if(i >= 27 && i < 40) strcpy(current->suit, "Clubs");
        if(i >= 40 && i < 54) strcpy(current->suit, "Diamonds");
        
        //Set name and value
        if(n > 1 && n < 11){
            current->name = 'N';
            current->value = n;
        }
        switch(n){
            case 1:
                current->name = 'A';
                current->value = 1;
                break;
            case 11:
                current->name = 'J';
                current->value = 10;
                break;
            case 12:
                current->name = 'Q';
                current->value = 10;
                break;
            case 13:
                current->name = 'K';
                current->value = 10;
                n = 0;
                break;
        }
        
        //Link current card to previous and make current card the new previous card for next iteration
        current->pt = NULL;
        
        Card_InsertAfter(last, current);
    
        
        last = current;
    }
}



void Card_InsertAfter(card *prev, card *next)
{
    card *temp;
    
    //inserts a card after another in a list
    temp = prev->pt;
    prev->pt = next;
    next->pt = temp;
    
}



int RandomNumber(int s)
{
	double frac;
	int index;
	int i;
	
    
    
	srand((int)time(NULL));
	//produce random number list based on given length.
    //A list must be created because the time seed doesn't change much from moment to moment
    //but a list can give a large range of values
	for(i = 0; i < s; i++){
	frac = (double)rand()/((double)RAND_MAX+1);
	index = floor((52)*frac);
	}

	return index;
}

void Switch_cards(card *first, card *second)
{
		card *temp;
        //switches two cards
		temp = (card*) malloc(sizeof(card));

		temp->name = second->name;
		temp->value = second->value; 
		strcpy(temp->suit, second->suit);

		second->name = first->name;
		second->value = first->value; 
		strcpy(second->suit, first->suit);

		first->name = temp->name;
		first->value = temp->value; 
		strcpy(first->suit, temp->suit);

		free(temp);
        //frees the temp values
}


void ShuffleCards(card **head)
{
	card *temp1;
	int r, i, j;
    float scale = 0;
    
    //counts the cards so the random number 91-52) can be scaled down more toward the deck size
    //without this the final card in the list would end up getting shuffelled more and more often as the deck gets shorter
    temp1 = *head;
    while(temp1 != NULL){
        scale++;
        temp1 = temp1->pt;
    }
    scale = scale / 52;
    
	temp1 = *head;
    
	for(j = 2; j < 10000; j++){

		r = RandomNumber(j) * scale;

		for(i = 0; i < r && temp1->pt != NULL; i++){

		   temp1 = temp1->pt;


		}
		Switch_cards(*head, temp1);
		temp1 = *head;
	}
}


void pause(){
    int i;
    //inserted for game pauses
    for(i = 0; i < 100000000; i++){
    }
}

void StartScreen(){
    int j;
    
    for(j = 0; j < 6; j++){
        
        printf("o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o\n");
        printf("                                                                               \n");
        printf("o                                                                             o\n");
        printf("            ______       ____            ____         _____      __     ___    \n");
        printf("o          /     /_     /   /          _/   /_      _/    /_    / /   _/ _/   o\n");
        printf("          /   __  /_   /   /         _/      /_   _/  __   /   / / _ / _/      \n");
        printf("o        /   /_/   /  /   /         /   __    /  /   / /__/   / /_/ __/       o\n");
        printf("        /         /  /   /         /   /_/   /  /   /        /     /           \n");
        printf("o      /   __    /  /   /         /         /  /   / ____   /  __ /_          o\n");
        printf("      /   /_/  _/  /   /______   /  ____   /  /_  /_/   /  /  / /_ /_          \n");
        printf("o    /       _/   /          /  /  /   /  /    /_     _/  /  /   /_ /_        o\n");
        printf("    /_______/    /__________/  /__/   /__/      /____/   /__/     /__/         \n");
        printf("o                 ____      ____         _____      __     ___                o\n");
        printf("                 /   /    _/   /_      _/    /_    / /   _/ _/                 \n");
        printf("o               /   /   _/      /_   _/  __   /   / / _ / _/                  o\n");
        printf("               /   /   /   __    /  /   / /__/   / /_/ __/                     \n");
        printf("o       ___   /   /   /   /_/   /  /   /        /     /                       o\n");
        printf("       /  /  /   /   /         /  /   / ____   /  __ /_                        \n");
        printf("o     /  /__/   /   /  ____   /  /_  /_/   /  /  / /_ /_                      o\n");
        printf("     /         /   /  /   /  /    /_     _/  /  /   /_ /_                      \n");
        printf("o   /_________/   /__/   /__/      /____/   /__/     /__/                     o\n");
        printf("                                                                               \n");
        printf("o                                                                             o\n");
        printf("  o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o  \n");
        pause();
        //printf("\f");
        printf(" o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o \n");
        printf("o                                                                             o\n");
        printf("                                                                               \n");
        printf("o           ______       ____            ____         _____      __     ___   o\n");
        printf("           /     /_     /   /          _/   /_      _/    /_    / /   _/ _/    \n");
        printf("o         /   __  /_   /   /         _/      /_   _/  __   /   / / _ / _/     o\n");
        printf("         /   /_/   /  /   /         /   __    /  /   / /__/   / /_/ __/        \n");
        printf("o       /         /  /   /         /   /_/   /  /   /        /     /          o\n");
        printf("       /   __    /  /   /         /         /  /   / ____   /  __ /_           \n");
        printf("o     /   /_/  _/  /   /______   /  ____   /  /_  /_/   /  /  / /_ /_         o\n");
        printf("     /       _/   /          /  /  /   /  /    /_     _/  /  /   /_ /_         \n");
        printf("o   /_______/    /__________/  /__/   /__/      /____/   /__/     /__/        o\n");
        printf("                  ____      ____         _____      __     ___                 \n");
        printf("o                /   /    _/   /_      _/    /_    / /   _/ _/                o\n");
        printf("                /   /   _/      /_   _/  __   /   / / _ / _/                   \n");
        printf("o              /   /   /   __    /  /   / /__/   / /_/ __/                    o\n");
        printf("        ___   /   /   /   /_/   /  /   /        /     /                        \n");
        printf("o      /  /  /   /   /         /  /   / ____   /  __ /_                       o\n");
        printf("      /  /__/   /   /  ____   /  /_  /_/   /  /  / /_ /_                       \n");
        printf("o    /         /   /  /   /  /    /_     _/  /  /   /_ /_                     o\n");
        printf("    /_________/   /__/   /__/      /____/   /__/     /__/                      \n");
        printf("o                                                                             o\n");
        printf("                                                                               \n");
        printf(" o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o \n");
        
        pause();

    }
}



void DisplayDealer(card *dealHead, card *deckHead, int gamesPlayed, int flipCard){
    int i, j = 1;
    int faceRow;
    card *temp1;
    int deck = 0;
    
    int deckState;
    int numberCards1 = 0;
    int numberCards2;
    char suitString[9];
    
    
    //these produce the values for different cards, called as needed when displaying line by line
    //setting these up takes up a very large section following this
    int value = 0, value1 = 0, value2 = 0, value3 = 0, value4 = 0, value5 = 0, value6 = 0;
	int suitRep = 0, suitRep1 = 0, suitRep2 = 0, suitRep3 = 0, suitRep4 = 0, suitRep5 = 0, suitRep6 = 0;
    int typeRep = 0, typeRep1 = 0, typeRep2 = 0, typeRep3 = 0, typeRep4 = 0, typeRep5 = 0, typeRep6 = 0;
	char suit = 'B', suit1 = 'B', suit2 = 'B', suit3 = 'B', suit4 = 'B', suit5 = 'B', suit6 = 'B';
    char type = 'N', type1 = 'N', type2 = 'N', type3 = 'N', type4 = 'N', type5 = 'N', type6 = 'N';
    
    temp1 = deckHead;
    while(temp1 != NULL){
        deck++;
        temp1 = temp1->pt;
    }
    
    if(deck > 30){
        deckState = 3;
    } else if(deck > 5){
        deckState = 2;
    } else if(deck > 0){
        deckState = 1;
    } else {
        deckState = 0;
    }
    
    temp1 = dealHead;
    while(temp1 != NULL){
        numberCards1++;
        temp1 = temp1->pt;
    }
    numberCards2 = numberCards1;
    
    
    if(numberCards1 > 0){
    value1 = dealHead->value;
    strcpy(suitString, dealHead->suit);
	suit1 = suitString[0];
    type1 = dealHead->name;
    }
    
    if(numberCards1 > 1){
        value2 = dealHead->pt->value;
        strcpy(suitString, dealHead->pt->suit);
        suit2 = suitString[0];
        type2 = dealHead->pt->name;
    }
    
    if(flipCard == 1){
            value2 = dealHead->pt->value;
            strcpy(suitString, dealHead->pt->suit);
            suit2 = suitString[0];
            type2 = dealHead->pt->name;
    } else {
        value2 = 0;
        suit2 = 'B';
    }
    
    if(numberCards1 > 2){
        value3 = dealHead->pt->pt->value;
        strcpy(suitString, dealHead->pt->pt->suit);
        suit3 = suitString[0];
        type3 = dealHead->pt->pt->name;
    }
    
    if(numberCards1 > 3){
        value4 = dealHead->pt->pt->pt->value;
        strcpy(suitString, dealHead->pt->pt->pt->suit);
        suit4 = suitString[0];
        type4 = dealHead->pt->pt->pt->name;
    }
    
    if(numberCards1 > 4){
        value5 = dealHead->pt->pt->pt->pt->value;
        strcpy(suitString, dealHead->pt->pt->pt->pt->suit);
        suit5 = suitString[0];
        type5 = dealHead->pt->pt->pt->pt->name;
    }
    
    if(numberCards1 > 5){
        value6 = dealHead->pt->pt->pt->pt->pt->value;
        strcpy(suitString, dealHead->pt->pt->pt->pt->pt->suit);
        suit6 = suitString[0];
        type6 = dealHead->pt->pt->pt->pt->pt->name;
    }
    
    
	if (type1 == 'J') typeRep1 = 1;
	if (type1 == 'Q') typeRep1 = 2;
	if (type1 == 'K') typeRep1 = 3;
    
    if (type2 == 'J') typeRep2 = 1;
	if (type2 == 'Q') typeRep2 = 2;
	if (type2 == 'K') typeRep2 = 3;
    
    if (type3 == 'J') typeRep3 = 1;
	if (type3 == 'Q') typeRep3 = 2;
	if (type3 == 'K') typeRep3 = 3;
    
    if (type4 == 'J') typeRep4 = 1;
	if (type4 == 'Q') typeRep4 = 2;
	if (type4 == 'K') typeRep4 = 3;
    
    if (type5 == 'J') typeRep5 = 1;
	if (type5 == 'Q') typeRep5 = 2;
	if (type5 == 'K') typeRep5 = 3;
    
    if (type6 == 'J') typeRep6 = 1;
	if (type6 == 'Q') typeRep6 = 2;
	if (type6 == 'K') typeRep6 = 3;
    
	
    
    if (suit1 == 'B') suitRep1 = 0;
	if (suit1 == 'D') suitRep1 = 1;
	if (suit1 == 'S') suitRep1 = 2;
	if (suit1 == 'C') suitRep1 = 3;
	if (suit1 == 'H') suitRep1 = 4;
    
    if (suit2 == 'B') suitRep2 = 0;
	if (suit2 == 'D') suitRep2 = 1;
	if (suit2 == 'S') suitRep2 = 2;
	if (suit2 == 'C') suitRep2 = 3;
	if (suit2 == 'H') suitRep2 = 4;
    
    if (suit3 == 'B') suitRep3 = 0;
	if (suit3 == 'D') suitRep3 = 1;
	if (suit3 == 'S') suitRep3 = 2;
	if (suit3 == 'C') suitRep3 = 3;
	if (suit3 == 'H') suitRep3 = 4;
    
    if (suit4 == 'B') suitRep4 = 0;
	if (suit4 == 'D') suitRep4 = 1;
	if (suit4 == 'S') suitRep4 = 2;
	if (suit4 == 'C') suitRep4 = 3;
	if (suit4 == 'H') suitRep4 = 4;
    
    if (suit5 == 'B') suitRep5 = 0;
	if (suit5 == 'D') suitRep5 = 1;
	if (suit5 == 'S') suitRep5 = 2;
	if (suit5 == 'C') suitRep5 = 3;
	if (suit5 == 'H') suitRep5 = 4;
    
    if (suit6 == 'B') suitRep6 = 0;
	if (suit6 == 'D') suitRep6 = 1;
	if (suit6 == 'S') suitRep6 = 2;
	if (suit6 == 'C') suitRep6 = 3;
	if (suit6 == 'H') suitRep6 = 4;
    
    
    value = value1;
    suitRep = suitRep1;
    typeRep = typeRep1;
    suit = suit1;
    type = type1;
    
    
    //first round shows labels
    if(gamesPlayed ==0){
    printf("                 Dealer's Hand");
    }
    printf("\n");

    
    //first line of deck, depending on number of cards in deck
	switch(deckState){
        case 0:
			printf("         ");
			break;
		case 1:
			printf(" ------- ");
			break;
        case 2:
			printf(" -------.");
			break;
        case 3:
			printf(" -------.");
			break;
	}
    printf("       ");
    
    //displays top of cards based only on number of cards present, or not present
    while(numberCards2 > 0){
        printf(" -------");
        printf("  ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    
    printf("\n");
    
    
    //next portion of deck
    switch(deckState){
        case 0:
			printf("          ");
			break;
        case 1:
			printf("|{}{}{}{| ");
			break;
		case 2:
			printf("|{}{}{}{|,");
			break;
        case 3:
			printf("|{}{}{}{|,");
			break;
    }
    printf("      ");
    
    //value and type of card
    while(numberCards2 > 0){
        
        switch(value){
            case 0:
                printf("|{}{}{}{|");
                break;
            case 1:
                printf("|A      |");
                break;
            case 2:
                printf("|2      |");
                break;
            case 3:
                printf("|3      |");
                break;
            case 4:
                printf("|4      |");
                break;
            case 5:
                printf("|5      |");
                break;
            case 6:
                printf("|6      |");
                break;
            case 7:
                printf("|7      |");
                break;
            case 8:
                printf("|8      |");
                break;
            case 9:
                printf("|9      |");
                break;
            case 10:
                switch(typeRep){
                    case 1:
                        printf("|J      |");
                        break;
                    case 2:
                        printf("|Q      |");
                        break;
                    case 3:
                        printf("|K      |");
                        break;
                    default:
                        printf("|10     |");
                        break;
                }
        }
        j++;
        switch(j){
            case 2:
                value = value2;
                typeRep = typeRep2;
                break;
            case 3:
                value = value3;
                typeRep = typeRep3;
                break;
            case 4:
                value = value4;
                typeRep = typeRep4;
                break;
            case 5:
                value = value5;
                typeRep = typeRep5;
                break;
            case 6:
                value = value6;
                typeRep = typeRep6;
                break;
        }
        printf(" ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    value = value1;
    typeRep = typeRep1;
    j = 1;
    printf("\n");
    
    
    
    //face portion of cards displayed
    for(faceRow = 1; faceRow <= 4; faceRow++){
        switch(deckState){
            case 0:
                printf("          ");
                break;
            case 1:
                printf("|{}{}{}{| ");
                break;
            case 2:
                printf("|}{}{}{}||");
                break;
            case 3:
                printf("|{}{}{}{||");
                break;
        }
        printf("      ");
        while(numberCards2 > 0){
            switch(suitRep){
                case 0:
                    printf("|}{}{}{}|");
                    break;
                case 1:
                    switch(faceRow){
                        case 1:
                            printf("|   ,   |");
                            break;
                        case 2:
                            printf("|  / \\  |");
                            break;
                        case 3:
                            printf("|  \\ /  |");
                            break;
                        case 4:
                            printf("|   `   |");
                            break;
                    }
                    break;
                case 2:
                    switch(faceRow){
                        case 1:
                            printf("|   ^   |");
                            break;
                        case 2:
                            printf("|  / \\  |");
                            break;
                        case 3:
                            printf("|   ^   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
                case 3:
                    switch(faceRow){
                        case 1:
                            printf("|   o   |");
                            break;
                        case 2:
                            printf("|  o o  |");
                            break;
                        case 3:
                            printf("|   ^   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
                case 4:
                    switch(faceRow){
                        case 1:
                            printf("| ( v ) |");
                            break;
                        case 2:
                            printf("|  \\ /  |");
                            break;
                        case 3:
                            printf("|   V   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
            }
            j++;
            switch(j){
                case 2:
                    
                    suitRep = suitRep2;
                    break;
                case 3:
                    
                    suitRep = suitRep3;
                    break;
                case 4:
                    
                    suitRep = suitRep4;
                    break;
                case 5:
                    
                    suitRep = suitRep5;
                    break;
                case 6:
                    suitRep = suitRep6;
                    break;
            }
            printf(" ");
            numberCards2--;
        }
        numberCards2 = numberCards1;
        while(5 - numberCards2 > 0){
            printf("         ");
            printf("  ");
            numberCards2++;
        }
        numberCards2 = numberCards1;
        suitRep = suitRep1;
        j = 1;
        printf("\n");
    }
    
    //bottom of deck display
    switch(deckState){
        case 0:
			printf("          ");
			break;
        case 1:
			printf("|{}{}{}{| ");
			break;
		case 2:
			printf("|}{}{}{}||");
			break;
        case 3:
			printf("|}{}{}{}||");
			break;
    }
    printf("      ");
    
    
    //bottom of card display, shows values
    while(numberCards2 > 0){
        
        switch(value){
            case 0:
                printf("|{}{}{}{|");
                break;
            case 1:
                printf("|      A|");
                break;
            case 2:
                printf("|      2|");
                break;
            case 3:
                printf("|      3|");
                break;
            case 4:
                printf("|      4|");
                break;
            case 5:
                printf("|      5|");
                break;
            case 6:
                printf("|      6|");
                break;
            case 7:
                printf("|      7|");
                break;
            case 8:
                printf("|      8|");
                break;
            case 9:
                printf("|      9|");
                break;
            case 10:
                switch(typeRep){
                    case 1:
                        printf("|      J|");
                        break;
                    case 2:
                        printf("|      Q|");
                        break;
                    case 3:
                        printf("|      K|");
                        break;
                    default:
                        printf("|     10|");
                        break;
                }
        }
        j++;
        switch(j){
            case 2:
                value = value2;
                typeRep = typeRep2;
                break;
            case 3:
                value = value3;
                typeRep = typeRep3;
                break;
            case 4:
                value = value4;
                typeRep = typeRep4;
                break;
            case 5:
                value = value5;
                typeRep = typeRep5;
                break;
            case 6:
                value = value6;
                typeRep = typeRep6;
                break;
        }
        printf(" ");
        numberCards2--;
    }
    
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    value = value1;
    typeRep = typeRep1;
    j = 1;
    printf("\n");
    
    
    //very bottom of deck
    switch(deckState){
        case 0:
			printf("          ");
            printf("      ");
			break;
		case 1:
			printf(" -------  ");
            printf("      ");
			break;
        case 2:
			printf("._______.|");
            printf("      ");
			break;
        case 3:
			printf(".-------.|");
            printf("      ");
			break;
	}
    
    while(numberCards2 > 0){
        printf(" -------");
        printf("  ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    
    printf("\n");

    switch(deckState){
        case 0:
			printf("          ");
            printf("  ");
			break;
		case 1:
			printf("          ");
            printf("  ");
			break;
        case 2:
			printf(" `-------`");
            printf("  ");
			break;
        case 3:
			printf(" `-------`");
            printf("  ");
			break;
	}
    for(i = 0; i < 5; i++){
        printf("         ");
        printf("  ");
    }
	printf("\n");
    
    
}

void DisplayBet(int bet, int win, int gamesPlayed, int pWins){
    
    //display bet and winning so that it accomadates their presence and the size of
    //the number on them, also only shows labels the first time
    if(win == 0){
        if(bet > 0){
            printf("                               .--.               \n");
            if(gamesPlayed == 0){
                if(bet < 100){
                    printf("                          Bet / $%d\\               \n", bet);
                } else {
                    printf("                          Bet /$%d\\               \n", bet);
                }
            } else {
                if(bet < 100){
                    printf("                              / $%d\\               \n", bet);
                } else {
                    printf("                              /$%d\\               \n", bet);
                }
            }
            printf("                              \\    /               \n");
            printf("                               '--'               \n");
            
        } else {
            printf("\n\n\n\n\n");
        }
    }
    if(win < 0){
        printf("\n\n\n\n\n");
    }
    if(win > 0){
        printf("                               .--.    .--.             \n");
        if(gamesPlayed == 0 || pWins == 0){
            if(bet < 100 && win < 100){
                printf("                          Bet / $%d\\  / $%d\\ Winnings       \n", bet, win);
            } else if(bet < 100) {
                printf("                          Bet / $%d\\  /$%d\\ Winnings       \n", bet, win);
            } else if (win < 100){
                printf("                          Bet /$%d\\  / $%d\\ Winnings       \n", bet, win);
            } else {
                printf("                          Bet /$%d\\  /$%d\\ Winnings       \n", bet, win);
            }
        } else {
            if(bet < 100 && win < 100){
                printf("                              / $%d\\  / $%d\\                 \n", bet, win);
            } else if(bet < 100) {
                printf("                              / $%d\\  /$%d\\                \n", bet, win);
            } else if (win < 100){
                printf("                              /$%d\\  / $%d\\                \n", bet, win);
            } else {
                printf("                              /$%d\\  /$%d\\               \n", bet, win);
            }
        }

        printf("                              \\    /  \\    /             \n");
        printf("                               '--'    '--'           \n");
    }
    
    
}



void DisplayPlayer(card * playHead, int money, int gamesPlayed){
    int j = 1;
    int faceRow;
    int moneyState;
    card *temp1;
    int numberCards1 = 0;
    int numberCards2;
	char suitString[9];
    
    //these produce the values for different cards, called as needed when displaying line by line
    //setting these up takes up a very large section following this
    int value = 0, value1 = 0, value2 = 0, value3 = 0, value4 = 0, value5 = 0, value6 = 0;
	int suitRep = 0, suitRep1 = 0, suitRep2 = 0, suitRep3 = 0, suitRep4 = 0, suitRep5 = 0, suitRep6 = 0;
    int typeRep = 0, typeRep1 = 0, typeRep2 = 0, typeRep3 = 0, typeRep4 = 0, typeRep5 = 0, typeRep6 = 0;
	char suit = 'B', suit1 = 'B', suit2 = 'B', suit3 = 'B', suit4 = 'B', suit5 = 'B', suit6 = 'B';
    char type = 'N', type1 = 'N', type2 = 'N', type3 = 'N', type4 = 'N', type5 = 'N', type6 = 'N';
    
    temp1 = playHead;
    while(temp1 != NULL){
        numberCards1++;
        temp1 = temp1->pt;
    }
    numberCards2 = numberCards1;

    
    if(numberCards1 > 0){
    value1 = playHead->value;
    strcpy(suitString, playHead->suit);
	suit1 = suitString[0];
    type1 = playHead->name;
    }
    
    if(numberCards1 > 1){
    value2 = playHead->pt->value;
    strcpy(suitString, playHead->pt->suit);
	suit2 = suitString[0];
    type2 = playHead->pt->name;
    }
    
    if(numberCards1 > 2){
    value3 = playHead->pt->pt->value;
    strcpy(suitString, playHead->pt->pt->suit);
	suit3 = suitString[0];
    type3 = playHead->pt->pt->name;
    }
    
    if(numberCards1 > 3){
        value4 = playHead->pt->pt->pt->value;
        strcpy(suitString, playHead->pt->pt->pt->suit);
        suit4 = suitString[0];
        type4 = playHead->pt->pt->pt->name;
    }
    
    if(numberCards1 > 4){
        value5 = playHead->pt->pt->pt->pt->value;
        strcpy(suitString, playHead->pt->pt->pt->pt->suit);
        suit5 = suitString[0];
        type5 = playHead->pt->pt->pt->pt->name;
    }

    if(numberCards1 > 5){
        value6 = playHead->pt->pt->pt->pt->pt->value;
        strcpy(suitString, playHead->pt->pt->pt->pt->pt->suit);
        suit6 = suitString[0];
        type6 = playHead->pt->pt->pt->pt->pt->name;
    }
    
    if(money <= 0){
        moneyState = 0;
    } else if(money < 300){
        moneyState = 1;
    } else if(money <= 600){
        moneyState = 2;
    } else{
        moneyState = 3;
    }
    
    
	if (type1 == 'J') typeRep1 = 1;
	if (type1 == 'Q') typeRep1 = 2;
	if (type1 == 'K') typeRep1 = 3;
    
    if (type2 == 'J') typeRep2 = 1;
	if (type2 == 'Q') typeRep2 = 2;
	if (type2 == 'K') typeRep2 = 3;
    
    if (type3 == 'J') typeRep3 = 1;
	if (type3 == 'Q') typeRep3 = 2;
	if (type3 == 'K') typeRep3 = 3;
    
    if (type4 == 'J') typeRep4 = 1;
	if (type4 == 'Q') typeRep4 = 2;
	if (type4 == 'K') typeRep4 = 3;
    
    if (type5 == 'J') typeRep5 = 1;
	if (type5 == 'Q') typeRep5 = 2;
	if (type5 == 'K') typeRep5 = 3;
    
    if (type6 == 'J') typeRep6 = 1;
	if (type6 == 'Q') typeRep6 = 2;
	if (type6 == 'K') typeRep6 = 3;
	
    
    if (suit1 == 'B') suitRep1 = 0;
	if (suit1 == 'D') suitRep1 = 1;
	if (suit1 == 'S') suitRep1 = 2;
	if (suit1 == 'C') suitRep1 = 3;
	if (suit1 == 'H') suitRep1 = 4;
    
    if (suit2 == 'B') suitRep2 = 0;
	if (suit2 == 'D') suitRep2 = 1;
	if (suit2 == 'S') suitRep2 = 2;
	if (suit2 == 'C') suitRep2 = 3;
	if (suit2 == 'H') suitRep2 = 4;
    
    if (suit3 == 'B') suitRep3 = 0;
	if (suit3 == 'D') suitRep3 = 1;
	if (suit3 == 'S') suitRep3 = 2;
	if (suit3 == 'C') suitRep3 = 3;
	if (suit3 == 'H') suitRep3 = 4;
    
    if (suit4 == 'B') suitRep4 = 0;
	if (suit4 == 'D') suitRep4 = 1;
	if (suit4 == 'S') suitRep4 = 2;
	if (suit4 == 'C') suitRep4 = 3;
	if (suit4 == 'H') suitRep4 = 4;
    
    if (suit5 == 'B') suitRep5 = 0;
	if (suit5 == 'D') suitRep5 = 1;
	if (suit5 == 'S') suitRep5 = 2;
	if (suit5 == 'C') suitRep5 = 3;
	if (suit5 == 'H') suitRep5 = 4;
    
    if (suit6 == 'B') suitRep6 = 0;
	if (suit6 == 'D') suitRep6 = 1;
	if (suit6 == 'S') suitRep6 = 2;
	if (suit6 == 'C') suitRep6 = 3;
	if (suit6 == 'H') suitRep6 = 4;
    
    
    value = value1;
    suitRep = suitRep1;
    typeRep = typeRep1;
    suit = suit1;
    type = type1;
    
    if(gamesPlayed == 0){
        printf("                 Your Hand");
    }
    printf("\n");
    
    //top of chip pile, based on amount of money
	switch(moneyState){
        case 0:
			printf("         ");
			break;
		case 1:
            printf("         ");
			break;
        case 2:
            printf("         ");
			break;
        case 3:
			printf("  .-\"\"-. ");
			break;
	}
    printf("       ");
    
    
    //displays top of cards based only on number of cards present, or not present
    while(numberCards2 > 0){
        printf(" -------");
        printf("  ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    
    printf("\n");
    
    // next line of money
    switch(moneyState){
        case 0:
			printf("          ");
			break;
        case 1:
            printf("          ");
			break;
		case 2:
            printf("  .-\"\"-.  ");
			break;
        case 3:
			printf(" /      \\ ");
			break;
    }
    printf("      ");
    
    //value of cards
    while(numberCards2 > 0){
        switch(value){
            case 0:
                printf("|{}{}{}{|");
                break;
            case 1:
                printf("|A      |");
                break;
            case 2:
                printf("|2      |");
                break;
            case 3:
                printf("|3      |");
                break;
            case 4:
                printf("|4      |");
                break;
            case 5:
                printf("|5      |");
                break;
            case 6:
                printf("|6      |");
                break;
            case 7:
                printf("|7      |");
                break;
            case 8:
                printf("|8      |");
                break;
            case 9:
                printf("|9      |");
                break;
            case 10:
                switch(typeRep){
                    case 1:
                        printf("|J      |");
                        break;
                    case 2:
                        printf("|Q      |");
                        break;
                    case 3:
                        printf("|K      |");
                        break;
                    default:
                        printf("|10     |");
                        break;
                }
        }
        j++;
        switch(j){
            case 2:
                value = value2;
                typeRep = typeRep2;
                break;
            case 3:
                value = value3;
                typeRep = typeRep3;
                break;
            case 4:
                value = value4;
                typeRep = typeRep4;
                break;
            case 5:
                value = value5;
                typeRep = typeRep5;
                break;
            case 6:
                value = value6;
                typeRep = typeRep6;
                break;
        }
        printf(" ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    value = value1;
    typeRep = typeRep1;
    j = 1;
    printf("\n");
    
    
    //display middle portion of money based on money amount
    for(faceRow = 1; faceRow <= 4; faceRow++){
        switch(faceRow){
            case 1:
                switch(moneyState){
                    case 0:
                        printf("          ");
                        break;
                    case 1:
                        printf("  .-\"\"-.  ");
                        break;
                    case 2:
                        printf(" /      \\ ");
                        break;
                    case 3:
                        if(money < 1000){
                            printf(" : $%d : ", money);
                        }else {
                            printf(" : $%d: ", money);
                        }
                        break;
                }
                break;
            case 2:
                switch(moneyState){
                    case 0:
                        printf("          ");
                        break;
                    case 1:
                        printf(" /      \\ ");
                        break;
                    case 2:
                        printf(" : $%d : ", money);
                        break;
                    case 3:
                        printf(" \\      /`");
                        break;
                        
                }
                break;
            case 3:
                switch(moneyState){
                    case 0:
                        printf("          ");
                        break;
                    case 1:
                        if(money < 10){
                            printf(" :  $%d  : ", money);
                        }else if(money < 100){
                            printf(" :  $%d : ", money);
                        } else {
                            printf(" : $%d : ", money);
                        }
                        break;
                    case 2:
                        printf(" \\      /`");
                        break;
                    case 3:
                        printf(" `'-..-'/`");
                        break;
                        
                }
                break;
            case 4:
                switch(moneyState){
                    case 0:
                        printf("          ");
                        break;
                    case 1:
                        printf(" \\      / ");
                        break;
                    case 2:
                        printf(" `'-..-'/`");
                        break;
                    case 3:
                        printf(" `'-..-'/`");
                        break;
                        
                }
                break;
                
        }
        printf("      ");
        
        
        //display suit of cards card by card, line by line
        while(numberCards2 > 0){
            switch(suitRep){
                case 0:
                    printf("|}{}{}{}|");
                    break;
                case 1:
                    switch(faceRow){
                        case 1:
                            printf("|   ,   |");
                            break;
                        case 2:
                            printf("|  / \\  |");
                            break;
                        case 3:
                            printf("|  \\ /  |");
                            break;
                        case 4:
                            printf("|   `   |");
                            break;
                    }
                    break;
                case 2:
                    switch(faceRow){
                        case 1:
                            printf("|   ^   |");
                            break;
                        case 2:
                            printf("|  / \\  |");
                            break;
                        case 3:
                            printf("|   ^   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
                case 3:
                    switch(faceRow){
                        case 1:
                            printf("|   o   |");
                            break;
                        case 2:
                            printf("|  o o  |");
                            break;
                        case 3:
                            printf("|   ^   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
                case 4:
                    switch(faceRow){
                        case 1:
                            printf("| ( v ) |");
                            break;
                        case 2:
                            printf("|  \\ /  |");
                            break;
                        case 3:
                            printf("|   V   |");
                            break;
                        case 4:
                            printf("|       |");
                            break;
                    }
                    break;
            }
            j++;
            switch(j){
                case 2:
                    suitRep = suitRep2;
                    break;
                case 3:
                    suitRep = suitRep3;
                    break;
                case 4:
                    suitRep = suitRep4;
                    break;
                case 5:
                    suitRep = suitRep5;
                    break;
                case 6:
                    suitRep = suitRep6;
                    break;
            }
            printf(" ");
            numberCards2--;
        }
        numberCards2 = numberCards1;
        while(5 - numberCards2 > 0){
            printf("         ");
            printf("  ");
            numberCards2++;
        }
        numberCards2 = numberCards1;
        suitRep = suitRep1;
        j = 1;
        printf("\n");
    }
    
    //another portion of the chips
    switch(moneyState){
        case 0:
			printf("          ");
			break;
		case 1:
            printf("  '-..-'  ");
			break;
        case 2:
            printf("  '-..-'  ");
			break;
        case 3:
			printf(" `'-..-'  ");
			break;
	}
    printf("      ");
    
    
    //display value of the cards, bottom portion
    while(numberCards2 > 0){
        switch(value){
            case 0:
                printf("|{}{}{}{|");
                break;
            case 1:
                printf("|      A|");
                break;
            case 2:
                printf("|      2|");
                break;
            case 3:
                printf("|      3|");
                break;
            case 4:
                printf("|      4|");
                break;
            case 5:
                printf("|      5|");
                break;
            case 6:
                printf("|      6|");
                break;
            case 7:
                printf("|      7|");
                break;
            case 8:
                printf("|      8|");
                break;
            case 9:
                printf("|      9|");
                break;
            case 10:
                switch(typeRep){
                    case 1:
                        printf("|      J|");
                        break;
                    case 2:
                        printf("|      Q|");
                        break;
                    case 3:
                        printf("|      K|");
                        break;
                    default:
                        printf("|     10|");
                        break;
                }
        }
        j++;
        switch(j){
            case 2:
                value = value2;
                typeRep = typeRep2;
                break;
            case 3:
                value = value3;
                typeRep = typeRep3;
                break;
            case 4:
                value = value4;
                typeRep = typeRep4;
                break;
            case 5:
                value = value5;
                typeRep = typeRep5;
                break;
            case 6:
                value = value6;
                typeRep = typeRep6;
                break;
        }
        printf(" ");
        numberCards2--;
    }
    
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    value = value1;
    typeRep = typeRep1;
    j = 1;
    printf("\n");
    
    
    //only show label 1st time
    if(gamesPlayed == 0){
        printf("Your Chips ");
    } else {
        printf("           ");
    }
    
    
    printf("     ");
    
    
    //display bottoms of cards based on number of cards present
    while(numberCards2 > 0){
        printf(" -------");
        printf("  ");
        numberCards2--;
    }
    numberCards2 = numberCards1;
    while(5 - numberCards2 > 0){
        printf("         ");
        printf("  ");
        numberCards2++;
    }
    numberCards2 = numberCards1;
    
    printf("\n");
    ;
    
    //divide input portion
    printf("_______________________________________________________________________________");
    
    
    printf("\n");
    
}



void RefreshDisplay(card *dealHead, card *playHead, card *deckHead, int money, int bet, int win, int gamesPlayed, int pWins, int flipCard){
    
    //bring all three parts of screen up at same time
    DisplayDealer(dealHead, deckHead, gamesPlayed, flipCard);
    DisplayBet(bet, win, gamesPlayed, pWins);
    DisplayPlayer(playHead, money, gamesPlayed);
}



void DisplayInfo(int games, int draws, int pwins, int dwins, int twentyones, int aceTwentyones, char print){
    
    FILE *outp;
    
    //print statistics to txt only if user indicated
    if(print == 'y' || print =='Y'){
    outp = fopen("statistics.txt", "w");
    
    fprintf(outp, "\t\t\t%d game(s) played\n\n", games);
    fprintf(outp, "\t\t\tPlayer won %.0f%% of the time.\n\n", (float)pwins / games * 100);
    fprintf(outp, "\t\t\tDealer won %.0f%% of the time.\n\n", (float)dwins / games * 100);
    fprintf(outp, "\t\t\t%.0f%% of games were a draw.\n\n", (float)draws / games * 100);
    fprintf(outp, "\t\t\t%.0f%% of all hands resulted in 21.\n\n", (float)twentyones / games / 2 * 100);
    fprintf(outp, "\t\t\t%.0f%% of dealer hands resulted in 21\n\t\t\twhen ace was the dealer's 1st card.\n\n", (float)aceTwentyones / games * 100);
    }
    printf("\n\n\n\n\n\n");
    
    
    //always print statistics to screen
    printf("\t\t\t%d game(s) played\n\n", games);
    printf("\t\t\tPlayer won %.0f%% of the time.\n\n", (float)pwins / games * 100);
    printf("\t\t\tDealer won %.0f%% of the time.\n\n", (float)dwins / games * 100);
    printf("\t\t\t%.0f%% of games were a draw.\n\n", (float)draws / games * 100);
    printf("\t\t\t%.0f%% of all hands resulted in 21.\n\n", (float)twentyones / games / 2 * 100);
    printf("\t\t\t%.0f%% of dealer hands resulted in 21\n\t\t\twhen ace was the dealer's 1st card.\n\n", (float)aceTwentyones / games * 100);
    printf("\t\t\tTill next time!\n\n");
    
    printf("\n\n\n\n\n");
}