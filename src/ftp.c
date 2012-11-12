#include "ftp.h"

int download(char* argv) {
	char *user, *password, *host, *urlpath;
	user = ALLOCSTRING;
	password = ALLOCSTRING;
	host = ALLOCSTRING;
	urlpath = ALLOCSTRING;

	parseParams(argv, user, password, host, urlpath);
	return 0;
}

int parseParams(char *argv, char *user, char *password, char *host, char *url) {
	// ftp://user:password@host/urlpath

	char *temp, *temp2;
	int len;

	temp = strchr(argv, '/') + 2;
	temp2 = strchr(temp, ':') - 1;
	len=temp2-temp+1;

	printf("userlen: %d\n",len);
	return 0;

}
