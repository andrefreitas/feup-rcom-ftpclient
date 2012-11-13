#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <regex.h>

#define MAXSIZE 256
#define ALLOCSTRING malloc(sizeof(char)*MAXSIZE)

int parseParams(char *argv,char *user,char *password, char *host, char *urlpath);
int checkSyntax(char *argv);
int download(char *argv);

