/* prog_server.c ~ has the remote procedures that are called by the server stub.
   Remote procedure 1 is bindate_1; returns date and time.
   Remote procedure 2 is uptime_1; returns uptime.
   Remote procedure 3 is available_memory_1; returns available memory.
   Remote procedure 4 is current_users_1; returns the current users.
   rpcgen generated sample templates by using rpcgen -a <inputFile>.
   I used the templates for a guideline.
   Name: Joshua Johnston
   Date: 11/22/2015
 
 */

#include "prog.h"
#include <sys/sysinfo.h>

long *    /* return the binary date and time */
bindate_1_svc(void *argp, struct svc_req *rqstp)
{	
    static long timeval;  
    timeval = time((long *) 0);
    printf("Responding to time request\n");
    return (&timeval);

}

char **   /* return the uptime */
uptime_1_svc(void *argp, struct svc_req *rqstp)
{
        static char * result;
        FILE *pipein_fp;             
	result = (char*)calloc(1048576, sizeof(char));         //allocating memory of type char*
    
	/* Create one way pipe line with call to popen() */ 
	if (( pipein_fp = popen("uptime", "r")) == NULL)       //if popen returns NULL print error message and exit
    {
        printf("ERROR: can't read uptime\n");        
        exit(1);
    }
    fgets(result, 1048576, pipein_fp);     //else read a string 
    pclose(pipein_fp);                // close popen
    printf("Responding to uptime request\n");  
    return (&result);  //return the uptime
}

char **    /* return the available memory */
available_memory_1_svc(void *argp, struct svc_req *rqstp)
{
        static char * result;
        struct sysinfo si;       									//using struct sysinfo from <sys/sysinfo.h>
	long total_mem;
    
	sysinfo (&si);   	
	total_mem = si.totalram;                                    //getting the total memory	
	result = (char*)calloc((total_mem + 1), sizeof(char));     //allocating memory of type char* with a size of the total memory + 1	
	sprintf(result," %ld", si.freeram);                        //converting the type long to a string
	printf("Responding to available memory request\n");
	return (&result);                                          //returning the available memory
}

char **   /* return the current users */
current_users_1_svc(void *argp, struct svc_req *rqstp)
{
    static char * result;	
    FILE *pipein_fp;
    result = (char*)calloc(1048576, sizeof(char));           //allocating memory of type char*
    
	/* Create one way pipe line with call to popen() */
    if (( pipein_fp = popen("who|wc", "r")) == NULL)       //if popen returns NULL print error message and exit
    {
	   printf("ERROR: can't read who|wc\n");
       exit(1);
    }
    fgets(result, 1048576, pipein_fp);                      //else read a string        
	pclose(pipein_fp);                                      //close popen
	printf("Responding to number of current users request\n");  
	return (&result);                                        //return current users
}
