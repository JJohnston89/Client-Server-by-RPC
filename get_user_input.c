/* get_user_input() prompts the user for input.
   Then it validates the user input, if it is invalid it will print an error message, display the menu, and return -1.
   If the input is valid then it will simply return the value.   
   Name: Joshua Johnston
   Date: 11/18/2015
  */
#include "protot.h"

int get_user_input()
{
	int option;
	printf("Enter an option (1-5): \n");   //prompting the user for input
	scanf("%d", &option);
	
	if(option < 1 || option > 5){          //validating the user input
		printf("ERROR: invalid option only 1-5 is accepted\n\n");   //printing error message
		                                       
		return -1;                                                  //returning -1 for error
		}
		
	return option;   //returning user input
}
	
