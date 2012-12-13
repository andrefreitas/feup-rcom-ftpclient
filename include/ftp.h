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
#include <fcntl.h>

#define MAXSIZE 1024
#define ALLOCSTRING malloc(sizeof(char)*MAXSIZE)
#define FTPPORT 21
#define LOGSUC "230"
#define ASKPASS "331"
#define CONSUC "220"
#define PASV "227"
#define OPENFILE "150"


int parseParams(char *argv,char *user,char *password, char *host, char *urlpath);
int checkSyntax(char *argv);
int download(int sock1fd,int sock2fd,char *urlpath);
int createSocket(char *host, int port);
int loginUser(int sockfd, char *user);
int loginUserPass(int sockfd, char *user, char *pass);
int getIP(char *host,char *ip);
int enterPassiveMode(int sockfd);


