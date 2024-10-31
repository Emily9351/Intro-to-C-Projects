#include <stdio.h>

void greeting();                                 // welcome the user to the coffee shop
void order(double *balance);                     // user will make a purchase
void viewAccount(double *balance);               // display current account balance of user
void transaction(double *balance, double price); // transaction with user account
void reload(double *balance);                    // reload your account balance
void displayMenu();                              // display beverage/food options and prices

int main()
{
    greeting(); //call greeting function
	
	//declare variables
    char var;
    int exitProgram = 0;
    double bal = 0.00;
    double *balance = &bal;

	//ask what the user wants to do and take them to that function
    while (exitProgram == 0)
    {
        printf("Please select one of the following options.\n");
        printf("O: Order\n");
        printf("V: View Account Summary\n");
        printf("D: Display Menu\n");
        printf("R: Reload Account\n");
        printf("E: Exit\n");

        printf("Please select what you would like to do.\nOption Selected: ");
        scanf(" %c", &var);

        if (var == 'O' || var == 'o') //O or o
        {
            printf("You selected Order.\n");
            order(balance); //order
        }
        else if (var == 'V' || var == 'v') //V or v
        {
            printf("You selected View Account Summary.\n");
            viewAccount(balance); //view account
        }
        else if (var == 'D' || var == 'd') //D or d
        {
            printf("You selected Display Menu.\n");
            displayMenu(); //display menu
        }
        else if (var == 'R' || var == 'r') //R or r
        {
            printf("You selected Reload Account.\n");
            reload(balance); //reload account
        }
        else if (var == 'E' || var == 'e') //E or e
        {
            printf("Thanks for visiting!\n");
            exitProgram = 1; //end program
        }
    }

    return 0;
}

void greeting()
{
	//output opener
    printf("Welcome to the Knightro's Coffee Shop!\n");
    printf("We serve delicious coffee and snacks!\n");
    printf("Is there anything I can help you with today?\n");
}

void order(double *balance)
{
	//call menu and ask user what the want to order
    displayMenu();
    int option;

    printf("Here are the options!\n");
    printf("What would you like today?\n");

    double price;

    do
    {
    	//collect user input
        printf("Option Selected: ");
        scanf("%d", &option);

		//find what item they want and run the price
        if (option == 1)
        {
            printf("Hot Coffee has been selected. Total cost:$3.53\n");  //output what they bought and cost
            price = 3.53; //update price
            printf("Beginning Transaction.\n"); 
            transaction(balance, price); //call transaction function using new price
        }
        else if (option == 2)
        {
            printf("Iced Coffee has been selected. Total cost:$4.20\n");
            price = 4.20;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 3)
        {
            printf("Hot Latte has been selected. Total cost:$3.13\n");
            price = 3.13;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 4)
        {
            printf("Iced Latte has been selected. Total cost:$4.12\n");
            price = 4.12;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 5)
        {
            printf("Bagel(includes cream cheese) has been selected. Total cost:$3.99\n");
            price = 3.99;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 6)
        {
            printf("Big Scone has been selected. Total cost:$4.99\n");
            price = 4.99;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 7)
        {
            printf("Frozen Coffee has been selected. Total cost:$5.03\n");
            price = 5.03;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else if (option == 8)
        {
            printf("Bottle Water has been selected. Total cost:$1.50\n");
            price = 1.50;
            printf("Beginning Transaction.\n");
            transaction(balance, price);
        }
        else //it was not a menu option
        {
            printf("Invalid option try again\n");
        }
    } while (option <= 0 || option > 8);
}

void viewAccount(double *balance) //output current balance
{
    printf("Here is your current account balance.\nYou have $%.2lf in your account\n", *balance);
}

void transaction(double *balance, double price)
{
	//not enough money 
    while (*balance <= price)
    {
        printf("You do not have enough in your account.\n");
        printf("Please reload your account balance.\n");
        reload(balance); //ask to reload their balance
    }

	//Enough money so run transaction
    printf("Your balance before offical transaction: $%.2lf\n", *balance);
    printf("Billing of $%.2lf to your account.\n", price);

    *balance = *balance - price;
    printf("Transaction was successful!\nYou now have $%.2lf in your account balance.\n", *balance); //output total after transaction
}

void reload(double *balance)
{
    int num;

	//ask and read how much they want to reload
    printf("How much would you like to reload your account?\n");
    printf("1: $1.00\n");
    printf("2: $5.00\n");
    printf("3: $10.00\n");

    printf("Option Selected: ");
    scanf("%d", &num);

	//add amount to account
    if (num == 1)
    {
        *balance = *balance + 1;
    }
    else if (num == 2)
    {
        *balance = *balance + 5;
    }
    else if (num == 3)
    {
        *balance = *balance + 10;
    }
    else //wasnt an option try again
    {
        printf("Invalid input try again.\n");
    }
}

void displayMenu()
{
	//display entire menu
    printf("*****************************************************\n");
    printf("1. Hot Coffee $3.53\n");
    printf("2. Iced Cofee $4.20\n");
    printf("3. Hot Latte $3.13\n");
    printf("4. Iced Latte $4.12\n");
    printf("5. Bagel (includes cream cheese) $3.99\n");
    printf("6. Big Scone $4.99\n");
    printf("7. Frozen Coffee $5.03\n");
    printf("8. Bottle Water $1.50\n");
    printf("*****************************************************\n");
}
