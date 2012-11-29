#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 256
#define ALLOCSTRING malloc(sizeof(char)*MAXSIZE)
#define PORT 21
#define LOGSUC "230"
#define ASKPASS "331"
#define CONSUC "220"


int parseParams(char *argv,char *user,char *password, char *host, char *urlpath);
int checkSyntax(char *argv);
int download(char *argv);
int createSocket(char *host);
void enterPassiveMode(int fd);
int loginUser(int sockfd, char *user);
int loginUserPass(int sockfd, char *user, char *pass);

