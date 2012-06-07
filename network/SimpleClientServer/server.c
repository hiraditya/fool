#include "error_handle.h"

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

typedef int ErrorType;

int main(int argc, char* argv[])
{
  int socketfd;
  int newsocketfd;
  unsigned int clilen;
  int portno;
  int cli_count = 5;

  int n;

  const int buffer_len = 256;
  char buffer[buffer_len];

  struct sockaddr_in serv_addr, cli_addr;

  if(argc < 2)
    print_error("usage: <port number>");

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if(socketfd < 0){
    PrintSocketError(socketfd);
    print_error("Could not create a socket");
  }

  //initialize the values of the struct
  bzero(&serv_addr, sizeof(serv_addr));

  portno = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if(bind(socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    print_error("could not bind socket to the server");

  listen(socketfd, cli_count);

  clilen = sizeof(cli_addr);

  newsocketfd = accept(socketfd, (struct sockaddr *)&cli_addr, &clilen);

  if(newsocketfd < 0)
    print_error("error while listening to the client");

  bzero(buffer, buffer_len);

  n = read(newsocketfd, buffer, buffer_len -1);

  if(n<0)
    print_error("error while reading from the client");

  printf("%s", buffer);

  char* ack = "Got the message";

  n = write(newsocketfd, ack, strlen(ack));

  if(n<0)
    print_error("error while writing to the client");

  return 0;
}
