
// server: saves all the messages to each user
// run hostname -i at helios to to find local ip
#include <stdio.h>
#include <sys/socket.h> // for sock()
#include <string.h>     // for using memset
#include <stdlib.h>
#include <arpa/inet.h>  // for inet_addr()
#include <unistd.h>     // for using write() function

int main(int argc,char *argv[])
{
  int sock=0, client_conn=0,i,j,pos,pos2,p=0;
  char username[50],recipient[50],data_received[1024];

  struct sockaddr_in ServerIp; 
  sock = socket(AF_INET, SOCK_STREAM, 0); // socket creation
  memset(&ServerIp,'0',sizeof(ServerIp) );

  ServerIp.sin_family = AF_INET;
  ServerIp.sin_port = htons(atoi(argv[2]));
  ServerIp.sin_addr . s_addr = inet_addr(argv[1]);

  if( bind( sock,(struct sockaddr* )&ServerIp, sizeof(ServerIp)) == -1 ) //bind ip and port with socket
    printf("Socket binding failed\n");
   
  if( listen(sock,1) == -1) // queue limit for incoming connections
    printf("Error\n");
  else  
    printf("Server started at: %s, port: %s\n",argv[1],argv[2]);
 
  // accept client's request
  client_conn = accept( sock, (struct sockaddr*)NULL, NULL); //accept connection request
  printf(" A request from client accepted \n");

  // recv - receive a message from a socket with this form: username|recipient|message
  if( recv(client_conn, data_received, 1024, 0 ) == 0 ) //if nothing is received
  {
    goto end;
  }
  else
  {
    for(i=0;i<strlen(data_received);i++)
    {
      if(data_received[i]=='|') // if '|' is found in the message it means client wants to write
      {
        p++;
        break;
      }
    }

    if(p==0) // client wants to read , if no '|' is found (p==0)
    {
        char buff[255];
        FILE *fptr;

        if( (fptr=fopen(data_received,"r"))==NULL)
        {
          //send message to client: NO MESSAGES FOUND FOR YOU
         strcpy(buff,"no messages found for you\n");
           write( client_conn, buff, sizeof(buff) ); // write to socket
          goto end;
        }
        else
        {
          //send to client the messages inside the txt with his username
          fptr=fopen(data_received,"r");
        
          char m[255];
          while(fgets(buff,255,fptr)!=NULL) // read whole file until end
            strcat(m,buff); // every line

          // send messages to client
          write( client_conn, m, sizeof(m) ); // write to socket

          fclose(fptr);
          goto end;
        }
    }

    printf(" Response Received is : %s\n", data_received );
    for(i=0;i<strlen(data_received);i++)// extract recipient from the message and put the message at a recipient.txt file
    {
      if(data_received[i]=='|') // find the first '|'
      {
        pos = i;
        break;
      }
    }

    for(i=pos+1;i<strlen(data_received);i++) // find the second '|'
    {
      if(data_received[i]=='|')
      {
        pos2 = i;
        break;
      }
    }
    
    i=0;
    for(j=pos+1;j<pos2;j++) // extract recipient from message
    {
      recipient[i] = data_received[j];
      i++;
    }

    FILE *ptr;
    ptr=fopen(recipient,"a"); // append new message to txt
    if(ptr==NULL)
    {
      printf("error!");
      exit(1);
    }
    fprintf(ptr,"%s",data_received);
    fclose(ptr);
  }

  end:
  close( client_conn );
  return 0;
}
