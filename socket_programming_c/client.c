// mail client , the client sends a message to server or reads a message from the server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // for sock()
#include <string.h>     // for using memset
#include <arpa/inet.h>  // for inet_addr()
#include <unistd.h>     // for using write() function

int main(int argc,char *argv[])
{
  int sock=0;
  char data_received[1024],data_send[1024],username[50],recipient[50],answer;

  struct sockaddr_in ServerIp;
  
  if( (sock = socket(AF_INET, SOCK_STREAM ,0 )) == -1 ) // create socket
    printf(" socket creation failed ");
  
  ServerIp.sin_family = AF_INET;
  ServerIp.sin_port = htons(atoi(argv[2])); 
  ServerIp.sin_addr . s_addr = inet_addr(argv[1]); 
   
  // requesting connection and connecting to socket
  if( (connect( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp) )) == -1 ){
    printf("connection to the socket failed ");
    exit(0);
  }
  else
    printf(" connected to socket \n");

  printf("Enter a username:\n");
  fgets(username,sizeof(username),stdin);

  printf("press 'w' to Write a message or 'r' to Read a message\n");
  do
  {
    answer = getchar();
  }while( (answer!='w') && (answer !='r') );
  while ((getchar()) != '\n'); // clear input buffer

  if(answer == 'w') // WRITE
  {
    printf("enter recipient username: ");
    fgets(recipient,sizeof(recipient),stdin);

    printf(" Enter a message >> ");
    fgets(data_send, sizeof(data_send), stdin ); 

    // remove enter character from strings
    username[strlen(username)-1]='\0'; 
    recipient[strlen(recipient)-1]='\0'; 
    
    // merge username,recipient,message and append strings to achieve this format: username|recipient|message
    strcat(username,"|");
    strcat(username,recipient);
    strcat(username,"|");
    strcat(username,data_send);
    strcpy(data_send,username);

    write( sock, data_send, sizeof(data_send) ); // write message to socket
  }
  else // READ
  {
    username[strlen(username)-1]='\0'; 
    write( sock, username, sizeof(username) ); // send client's username to the server

    if( recv(sock, data_received, 1024, 0 ) != 0 ) // receive message from socket
    {
      printf("\nInbox:\n--------\n%s---------\n",data_received);
    }
  }

  return 0;
}
