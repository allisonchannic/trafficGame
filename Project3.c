/* ------------------------------------------------
* Traffic
* CS 141 Spring 2014
*
* Allison Channic
* Lab Time: Thurs. 12:00pm
* System: Windows 8, written in Codewriter
*         Compiled With Visual Studio 2013
*
* Lily Lu
* Lab Time: Thurs. 2:00pm
* System: Windows 8, DevC++
* -------------------------------------------------
*
* Traffic Game
* This game represents a "traffic jam" in which one car, the "R" car, must
* get out of the traffic jam. The user must do this by moving all of the
* other cars on the board. User can only move cars in valid, open spaces, 
* represented by the '.' character. Certain cars move left-right while others 
* move up-down. The user must strategically move each car to open a path way 
* for the "R" car to get out, represented when the "R" car is next to the ">"
* character. 
*/
 
//Include necessary C libraries
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
 
 
/* Method to check if the user entered a valid car
 * Car character and game board taken in the method's parameter
 * Checks to see if user entered a letter that is on the board
 * returns 1 if the car appears on the board once
 * returns 0 if the car did not appear on the board
 */
int checkValidCar(char car, char board[])
{
	//Loop counter
	int i;
	//Check to see if the car is on the board
	for(i = 0; i < 64; i++)
	{
		//If the car is on the board and is a character in the alphabet
		//return 1
		if ((car == board[i]) && (isalpha(car)))
			return 1;
	}
	//Return 0 if the car was not found
	return 0;
}


/* Function to check if a car can move in a valid direction
 * Takes the car to be moved, its direction, and the game board array 
 * as parameters.
 * Returns 1 if the user input car can move in user input direction
 * Returns 0 if the user did not input a valid direction command
 * or if the user did not enter a valid direction for the car
 */
int checkValidCarAndDirection(char car, char direction, char board[])
{
	//Loop counter for board
	int i = 0;
	//Search for the first instance of car
	for (i = 0; i < 64; i++)
	{
		if(board[i] == car)
		{
			//Check if the car moves left-right
			if(direction == 'R' || direction == 'L')
			{
				if( board[i] != board[i + 1])
				{	
					printf("ERROR: This car cannot move in this direction\n");
					printf("Please try again.\n");
					return 0;
				}		
				return 1;	
			}
			//Check if the car moves up-down
			else if(direction =='U' || direction =='D')
			{
				if(board[i] != board[i + 8])
				{
					printf("ERROR: This car cannot move in this direction\n");
					printf("Please try again.\n");
					return 0;
				}
				return 1;
			}
			//Check if the user entered a valid direction command
			else
			{
				printf("ERROR: Invalid direction\n");
				printf("Please try again.\n");
				return 0;
			}
		}
	}
	
}//end of checkValidCarAndDirection


/* Method to check if the direction length the user wants to move a car is valid
 * Take the car to be moved, the car's direction, the length the car is to be
 * moved, and the game board as its parameters.
 * Gets the direction the user entered and checks if the array element the user
 * wants to move the car to is valid, represented by a '.'
 * Returns if the direction length is valid or not through a boolean variable
 */
int checkValidDirectionLength(char car, char direction, int directionValue,
                                                          char board[])
{
	//Loop counter for the array
	int i = 0;
	//Loop counter for the direction length
	int j = 0;
	
	//Switch statement to go through all possible direction values
	switch(direction)
	{
		//User wants to move a car left
		case 'L':
			//Go through the game board array
			for(i=0; i<64; i++)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Check all array elements up to where the user wants to
					//move the car
					for(j=1; j<=directionValue; j++)
					{
						//If the position is valid, direction length is valid
						if(board[i-j] != '.')
							return 0;
					}
					break;
				}
			}
			return 1;
			break;
			
		//User wants to move a car right	
		case 'R':
			//Go through the game board array
			for(i=63; i>=0; i--)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Check all array elements up to where the user wants to
					//move the car
					for(j=1; j<=directionValue; j++)
					{
						//If the position is valid, direction length is valid
						if(board[i+j] !='.')
							return 0;
					}
					break;
				}
			}
			return 1;
			break;
		
		//User wants to move a car up	
		case 'U':
			//Go through the game board array
			for(i=0; i<64; i++)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Check all array elements up to where the user wants to
					//move the car
					for(j=1; j<=directionValue; j++)
					{
						//If the position is valid, direction length is valid
						if(board[i-(8*j)] != '.')
						{
							return 0;
						}
					}
					break;
				}
			}
			return 1;
			break;
		
		//User wants to move a car down	
		case 'D':
			//Go through the game board array
			for(i=63; i>=0; i--)
			{
				//Get the position of the car
				if(board[i] == car)
				{
					//Check all array elements up to where the user wants to
					//move the car
					for(j=1; j <= directionValue; j++)
					{
						//If the position is valid, direction length is valid
						if(board[i+(8*j)] !='.')
							return 0;
					}
					break;
				}
			}
			return 1;
			break;
			
		//If the user did not enter a valid direction, directionlength is
		//automatically invalid
		default: return 0; break;
	}
}//end of checkValidDirectionLength


/* Function to display the game board
 * Takes the game board array as its parameter
 * Prints the array into 8 rows of 8 elements
 * Adds spaces after elements that aren't the end of rows
 */
void displayBoard(char gameBoard[])
{
	//Loop counter
	int i;
	//Go through the array
    for(i = 0; i < 64; i++)
    {
		//Print a new line after every 8 elements
    	if(i % 8 == 0)
        	printf("\n");
		//If an element is not at the end of a row, add a space after it	
        else
           	printf(" ");
 		//Print the new game board
        printf("%c", gameBoard[i]);
    }
}


/* Function to update the game board after the user moves a car
 * Takes the car to be moved, its direction, the direction value, and the
 * array the car moves in as its parameters
 * First checks the validity of the car, direction and direction value
 * If all these are valid, moves the car to the specified positions in the
 * array and adds periods to where the car element used to be
 * Prints the modified array using the displayBoard method
 */
void updateGameBoard(char car, char direction, int directionValue, char board[])
{
	//Temporary char variable to switch board positions
	char temp;
	//Loop counter for the array
	int i = 0;
	//loop counter for the directionLength
	int j = 0;
	
	//Switch statement to go through all possible direction values
	switch(direction)
	{
		//User wants to move a car left
		case 'L':
			//Go through game board
			for(i=0; i<64; i++)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Go through the array elements up to where the user wants
					//to move the car
					for(j=1; j<=directionValue; j++)
					{
						//Check if the position is valid
						if((board[i-j] == '.') && (directionValue < 5))
						{
							//Switch the car character and the '.' character
							temp = board[i];
							board[i] = board [i-j];
							board[i-j] = temp;
						}
					}
				}
			}
			break;
			
		//User wants to move a car right	
		case 'R':
			//Go through the game board
			for(i=63; i>=0; i--)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Go through the array elements up to where the user wants
					//to move the car
					for(j=1; j<=directionValue; j++)
					{
						//Check if the position is valid
						if((board[i+j] == '.') && (directionValue < 5))
						{
							//Switch the car character and the '.' character
							temp = board[i];
							board[i] = board [i+j];
							board[i+j] = temp;
						}
					}
				}
			}
			break;
		
		//User wants to move a car up
		case 'U':
			//Go through the game board
			for(i=0; i<64; i++)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Go through the array elements up to where the user wants
					//to move the car
					for(j=1; j<=directionValue; j++)
					{
						//Check if the position is valid
						if((board[i-(8*j)] == '.') && (directionValue < 5))
						{
							//Switch the car character and the '.' character
							temp = board[i];
							board[i] = board [i-(8*j)];
							board[i-(8*j)] = temp;
						}
					}
				}
			}
			break;
		
		//User wants to move a car down
		case 'D':
			//Go through the game board
			for(i=63; i>=0; i--)
			{
				//Get the position of the car
				if(board[i]==car)
				{
					//Go through the array elements up to where the user wants
					//to move the car
					for(j=1; j<=directionValue; j++)
					{
						//Switch the car character and the '.' character
						if((board[i+(8*j)] == '.') && (directionValue < 5))
						{
							temp = board[i];
							board[i] = board [i+(8*j)];
							board[i+(8*j)] = temp;
						}
					}
				}
			}
			break;
		
		//If the user did not enter a valid direction, the loop breaks
		default: break;
	}

}//end updateGameBoard method

 
/* Function to see if the user has won
 * Takes the game board array as its parameter
 * User wins when the 'R' car is touching the '>' character
 * Goes through the array to see if these two characters are next to each other
 * Returns if the user has won or not through a boolean variable where 0 is
 * false and 1 is true
 */
int checkWin(char board[])
{
	//Declare boolean variable to see if the user has won
	//Value starts at 0, or false
	int hasWon = 0;

	//Loop to go through the array to see is the user has won
	//User has won if the 'R' car is touching the '>' character
	int i;
    for (i = 0; i < 64; i++)
    {
  		//If the 'R' car is touching the '>' character
		//The user has won
		if ((board[i] == 'R') && (board[i+1] == '>'))
			hasWon = 1;
    }
	
	//Return if the user has won or not
	return hasWon;
}

 
//Main method
int main()
{
    //Prints project header with name, lab time, and project name
    printf("\nAllison Channic\n");
    printf("Lab: Thursday 12:00pm\n\n");
    printf("Lily Lu\n");
    printf("Lab: Thursday 2:00pm\n\n");
    printf("Program #3: Traffic\n\n\n");

    //Print game instructions
    printf("Welcome to the traffic game!\n\n");
    printf("Move the vehicles so that the Red car (RR) can\n");
    printf("exit the board to the right. Each move should be\n");
    printf("of the form: CDN where C is the vehicle to be\n");
    printf("moved, D is the direction (u for up, d for down,\n");
    printf("l for left or r for right), and N is the number of\n");
    printf("squares to move it. For example GR2 means move the\n");
    printf("G vehicle to the right 2 squares. Lower-case input\n");
    printf("such as gr2 is also accepted. Enter x to exit\n");
    printf("the program.\n\n");

    //Initialize file to be read for the game board and put it into an array
    FILE* gameBoardText;
    char board[64];        
    int i = 0;
    char gameBoard[] = "board.txt";

    //Associate the actual file name with file pointer and try to open it
    gameBoardText = fopen(gameBoard, "r");

    //Check if the file is null
    if(gameBoardText == NULL)
    {
    	printf("Attempt to open file %s failed.  Exiting ... \n", gameBoard);
        exit(-1);      
    }
 
    //Read from the file into the board.
    while(fscanf(gameBoardText, " %c", &board[i]) != EOF)
    	i++;

    //Close file
    fclose(gameBoardText);

	//Declare variables for user input
	char userCar;
	char userDirection;
	int userDistance;

	/* do-while loop to go through main gameplay
	 * Gets user input for car, direction, and direction value
	 * First checks if these values are valid and if not, goes to the beginning
	 * of the loop so the user can try again
	 * If user input is valid, calls the method updateGameBoardMethod with
	 * user input as parameters and displays the new game board to reflect the
	 * user's move
	 * After user has moved, checks to see if the user has won by calling the
	 * checkWin method with the new game board as the parameter
	 * Process repeats until the user has won
	 */
	 
	do
	{
		//Display the board
		displayBoard(board);
		printf("\n\n");
		
		//Prompt the user for car, direction, and direction value
		printf("Your move -> ");
		//Get car to be moved
		scanf(" %c", &userCar);
		//make userCar to upper case to make case input irrevelant
		userCar = toupper(userCar);
		
		//If user has typed in'x', exit the program
		if( userCar == 'X')
		{
			printf("Exiting program...");
			return 0;
			break;
		}
		//Get direction and distance of car to be moved
		scanf(" %c %d", &userDirection, &userDistance);
		printf("\n\n");
		
		//Make userDirection upper case to
		//make case of the character the user input irrevelant 
		userDirection = toupper(userDirection);
		
		//Check to see if the user entered a valid car
		//If not, return to beginning of the loop
		if (checkValidCar(userCar, board) == 0)
		{
			printf("ERROR: You have entered an invalid car. ");
			printf("Please try again.\n\n");
			continue;
		}

		//Check to see if the user entered a valid direction
		//If not, return to beginning of the loop
		if (checkValidCarAndDirection(userCar, userDirection, board) == 0)
			continue;

		//Check to see if the user entered a valid direction value
		//for the car based on its position in the array
		//If not, return to beginning of the loop
		if (checkValidDirectionLength(userCar,
									userDirection, userDistance, board) == 0)
		{
			printf("ERROR: Car cannot move here. Please try again.\n");
			continue;
		}

		//Update the game board to reflect user's move
		for(i=0; i< userDistance; i++ )
			updateGameBoard(userCar, userDirection, userDistance, board);
			
		//Check to see if the user has won the game
		//If the user has won, tell the user he/she has won
		//and exit the program
		if (checkWin(board) == 1)
		{
			displayBoard(board);
			printf("\nCongratulations! You got the red car out and won ");
			printf("the game! \nNow exiting.\n");
			break;
		}
		
	}while(checkWin(board) != 1); //Exit program if user has won
		
}//End main method