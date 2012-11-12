#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXSIZE 256
#define ALLOCSTRING (char *) malloc(sizeof(char)*MAXSIZE)

int parseParams(char *argv,char *user,char *password, char *host, char *urlpath);

int download(char *argv);

