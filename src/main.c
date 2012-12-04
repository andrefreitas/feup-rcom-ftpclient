
#include "ftp.h"
int main(int argc, char *argv[]){

	if(argc==2) {
		int correctSyntax=checkSyntax(argv[1]);
		if(correctSyntax){
			printf("Sintaxe correcta\n");

			char *user,*password,*host,*urlpath,*ip;
			int ret,sock1fd,pasvPort,sock2fd;

			user=ALLOCSTRING;
			password=ALLOCSTRING;
			host=ALLOCSTRING;
			urlpath=ALLOCSTRING;
			ip=ALLOCSTRING;

			ret = parseParams(argv[1],user,password,host,urlpath);
			getIP(host,ip);

			sock1fd=createSocket(ip,FTPPORT);
			if(ret == 0)
				loginUserPass(sock1fd,user,password);
			else if(ret == 1)
				loginUser(sock1fd,user);
			else if(ret == 2)
				loginUserPass(sock1fd,"anonymous","foo");
			pasvPort = enterPassiveMode(sock1fd);
			sock2fd = createSocket(ip,pasvPort);
			download(sock1fd,sock2fd,urlpath);
			close(sock1fd);
			close(sock2fd);
		}
		else printf("Sintaxe errada!\n");

	}
	else return -1;
	return 0;
}
