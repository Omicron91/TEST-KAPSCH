#ifndef NETWORKING_H
#define NETWORKING_H

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int hostLocalServer(int);
int connect2server(char *, int);


#endif  // NETWORKING_H