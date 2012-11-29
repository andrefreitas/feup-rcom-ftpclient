
#include "ftp.h"
int main(int argc, char *argv[]){

	if(argc==2) {
		int correctSyntax=checkSyntax(argv[1]);
		if(correctSyntax){
			printf("Sintaxe correcta\n");

			char *user,*password,*host,*urlpath,*ip,*pasvPort;
			int ret,sockfd;

			user=ALLOCSTRING;
			password=ALLOCSTRING;
			host=ALLOCSTRING;
			urlpath=ALLOCSTRING;
			ip=ALLOCSTRING;
			pasvPort=ALLOCSTRING;

			ret = parseParams(argv[1],user,password,host,urlpath);
			printf("Ret: %d\n",ret);
			getIP(host,ip);
			sockfd=createSocket(ip);
			if(ret == 0)
				loginUserPass(sockfd,user,password);
			else if(ret == 1)
				loginUser(sockfd,user);
			enterPassiveMode(sockfd,pasvPort);
		}
		else printf("Sintaxe errada!\n");

	}
	else return -1;
	return 0;
}
