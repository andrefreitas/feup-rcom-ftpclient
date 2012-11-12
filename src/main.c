
#include "ftp.h"
int main(int argc, char *argv[]){

	if(argc==2) download(argv[1]);
	else return -1;
	return 0;
}
