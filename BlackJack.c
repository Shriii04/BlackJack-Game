#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int money=1000,bet,i;
int card[52];
char user[10]="yes";
int sum1=0,sum2=0;

void win(){ // To calculate the winning amount
	money=money+bet;
	printf("Current amount: %d\n\n",money);
}

void lose(){// To calculate amount left after loosing.
	money=money-bet;
	printf("Current amount: %d\n\n",money);
}

void my_cards(int n){
	sum1=0;
	printf("\tMy cards: ");
	for (i=0;i<n;i++){
		printf("%d   ",card[i]);
		sum1=sum1+card[i];
	}
	printf("sum=%d\n",sum1);
}

void opponent_cards(int m){
	sum2=0;
	printf("\nOpponent's cards: ");
	for (i=0;i<m;i++){
		printf("%d   ",card[10+i]);
		sum2=sum2+card[10+i];
	}
	printf("sum=%d\n\n",sum2);
}

void board(int m,int n){ //For displaying opponent and hour cards
	opponent_cards(m);
	my_cards(n);
}

void hit_stand(char* choice){
	while (strcasecmp(choice,"stand") && strcasecmp(choice,"hit")){
    	printf("Error! Input can only be hit or stand.");
    	printf("\nHit or Stand: ");
    	scanf("%s",choice);
	}
}

void check(int sum1, int sum2){// To check whether the sum is greater than 21.
	if (sum1>21 && sum2>21){
		printf("\nBoth got busted-_-\n");
		printf("Current amount: %d\n",money);
	}
	else if (sum1==21 && sum2!=21){
    	printf("\nBLACKJACK! You won:)\n");
    	win();
	}
	else if (sum2==21 && sum1!=21){
    	printf("\nBLACKJACK! Opponent won:(\n");
    	lose();
	}
	else if (sum1==21 && sum2==21){
    	printf("\nIt's a tie-_-\n");
    	printf("Current amount: %d\n",money);
	}
	else if (sum1>21){
		printf("\nYou got busted:(\n");
		lose();
	}
	else if (sum2>21){
    	printf("\nOpponent got busted:)\n");
    	win();
	}
}


int main(){
while (!strcasecmp(user,"yes")){
	int n=2,m=2;
	char choice[10]="none";
	printf("Current amount: %d\n",money);
	printf("How much would you like to bet: ");
	scanf("%d",&bet);
	while (bet>money || bet<0){
		printf("Error! Bet should be between 0 and %d.\n",money);
		printf("How much would you like to bet: ");
		scanf("%d",&bet);
	}
	srand(time(0));
	for(i=0;i<20;i++){
		card[i]=rand()%11+1;
	}

	printf("\nOpponent's cards: ?   %d   sum=%d\n\n",card[11],card[11]);
	printf("\tMy cards: %d   %d   sum=%d\n",card[0],card[1],card[0]+card[1]);
	sum1=card[0]+card[1];
	sum2=card[10]+card[11];

	if (sum1<21 && sum2<21){
    	printf("Hit or Stand: ");
    	scanf("%s",choice);
    	hit_stand(choice);
	}
	else if (sum1>=21 || sum2>=21){
    	board(m,n);
    	check(sum1,sum2);
	}

	while (!strcasecmp(choice,"hit")){
		n+=1;
		sum1=0;
		for (i=0;i<n;i++){
			sum1=sum1+card[i];
		}
		if (sum1<21){
			printf("\nOpponent's cards: ?   %d   sum=%d\n\n",card[11],card[11]);
    		my_cards(n);
    		printf("Hit or Stand: ");
    		scanf("%s",choice);
    		hit_stand(choice);
    	}
    	else if (sum1>21){
    		board(m,n);
    		check(sum1,sum2);
    		break;
		}
		else{
			break;
		}
    }

	if (strcmp(choice,"none")){
		while (sum1<=21 && sum2<=15){
	    	m+=1;
	    	sum2=0;
	    	for (i=0;i<m;i++){
	    		sum2=sum2+card[10+i];
			}
			if (sum2<=15){
				board(m,n);
			}
		}
		if (sum1<=21 && sum2>15){
			board(m,n);
			check(sum1,sum2);
		}
	}

	if (!strcasecmp(choice,"stand") && sum2<21){
    	if (sum1>sum2){
    		printf("\nYou won:)\n");
    		win();
    	}
    	else if (sum1<sum2){
    		printf("\nYou lost:(\n");
    		lose();
		}
    	else{
    		printf("\nIt's a tie-_-\n");
    		printf("Current amount: %d\n",money);
		}
	}

	if (money==0){
		printf("\nBankrupt! You don't have any money left");
		printf("\nYou had a loss of 1000:(");
		printf("\nSorry for playing:((");
		break;
	}

	printf("\nDo you want to play again?(yes/no): ");
	scanf("%s",user);
	while (strcasecmp(user,"yes") && strcasecmp(user,"no")){
		printf("Error! Input can only be yes or no.");
		printf("\nDo you want to play again?(yes/no): ");
		scanf("%s",user);
	}

	if (!strcasecmp(user,"no")){
		if (money>1000){
			printf("\nYou made a profit of %d:)",money-1000);
			printf("\nThanks for playing:))");
		}
		else if (money<1000){
			printf("\nYou had a loss of %d:(",1000-money);
			printf("\nSorry for playing:((");
		}
		else{
			printf("\nYou made no profit or loss-_-");
			printf("\nThanks for playing-__-");
		}
	}
}
return 0;
}