#include <iostream>
#include <cstring>
#include "libroll.h"

int main(int argc, char* argv[]){
	
	//Programm-Flags
	int f_mode = 0;
	bool f_verbose = false;
	
	//Input-String
	char* argString = NULL;
	
	for(int i=1;i<argc;i++){
		//printf("%s;%i,%i\n",argv[i],f_mode,f_verbose);
		
		//Infix-Modus
		if(strcmp(argv[i],"-i")==0){	f_mode = 0;
		//RPN-Modus
		}else if(strcmp(argv[i],"-p")==0){	f_mode = 1;
		//Translate-Modus
		}else if(strcmp(argv[i],"-t")==0){	f_mode = 2;
		//Help-Modus
		}else if( strcmp(argv[i],"-?")==0 || strcmp(argv[i],"-h")==0 ){	f_mode = 3;
		//Verbose
		}else if(strcmp(argv[i],"-v")==0){	f_verbose = true;
		//Fetch String
		}else{	argString = argv[i];	}
	}
	//printf("%i,%i\n",f_mode,f_verbose);
		
	
	switch( f_mode ){
		case 0:{	std::cout << iRoll(argString) << std::endl;	break;	}
		case 1:{	std::cout << pRoll(argString) << std::endl;	break;	}
		case 2:{	std::cout << iRoll_str(argString) << std::endl;	break;	}
		case 3:{	std::cout 	<< "Roll: A calculator for shell wizards.\n\n"
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
	
	return 0;
}