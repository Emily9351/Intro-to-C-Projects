#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX 20
#define STRIKE 6

//declare functions
void maskWord (char starword[MAX], int size1); //mask word with stars to display
int playRound(char starword[MAX], char answer[MAX]); //play a round of hangman
int occurencesInWord(char userguess, char answer[MAX]); //times letter occurs in word
void updateStarWord(char starword[MAX], char answer[MAX], char userguess); //replace respective *
int guessTheWord(char answer[MAX]); //guess the word
void playAgain(int *play); //ask user to play again

int main()
{
	//welcome statement
	printf("Welcome to the Hangman Game!\n");
	printf("************************************************************************\n");
	printf("Here are the rules.\n");
	printf("I will provide you a set of * characters for each round.\n");
	printf("Each * represents a letter in the English Alphabet.\n");
	printf("You must figure out each letter of the missing word.\n");
	printf("For every correct letter guessed, I will reveal its place in the word.\n");
	printf("Each mistake will result in a strike.\n");
	printf("6 strikes will result in a loss that round.\n");
	printf("Are you ready? Here we go!\n");
	
	//declare function
	char starword[MAX];
	
	//open file to be read from
	FILE *file  = fopen("words.txt", "r"); 
	
	//get first word
	fgets(starword, MAX, file);
	
	//declare variables
	int again = 0;
	int *play = &again;
	
	//declare size of word	
	int size1 = strlen(starword);
	
	//declare answer to be safe as the word that was read from file	
	char answer[MAX];
	strcpy(answer, starword);
	
	//call first function
	maskWord(starword, size1);
	
	//call second function
	int winner = playRound(starword, answer);
	
	//if player won the round
	if(winner == 1)
	{
		//say congrats and ask to play again
		printf("Congratulations! You Won! The word was %s\n", answer);
		playAgain(play);
	}
	else
	{
		//you didn't win but play again?
		printf("Sorry you did not win the round. The word was %s\n", answer);
		playAgain(play);
	}
	//reset winner value to zero
	winner = 0;
	
	//keep going well still words in file
	//and if they said yes to play again
	while((fgets(starword, MAX, file)) != EOF && again == 1)
	{
		//reset size to new word and match answer and starword
		int size1 = strlen(starword);
		strcpy(answer, starword);
		
		//recall first function
		maskWord(starword, size1);
		
		//call second function
		winner = playRound(starword, answer);
	
		//if player won print congrats
		if(winner == 1)
		{
			printf("Congratulations! You Won! The word was %s", answer);
			playAgain(play);
		}
		else //player lost
		{
			printf("Sorry you did not win the round. The word was %s", answer);
			playAgain(play);
		}
		winner = 0;
	}
	
	//close file
	fclose(file);
	
	return 0;
}

//function 1
void maskWord (char starword[MAX], int size1)
{		
	//for each value that is an alphabetical character
	//place a star
	for(int i = 0; i < size1; i++)
	{
		while(isalpha(starword[i]))
		{
			starword[i] = '*';
		}
	}
	
	//print starword	
	printf("%s\n", starword);
}

int playRound(char starword[MAX], char answer[MAX])
{
	printf("************************************************************************\n");
	printf("Welcome to the Round!\n");
	
	//declare functions
	char userGuess[26];
	int n = strlen(answer);
	int count = 0;
	int index = 0;
	
	//print guessed values
	for (int a = 0; a < 26; a++)
	{
		userGuess[a] = '\0';
	}
		
	int k = n - 1;
	
	//go down line and count size of word
	while(!isalpha(answer[k]))
	{
		k--;
	}
	
	while(isalpha(answer[k]))
	{
		k--;
		count++;
	}
	
	//declare variables
	char x;
	int strikes = 0;
	char userguess;
	int numCorrect = 0;
	int won = 0;
	int check = 1;
	
	//print size of word
	printf("The size of your word has %d letters.\n", count);
	
	printf("\n");
	
	//print strike count and what letters have been guessed
	printf("You currently have %d strike(s).\n", strikes);
	printf("Letters you have guessed: %s\n", userGuess);
	printf("\n");
	
	//print starword
	printf("%s\n", starword);
		
	//go through entire word
	for(int j = 0; j < count; j++)
	{	
		//while not at 6 strikes
		while (strikes != 6)
		{
			//collect user guess
			printf("Enter your guess: ");
			scanf(" %c", &userguess);
			
			//make sure it hasnt already been guessed
			//if has not add to letters guessed
			for (int b = 0; b < 26; b++)
			{
				
				if (userguess == userGuess[b])
				{
					
					check = 0;
				}
				
			}
			
			if (check == 1)
			{
				userGuess[j] = userguess;
				j++;	
			}
			
			check = 1;
			
			//check if guessed letter appears in word
			int inWord = occurencesInWord(userguess, answer);
		
			//in word
			if(inWord == 1)
			{
				//print that letter is in word
				printf("The letter %c is in the word\n", userguess);
				
				//update the starword to fill in pieces of word
				updateStarWord(starword, answer, userguess);
				
				//check if words match if so return a win
				int win = strcmp(answer, starword);

				if(win == 0)
				{
					return 1;
				}
				
				//count amount letters correct and see if more than 2
				//if more than two ask if they want to guess word
				numCorrect++;
				
				if(numCorrect >= 2)
				{
					printf("%s\n", starword);
					printf("Letters you have guessed: %s\n", userGuess);
					printf("You have made at least 2 consecutive correct guesses. Would you like to guess the word (1 for Yes 0 for no.): ");
					scanf(" %c", &x);
						
					if(x == '1')
					{
						won = guessTheWord(answer);
						//if player was correct return a win
						if(won == 1)
						{
							return 1;
						}
					}
				}
			}
			else //not in word so add a strike
			{
				printf("The letter %c is NOT in the word\n", userguess);
				strikes++;
				numCorrect = 0;
			}
			
			//reprint opening information
			printf("You currently have %d strike(s).\n", strikes);
			printf("Letters you have guessed: %s\n", userGuess);
			printf("\n");
			printf("%s\n", starword);
		}
		
	}
	
	return 0;
		
}

//count how many times in word
int occurencesInWord(char userguess, char answer[MAX])
{
	//declare total length
	int length = strlen(answer);
	int numTimes = 0;
	
	//look which values match and count the amount of times
	for(int l = 0; l < length; l++)
	{
		if(userguess == answer[l])
		{
			numTimes++;
		}
	}
	
	//not in word
	if(numTimes < 1)
	{
		return 0;
	}
	else //in word at least once
	{
		return 1;
	}
}

//update word
void updateStarWord(char starword[MAX], char answer[MAX], char userguess)
{
	//set total length
	int ttlLength = strlen(answer);
	
	//replace characters that have been guessed
	for(int m = 0; m < ttlLength; m++)
	{
		if(userguess == answer[m])
			{
				starword[m] = userguess;
			}
	}
}

//guess the word
int guessTheWord(char answer[MAX])
{
	int length = strlen(answer);
	char word[MAX];
	
	//collect input
	printf("Enter your guess: ");
	scanf("%s", word);
	
	int len = strlen(word);
	int correct;
	
	//see if the words do not match
	for (int i = 0; i < len; i++)
	{
		if (answer[i] != word[i])
		{
			correct = 0;

			return 0;
		}
	}
	
	//if passes words match
	correct = 1;
	return 1;
	
}
void playAgain(int *play)
{
	//ask to play again
	printf("Would you like to play another round?\n");
	printf("1: Yes\n2: No\n");
	printf("Choice: ");
	scanf("%d", play);
}

