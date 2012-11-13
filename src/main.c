
#include "ftp.h"
int main(int argc, char *argv[]){

	if(argc==2) {
		int correctSyntax=checkSyntax(argv[1]);
		if(correctSyntax){
			printf("Sintaxe correcta\n");
		}
		else printf("Sintaxe errada!\n");

	}
	else return -1;
	return 0;
}
