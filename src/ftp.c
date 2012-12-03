#include "ftp.h"

int getIP(char *host, char *ip) {
	struct hostent *h;

	/*
	 struct hostent {
	 char    *h_name;	Official name of the host.
	 char    **h_aliases;	A NULL-terminated array of alternate names for the host.
	 int     h_addrtype;	The type of address being returned; usually AF_INET.
	 int     h_length;	The length of the address in bytes.
	 char    **h_addr_list;	A zero-terminated array of network addresses for the host.
	 Host addresses are in Network Byte Order.
	 };

	 #define h_addr h_addr_list[0]	The first address in h_addr_list.
	 */
	if ((h = gethostbyname(host)) == NULL ) {
		herror("gethostbyname");
		exit(1);
	}

	strcpy(ip, inet_ntoa(*((struct in_addr *) h->h_addr)));

	return 0;
}

int loginUser(int sockfd, char *user) {
	char *buf = ALLOCSTRING;
	int len = 0;

	strcpy(buf, "user ");
	strcat(buf, user);
	strcat(buf, "\n");
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	len = read(sockfd, buf, MAXSIZE);
	buf[len] = '\0';
	//230 Login successful.
	if (strncmp(buf, LOGSUC, 3) != 0)
		return -1;
	return 0;
}

int loginUserPass(int sockfd, char *user, char *pass) {
	char *buf = ALLOCSTRING;
	int len = 0;

	strcpy(buf, "user ");
	strcat(buf, user);
	strcat(buf, "\n");
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	len = read(sockfd, buf, MAXSIZE);
	buf[len] = '\0';
	//331 Please specify the password.
	if (strncmp(buf, ASKPASS, 3) != 0)
		return -1;
	bzero(buf, sizeof(buf));
	strcpy(buf, "pass ");
	strcat(buf, pass);
	strcat(buf, "\n");
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	len = read(sockfd, buf, MAXSIZE);
	buf[len] = '\0';
	//230 Login successful.
	if (strncmp(buf, LOGSUC, 3) != 0)
		return -1;
	return 0;
}

int enterPassiveMode(int sockfd) {
	char *buf = ALLOCSTRING;
	char *num1 = ALLOCSTRING;
	char *num2 = ALLOCSTRING;
	int n1, n2;

	char *temp, *temp2;
	int len = 0;

	strcpy(buf, "pasv\n");
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	len = read(sockfd, buf, MAXSIZE);
	buf[len] = '\0';
	// 227 Entering Passive Mode (192,168,50,138,71,81).
	if (strncmp(buf, PASV, 3) != 0)
		return -1;
	temp = strchr(buf, '(');
	temp = strchr(temp, ',') + 1;
	temp = strchr(temp, ',') + 1;
	temp = strchr(temp, ',') + 1;
	temp = strchr(temp, ',') + 1;
	temp2 = strchr(temp, ',') - 1;

	len = temp2 - temp + 1;
	strncpy(num1, temp, len);
	num1[len] = '\0';

	temp2 += 2;
	temp = strchr(temp2, ')') - 1;

	len = temp - temp2 + 1;
	strncpy(num2, temp2, len);
	num2[len] = '\0';

	n1 = atoi(num1);
	n2 = atoi(num2);

	return (n1 * 256 + n2);
}

int createSocket(char *host, int port) {
	int sockfd, len;
	struct sockaddr_in server_addr;
	char *buf = ALLOCSTRING;

	/*server address handling*/
	bzero((char*) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(host); /*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port); /*server TCP port must be network byte ordered */

	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))
			< 0) {
		perror("connect()");
		exit(0);
	}

	if (port == FTPPORT) {

		len = read(sockfd, buf, MAXSIZE);
		buf[len] = '\0';

		//220 FTP for Alf/Tom/Crazy/Pinguim
		if (strncmp(buf, CONSUC, 3) != 0)
			return -1;
	}

	return sockfd;
}

int download(int sock1fd,int sock2fd,char *urlpath) {
	char *buf = ALLOCSTRING;
	char *fileName = ALLOCSTRING;
	char *temp = ALLOCSTRING;
	strcpy(fileName,urlpath);
	int len,filefd;

	strcpy(buf,"retr ");
	strcat(buf, urlpath);
	strcat(buf, "\n");
	write(sock1fd, buf, strlen(buf));
	bzero(buf, sizeof(buf));

	len = read(sock1fd,buf,MAXSIZE);
	buf[len] = '\0';

	if(strncmp(buf,"150",3) != 0) return -1;
	bzero(buf, sizeof(buf));

	while((temp=strchr(fileName,'/'))) strcpy(fileName,temp+1);
	filefd = open(fileName,O_RDWR|O_CREAT,0777);

	while((len=read(sock2fd,buf,MAXSIZE))){
		write(filefd,buf,len);
		bzero(buf, sizeof(buf));
	}
	close(filefd);
	return 0;
}

int parseParams(char *argv, char *user, char *password, char *host,
		char *urlpath) {

	// argv = ftp://user:password@host.com/urlpath
	// argv = ftp://host.com/urlpath
	// argv = ftp://@host.com
	// argv = ftp://foo:@host.com

	char *temp, *temp2;
	int len, ret = 0;

	temp = strchr(argv, '/') + 2;
	temp2 = strchr(temp, ':');

	// If needs authentication
	if (temp2 != 0) {
		temp2--;

		// user
		len = temp2 - temp + 1;
		strncpy(user, temp, len);
		user[len] = '\0';

		// password
		temp2 += 2;
		temp = strchr(temp2, '@') - 1;
		len = temp - temp2 + 1;
		strncpy(password, temp2, len);
		password[len] = '\0';

		temp += 2;

		printf("User: %s Password: %s ", user, password);
		if (strlen(password) == 0) {
			ret = 1;
		}
	} else {
		ret = 2;
	}

	// host
	temp2 = strchr(temp, '/') - 1;
	len = temp2 - temp + 1;
	strncpy(host, temp, len);
	host[len] = '\0';
	if (host[0] == '@')
		host++;

	// urlpath
	temp2 += 2;
	strcpy(urlpath, temp2);

	printf("Host: %s Urlpath: %s\n", host, urlpath);
	return ret;

}

int checkSyntax(char *argv) {
	// re = ftp://(([a-zA-Z0-9.]+:[a-zA-Z0-9]*@)?|@?)([a-zA-Z0-9]+[.])+[a-zA-Z0-9]+/([a-zA-Z0-9_-]+[/]?)*[a-zA-Z0-9_-]+([.][a-zA-Z0-9]+)?
	// argv = ftp://user:password@host.com/urlpath
	// argv = ftp://host.com/urlpath
	// argv = ftp://foo:@host.com

	regex_t regex;
	int totalMatch, matchesBegin;
	size_t nmatch = strlen(argv);
	regmatch_t pmatch[nmatch];

	regcomp(&regex,
			"ftp://(([a-zA-Z0-9.]+:[a-zA-Z0-9]*@)?|@?)([a-zA-Z0-9]+[.])+[a-zA-Z0-9]+/([a-zA-Z0-9 _-]+[/]?)*[a-zA-Z0-9 _-]+([.][a-zA-Z0-9]+)?",
			REG_EXTENDED);
	regexec(&regex, argv, nmatch, pmatch, 0);

	totalMatch = pmatch[0].rm_eo;
	matchesBegin = pmatch[0].rm_so == 0;

	//printf("Total Match: %d SO: \n",totalMatch);
	regfree(&regex);
	return ((totalMatch == strlen(argv)) && matchesBegin);

}
