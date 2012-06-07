#include "error_handle.h"

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char* argv[])
{
  int socketfd;
  int portno;
  int n;

  const int buffer_len = 256;
  char buffer[buffer_len];

  struct sockaddr_in serv_addr;
  struct hostent* server;

  if(argc < 3)
    print_error("usage: <ip_address> <port number>");

  portno = atoi(argv[2]);

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if(socketfd < 0){
    PrintSocketError(socketfd);
    print_error("Could not create a socket");
  }

  server = gethostbyname(argv[1]);

  if(server == NULL)
    print_error("could not resolve host name");

  //initialize the values of the struct
  bzero(&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;

  //serv_addr.sin_addr.s_addr = INADDR_ANY;
  bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);

  serv_addr.sin_port = htons(portno);

  if(connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    print_error("could not connect to the server");

  printf("Please enter the message:");
/*
  clilen = sizeof(cli_addr);

  newsocketfd = accept(socketfd, &cli_addr, clilen);

  if(newsocketfd < 0)
    perror("error while listening to the client");
*/

  bzero(buffer, buffer_len);
  fgets(buffer, buffer_len, stdin);

  n = write(socketfd, buffer, strlen(buffer));

  if(n<0)
    print_error("error while writing to the server");

  printf("%s", buffer);


  bzero(buffer, buffer_len);
  n = read(socketfd, buffer, buffer_len -1);

  if(n<0)
    print_error("error while reading from the server");

  return 0;
}
