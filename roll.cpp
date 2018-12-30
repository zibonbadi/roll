#include <iostream>
#include <cstring>
#include "libroll/libroll.h"

int main(int argc, char* argv[]){
	
	//Programm-Flags
	int f_mode = 0;
	bool f_verbose = false;
	
	//Input-String
	char* argString = NULL;
	
	for(int i=1;i<argc;i++){
		//printf("%s;%i,%i\n",argv[i],f_mode,f_verbose);
		
		for(int c=1;(argv[i][c]!='\0' && argv[i][0]=='-');c++){
			//printf("flag: %c\n",argv[i][c]);
			switch(argv[i][c]){
				case '?':{}
				case 'h':{	f_mode = 3;	break;}
				case 'i':{	f_mode = 0;	break;}
				case 'p':{	f_mode = 1;	break;}
				case 't':{	f_mode = 2;	break;}
				case 'v':{	f_verbose = true;	break;}
				default:{	printf("Unknown flag '-%c' ignored.\n",argv[i][c]);	break;}
			}	
		}
		
		//Infix-Modus
		if(	argv[i][0]!='-'){	argString = argv[i];	}
		
	}
	
	//Notausgang
	if(argString == NULL && f_mode != 3){	std::cout << "No expression recieved :(\nType \"roll -h\" for help." << std::endl;	return 0;	}
	
	//Verbose
	//printf("%i,%i\n",f_mode,f_verbose);
	if(!f_verbose){	std::cout.setstate( std::ios_base::badbit );	}
	
	char* rVal = (char*) calloc(1,sizeof(char));
	
	switch( f_mode ){
		case 0:{	sprintf(rVal,"%f",iRoll(argString) );	break;	}
		case 1:{	sprintf(rVal,"%f",pRoll(argString) );	break;	}
		case 2:{	sprintf(rVal,"%s",iRoll_str(argString) );	break;	}
		case 3:{	std::cout.clear();
				std::cout 	<< "Roll: A calculator for shell wizards.\n"
						<< "written by Zibon Badi ( v.0.7 )\n\n"
						<< "-i: Infix mode (default)\n"
						<< "-p: Reverse polish notation mode\n"
						<< "-t: Translate Infix -> RPN\n"
						<< "-h or -?: This help\n"
						<< "-v: Verbose output\n"
						<< std::endl;
						break;
			}
		default:{	std::cout << "Invalid flags detected! Type \"roll -h / -?\"" << std::endl;	break;	}
	}
	
	
	std::cout.clear();
	
	std::cout << rVal << std::endl;
	free(rVal);
	
	return 0;
}
