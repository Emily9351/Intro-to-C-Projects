#define ROUNDS 5
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void greeting(); //display welcome message to user
void playRound(int round); //play one round
int pickOne(); //retrieve the user's guess
int computerPick(); //computer makes its pick
int battle(int player1, int player2); //battle rock...paper...scissor
void result(int player1, int player2); //overall winner of round

int main()
{
	greeting(); //display greeting message
	
	//setup random generator
	int seed;
	printf("Before we start, pick a number to determine how random I will be.\n");
	scanf("%d", &seed);
    srand(seed);
	printf("All set now!\n");
	
	
	for(int x = 0; x < ROUNDS; ++x)
	{
		playRound(x + 1);
	}
	
	
	printf("********************************************************\n");
	printf("Thank you for playing!\n");
	return 0;
}

void greeting()
{
	//output the game rules
	printf("Welcome to rock paper scissor game!\nHere are the rules.\nYou and I will get to choose rock, paper, or scissor.\nAfter we made a decision we will reveal it and determine the winner based on these rules.\n");
	printf("Rock beats Scissor!\nPaper beats Rock!\nScissor beats Paper!\nIf we both pick the same option, then it is a tie.\nReady to play?...Here we go!\n");
}


void playRound(int round)
{
	printf("Welcome to a new round %d!\n", round);
	printf("Best out of three...Let's go!\n");
	printf("********************************************************\n");
	
	//declare player wins to start at 0
	int p1wins = 0;
	int p2wins = 0;
	
	//declare player1 and player2
	int player1;
	int player2;
	
	//loop that keeps track of wins until respective player reaches 3. we will learn about conditional loops soon :)
	while(p1wins != 3 && p2wins != 3)
	{
		//running total of each players wins
		printf("Player 1 has won %d time(s).\n", p1wins);
		printf("Player 1 has won %d time(s).\n", p2wins);
		
		//assign the user input to player1
		player1 = pickOne();
		
		//assign the computer to player2
		player2 = computerPick();
		
		//declare the returned value to wins and then run it through an if statement to caluclate who should get the point
		int wins = battle(player1, player2);
	
		if (wins == 0) //0 means there was a tie or an error
		{
			p1wins = p1wins;
			p2wins = p2wins;
		}
		else if (wins == 1) //1 means that player 1 won the battle
		{
			p1wins = p1wins + 1;
			p2wins = p2wins;
		}
		else //player 2 won the battle
		{
			p1wins = p1wins;
			p2wins = p2wins + 1;
		}
	}
		//reassign player1 and player2 to the amount of wins to output after each round
		player1 = p1wins;
		player2 = p2wins;
		
		result(player1, player2);
}

int pickOne()
{
	//declare a variable
	int p1choice;
	
	//collect the users choice
	printf("1--Rock\n2--Paper\n3--Scissor\n");
	printf("Make your selection: ");
	scanf("%d", &p1choice);
	
	//determine if the variable is valid if so return the inputed value if not return 0
	if(p1choice == 1 || p1choice == 2 || p1choice == 3)
	{
		return p1choice;
	}
	else
	{
		return 0;
	}
}

int computerPick()
{
	printf("I'm making my decision now.\n");
	
	//assign computer to the random value between 0-2 and then add one to that number to make it on the 1,2,3 scale
	int computer = (rand() % 3) + 1; 
	
	//determine if it a valid innput
	if(computer == 1 || computer == 2 || computer == 3)
	{
		return computer;
	}
	else
	{
		return 0;
	}
	
}

int battle(int player1, int player2)
{
	//if statements to declare winners
		if (player1 == 1 && player2 == 1)  //player 1 and 2 chose Rock
		{
			printf("Player 1 used Rock and Player 2 used Rock!\nDraw!\n");
			printf("********************************************************\n");
			return 0;
		}
		else if (player1 == 2 && player2 == 2) //Both chose Paper
		{
			printf("Player 1 used Paper and Player 2 used Paper!\nDraw!\n");
			printf("********************************************************\n");
			return 0;
		}
		else if (player1 == 3 && player2 == 3) //Both chose scissors
		{
			printf("Player 1 used Scissors and Player 2 used Scissors\nDraw!\n");
			printf("********************************************************\n");
			return 0;
		}
		else if (player1 == 1 && player2 == 2) //Player1 chose rock and player 2 chose paper
		{
			printf("Player 1 used Rock and Player 2 used Paper!\nPaper beats Rock!\n");
			printf("********************************************************\n");
			return 2;
		}
		else if (player1 == 1 && player2 == 3) //Player 1 chose rock and player chose scissors
		{
			printf("Player 1 used Rock and Player 2 used Scissors!\nRock beats Scissors!\n");
			printf("********************************************************\n");
			return 2;
		}
		else if (player1 == 2 && player2 == 1) //Player 1 chose paper and player chose rock
		{
			printf("Player 1 used Paper and Player 2 used Rock!\nPaper beats Rock!\n");
			printf("********************************************************\n");
			return 1;
		}
		else if (player1 == 2 && player2 == 3) //Player 1 chose paper and player chose scissors
		{
			printf("Player 1 used Paper and Player 2 used Scissors!\nScissors beats Paper!\n");
			printf("********************************************************\n");
			return 2;
		}
		else if (player1 == 3 && player2 == 1) //Player 1 chose scissors and player chose rock
		{
			printf("Player 1 used Scissors and Player 2 used Rock!\nRock beats Scissors!\n");
			printf("********************************************************\n");
			return 2;
		}
		else if (player1 == 3 && player2 == 2) //Player 1 chose scissors and player chose paper
		{
			printf("Player 1 used Scissors and Player 2 used Paper!\nScissors beats Paper!\n");
			printf("********************************************************\n");
			return 1;
		}	
		else //user inputed an invalid choice
		{
			printf("Someone made an invalid choice.\n");
			printf("********************************************************\n");
			return 0;
		}
}

void result(int player1, int player2)
{
	if (player1 == 3) //if the player1 had 3 wins then the user won
	{
		printf("You Won! Ill let you have this one.\n");
	}
	else //player2 won
	{
		printf("I won! Haha better luck next time!\n");
	}
}
