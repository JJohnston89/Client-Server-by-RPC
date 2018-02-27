# Client-Server-by-RPC
This is a class project from Computer Networks and Distributed Processing.
This project is written in C using RPC.

This client-server programming project is an iterative TCP based network administration tool. 
The server provides current system status as requested from the client. 
The client can request from the server such information as the system time, the uptime, the memory use, netstat, current users, 
and the running processes. 
The client program displays a text menu for the user. The user makes requests by selecting a menu option. 

The user will enter the server hostname as a command line argument when the client program is invoked. 
If there is no command line argument then the program will print an error message and exit. 
The client program then enters a loop until told to quit where it will:

•	Display a menu 
•	Prompt the user for a command
•	Test user input for command validity. If user command is invalid, inform the user and redisplay the menu.
•	Send that command request to the server on the host
•	Get response back from server
•	Display response for user

The menu will provide the following choices to the user:
1.	Host current Date and Time
2.	Host uptime
3.	Host memory use
4.	Host Netstat
5.	Host current users
6.	Host running processes
7.	Quit

The server will print out diagnostic messages about what it is doing (e.g., “accepting a new connection”, etc.)

