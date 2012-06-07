#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

typedef int ErrorType;

void print_error(const char* s)
{
  printf("%s\n",s);
  exit(1);
}


void PrintSocketError(ErrorType err)
{
  char* msg = NULL;
  switch(err){
    case EPROTONOSUPPORT:
      msg = "The protocol or style is not supported by the namespace specified.";
    case EMFILE:
      msg = "The process already has too many file descriptors open.";
    case ENFILE:
      msg = "The system already has too many file descriptors open.";
    case EACCES:
      msg = "The process does not have the privilege to create a socket of the specified style or protocol.";
    case ENOBUFS:
      msg = "The system ran out of internal buffer space.";
    default:
      msg = "Unknown Socket Error";
  }
}

#endif // ERROR_HANDLE_H
