#ifndef libroll_h__
#define libroll_h__


#ifdef _WIN32
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT 
#endif


#include "iroll.h"
#include "proll.h"
#include "stdio.h"

double iRoll(const char* input){
	//printf("using libroll.h\n");
	//const char* rpnExp = iRoll_str(input);	
	return pRoll(iRoll_str(input));
}

#endif