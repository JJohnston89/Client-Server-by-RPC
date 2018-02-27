/*  main.c is the client side program. The program displays a menu with options: 1) time, 2) uptime, 3) available memory, 4) current users
    and 5) exit. The user is prompt for an option 1-5. Then the users input value is checked to make sure it is not less then 1 or greater then 5.
    If it is out of range then an error message is printed and the menu is displayed again. If it is valid then it will go through a switch and send a 
    request to the server by RPC. If the response from the server is NULL then an error message is printed and the program will exit. If the response
    from the server is not NULL then it will be printed to the screen. The program continues until the user says exit (option 5).
    Name: Joshua Johnston
    Date: 11/18/2015
*/
#include <stdio.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <time.h>
#include "prog.h"
#include "protot.h"

int main(int argc, char *argv[]) 
{
  CLIENT *cl;
  char *server;
  long  *lres;
  char **uptime_results;
  char **memory_results;
  char **users_results;
  int choice;
  
  
  if (argc != 2)                                           //checking to see if the user enter a host name
  { 	                                                   //if there is no host name then print error message and exit
	fprintf(stderr, "ERROR: No Host Name!\n");
	fprintf(stderr, "Program will now exit...\n");
        exit(1);
  }
  server = argv[1];
  /* create client handle */
  if ((cl = clnt_create(server, PROG, DATEVERS, "TCP")) == NULL) 
  {
    /* couldn't establish connection with server */
    printf("can't establish connection with host %s\n", server);
    exit(2);
  }
  
  do{                                     //started the loop
		display_menu();                   //display menu
		choice = get_user_input();        //get a int value from the get_user_input()
		
		if(choice == -1)                 //if it is -1 then it is not valid
		{	
			continue;                    //go to the top of the loop
		}
		else                             //else it is valid 
		{
			switch(choice)
			{
				case 1: 
						printf("Requesting system time\n");
						/* first call the remote procedure bindate() */
						if (( lres = bindate_1(NULL, cl)) == NULL)              //if bindate_1 is NULL print error message and exit
						{
							printf(" remote procedure bindate() failure\n");
							exit(2);
						}
						printf("time on host %s = %s\n", server, ctime(lres));   //else it is not NULL, so print value
                        break;
				
				case 2:
						printf("Requesting system uptime\n");
				                /* second call the remote procedure uptime() */
						if ((uptime_results = uptime_1(NULL, cl)) == NULL)       //if uptime_1 is NULL print error message and exit
						{
							printf(" remote procedure uptime() failure\n");
							exit(2);
						}												
						printf("uptime on host %s = %s\n", server, *uptime_results);   //else it is not NULL, so print value
                        break;
						
				case 3:
						printf("Requesting system available memory\n");
						/* third call the remote procedure available_memory() */
						if ((memory_results = available_memory_1(NULL, cl)) == NULL)    //if available_memory_1 is NULL print error message and exit
						{
							printf(" remote procedure avilable_memory() failure\n");
							exit(2);
						}
						printf("Free memory on host %s = %s\n", server, *memory_results);   //else it is not NULL, so print value
                        break;
						
				case 4:
						printf("Requesting system number of current users\n"); 
						/* fourth call the remote procedure current_users() */
						if ((users_results = current_users_1(NULL, cl)) == NULL)   //if current_users_1 is NULL print error message and exit
						{
							printf(" remote procedure current_user() failure\n");
							exit(2);
						}						
						printf("Number of current users on host %s = %s\n", server,  *users_results);  //else it is not NULL, so print value						
                        break;
				
			} //end of switch
		} //end of else
	}while(choice != 5); 

  clnt_destroy(cl); /* done with handle */
  printf("Exiting...\n");
  return 0;
} //end of main()
