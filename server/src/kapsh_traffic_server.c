#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>

#include "networking.h"
#include "factorization.h"


#define MAX_CONNECTIONS 10
#define MAX_NUMBER 50000
#define PORT 8080

int8_t connections = 0;
int isRunning;

void print_usage(const char *prog_name)
{
    printf("Usage: %s [--host <host>] [--port <port>]\n", prog_name);
}

void cleanup_and_exit(int);

void *handleClient(void *);
void *processFactorization(int *);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char **argv)
{
    int socketFd, clientAddrLen, *clientSocket;
    struct sockaddr_in clientAddr;

    pthread_t threadId;

    clientAddrLen = sizeof(clientAddr);

    int port = -1;
    /* PARSE CMD ARGS */
    static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"help", 0, 0, '?'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "p:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            case '?':
                print_usage(argv[0]);
                return 1;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (port >= 0) {
        printf("Port selected: %d\n", port);
    } else {
        printf("Port: not specified. Default port 8080 will be used \n");
        port = PORT;
    }

    socketFd = hostLocalServer(port);

    if (socketFd < 0)
    {
        return 1;
    }
    
    isRunning = 1;

    do
    {
        if (connections == MAX_CONNECTIONS)
        {
            printf("The maximum number of connections has been reached\n");
            continue;
        }

        printf("Waiting for clients...\n");
        clientSocket = malloc(sizeof(int));
        if (!clientSocket)
        {
            printf("The client socket couldn't be allocated\n");
        }
        *clientSocket = accept(socketFd, (struct sockaddr *)&clientAddr, (socklen_t *)&clientAddrLen);
        if (*clientSocket < 0)
        {
            printf("Socket accept failed\n");
            free(clientSocket);
            return 4;
        }
        else
        {
            if (pthread_create(&threadId, NULL, handleClient, clientSocket) != 0)
            {
                printf("Thread connection create failed\n");
                free(clientSocket);
            }
            else
            {
                printf("New client connection accepted!\n");
                pthread_mutex_lock(&mutex);
                connections++;
                pthread_mutex_unlock(&mutex);
            }
                
        }
    } while (isRunning);

    printf("Program finished!\n");

    return 0;
}


void *handleClient(void *clientSocket)
{
    int _clientSocket = *(int *)clientSocket;
    char message[1024];

    printf("Handling messages...\n");
    do
    {
        memset(message, 0, sizeof(message));

        int responseVal = read(_clientSocket, message, 1024);
        if (responseVal == 0)
        {
            printf("Client disconnected\n");
            break;
        }

        char resultBuffer[1024] = {0};

        if (strlen(message) > 0)
        {
            uint16_t numb = atoi(message);
            if (numb > MAX_NUMBER)
            {
                printf(
                    "The number %d can't be processed. The maximum valid number is %d\n",
                    numb, 
                    MAX_NUMBER
                );
                char *temp = "-1";
                strcat(resultBuffer, temp);
                send(_clientSocket, resultBuffer, strlen(resultBuffer), 0);
                continue;
            }
            int lenFactors = 0;
            uint16_t factors[1024] = { 0 };

            printf("Processing factors of %d\n", numb);
            
            factorize(numb, &lenFactors, factors);

            for(int i = 0; i < lenFactors; ++i)
            {             
                char temp[16];
                // Convert uint16_t to string
                sprintf(temp, "%u ", factors[i]);
                strcat(resultBuffer, temp);
            }
            send(_clientSocket, resultBuffer, strlen(resultBuffer), 0);
            printf("Sent factors: %s\n", resultBuffer);
        }
    } while(1);

    pthread_mutex_lock(&mutex);
    connections--;
    pthread_mutex_unlock(&mutex);
    
    close(_clientSocket);
    free(clientSocket);
    pthread_exit(NULL);
}