
#include "ftp.h"
int main(int argc, char *argv[]){

	if(argc==2) {
		int correctSyntax=checkSyntax(argv[1]);
		if(correctSyntax){
			printf("Sintaxe correcta\n");

			char *user,*password,*host,*urlpath,*ip;

			user=ALLOCSTRING;
			password=ALLOCSTRING;
			host=ALLOCSTRING;
			urlpath=ALLOCSTRING;
			ip=ALLOCSTRING;
			printf("Ret: %d\n",parseParams(argv[1],user,password,host,urlpath));
			getIP(host,ip);
			loginUserPass(createSocket(ip),user,password);
		}
		else printf("Sintaxe errada!\n");

	}
	else return -1;
	return 0;
}
