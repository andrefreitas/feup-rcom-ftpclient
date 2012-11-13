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

int parseParams(char *argv, char *user, char *password, char *host,
		char *urlpath) {
	char *temp, *temp2;
	int len;

	temp = strchr(argv, '/') + 2;
	temp2 = strchr(temp, ':');

	// If needs authentication
	if (temp2 != 0) {
		temp2--;

		// user
		len = temp2 - temp + 1;
		strncpy(user, temp, len);

		// password
		temp2 += 2;
		temp = strchr(temp2, '@') - 1;
		len = temp - temp2 + 1;
		strncpy(password, temp2, len);

		temp += 2;

		printf("User: %s Password: %s ", user, password);
		if (strlen(password) == 0)
			password = 0;
	}

	// host
	temp2 = strchr(temp, '/') - 1;
	len = temp2 - temp + 1;
	strncpy(host, temp, len);
	if (host[0] == '@')
		host++;

	// urlpath
	temp2 += 2;
	strcpy(urlpath, temp2);

	printf("Host: %s Urlpath: %s\n", host, urlpath);
	return 0;

}

int checkSyntax(char *argv) {
	// re = ftp://(([a-zA-Z0-9.]+:[a-zA-Z0-9]*@)?|@?)([a-zA-Z0-9]+[.])+[a-zA-Z0-9]+/([a-zA-Z0-9]+[/]?)*
	// argv = ftp://user:password@host/urlpath
	// argv = ftp://host/urlpath
	// argv = ftp://@host.com
	// argv = ftp://foo:@host.com

	regex_t regex;
	int totalMatch,matchesBegin;
	size_t nmatch=strlen(argv);
	regmatch_t pmatch[nmatch];

	regcomp(&regex, "ftp://\\(\\([a-zA-Z0-9\\.]\\+:[a-zA-Z0-9]*@\\)\\?\\|@\\?\\)\\([a-zA-Z0-9]\\+[\\.]\\)\\+[a-zA-Z0-9]\\+/\\([a-zA-Z0-9]\\+[/]\\?\\)*", 0);
	regexec(&regex, argv, nmatch, pmatch, 0);

	totalMatch=pmatch[0].rm_eo;
	matchesBegin=pmatch[0].rm_so==0;

	//printf("Total Match: %d SO: \n",totalMatch);
	regfree(&regex);
	return((totalMatch==strlen(argv)) && matchesBegin);


}
