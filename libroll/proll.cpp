#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <random>

int* roll( int dice, int sides){

	std::random_device rng;

	static int* out = (int*) realloc(out,0);
	out = (int*) calloc(dice,sizeof(int));
	
	if(sides > 0){
		for(int i=0;i<dice;i++){
			std::cout << '\t' << dice << 'd' << sides << " (" << i << ") " ;
			int roll = ( rng()%(sides) )+1;
			out[i] += roll;
			std::cout << "-> " << roll << std::endl;
		}
		
		//printf("exit...");
		
		return out;
	}
	
	return 0;
}


double pRoll(const char* input){


	printf("proll ver. 0.8: written by Zibon Badi.\ninput_expr: \"%s\"\n\n",input);

	char* pch = strtok ((char*)input," ,;\n");
	int codeSize = 0;
	
	//Instruction Token StringArray
	char** instruction = (char**) calloc(1,sizeof(char**));
	//UPN-Code setup
	while (pch != NULL)
	{
	
		//printf(">%d,%s\n",codeSize,pch );
		
		//Extend instruction memory
		instruction = (char**) realloc(instruction, sizeof(char*)*(codeSize+1) );
		//instruction[codeSize+1] = (char*) calloc(1,sizeof(char*));
		
		//printf("<%s,", instruction[0]);
		
		//Append new instruction
		instruction[codeSize] = pch;
		
		//printf("%s[%d:%d]\n",instruction[codeSize],sizeof(instruction),strlen(pch));
		codeSize++;
		
		pch = strtok (NULL, " ,;\n");
  	}

  	double hand = 0;
	double next = 0;

	std::stack<double> NumberStack;
	
	//std::cout << "CodeSize:" << codeSize << std::endl;	
	  	
  	//IP=Instuction Pointer
  	for(int IP=0;(IP<codeSize && IP >= 0);IP++){
  		
  		std::cout << '[' << IP << "]:";
  		
  		hand = (!NumberStack.empty())?NumberStack.top():0;
		if( !NumberStack.empty() ){	NumberStack.pop();	}
		next = (!NumberStack.empty())?NumberStack.top():0;
		if( !NumberStack.empty() ){	NumberStack.pop();	}
		
		
		//Basic arithmetic
		if( strcmp(instruction[IP],"+") == 0 ){
			std::cout << next << '+' << hand << '=' << next+hand << std::endl;
			NumberStack.push(hand+next);
		}else if( strcmp(instruction[IP],"-") == 0){
			std::cout << next << '-' << hand << '=' << next-hand << std::endl;
			NumberStack.push(next-hand);
		}else if( strcmp(instruction[IP],"*") == 0){
			std::cout << next << '*' << hand << '=' << next*hand << std::endl;
			NumberStack.push(hand*next);
		}else if( strcmp(instruction[IP],"/") == 0){
			std::cout << next << '/' << hand << '=' << next/hand << std::endl;
			NumberStack.push(next/hand);
		}else if( strcmp(instruction[IP],"%") == 0){
			std::cout << next << '%' << hand << '=' << (( abs((int)next*(int)hand)+(int)next )%(int)hand) << std::endl;
			NumberStack.push(  ( abs((int)next*(int)hand)+(int)next )%(int)hand);
		}
		
		//Rolling
		else if( *instruction[IP] == 'd'){
			//Würfel AdB
			
			//
			//	Possible flags:
			//		'l' : push least on top
			//		'h' : push highest on top
			//		'-l' : reomve least from sum
			//		'-h' : remove highest from sum
			//		'/' : push roll's average
			//		'+' : push roll's sum as well (if '/')
			//		'!' : explosion roll
			//
			
			if( (int)next != 0 && (int)hand != 0){
			
				char* ptr_rollChar = instruction[IP];
				bool rf_max,rf_min,rf_rmmax,rf_rmmin,rf_avg,rf_avgSum,rf_explosion = false;
				
				//Determine flags
				ptr_rollChar++;
				while( *ptr_rollChar != '\0'){
					//printf("%srollflag: %c\n", ( *(ptr_rollChar-1)=='-')?"negative ":"" ,*ptr_rollChar);
					
					if( *ptr_rollChar == 'l'){
						if( *(ptr_rollChar-1)=='-' ){	rf_rmmin = true;
						}else{	rf_min = true;	}
					}
					if( *ptr_rollChar == 'h'){
						if( *(ptr_rollChar-1)=='-' ){	rf_rmmax = true;
						}else{	rf_max = true;	}
					}
					if( *ptr_rollChar == '!'){	rf_explosion = true;	}
					if( *ptr_rollChar == '/'){	rf_avg = true;	}
					if( *ptr_rollChar == '+'){	rf_avgSum = true;	}
					
					//printf("{%i,%i,%i,%i,%i,%i,%i}\n",rf_max,rf_min,rf_rmmax,rf_rmmin,rf_avg,rf_avgSum,rf_explosion);
					
					
					ptr_rollChar++;
				}
				
				//setting up stuff about the roll
				int *out = NULL;
				int totalsum = 0, sum = 0, xroll_iter = 0,  max = -1, min = ((int)hand)+1;
				
				//(Possible explosion) rolling
				do{
					int i_max = 0, i_min = 0;
					
					sum = 0;
					out = roll((int)next, (int)hand);
					
					//Determine MAX/min-Index
					for(int i=0;i<(int)next;i++){
						i_max = (out[i_max] < out[i])?i:i_max;
						i_min = (out[i_min] > out[i])?i:i_min;
					}
					
					for(int i=0;i<(int)next;i++){	
						if(	( rf_rmmax && (i == i_max) ) ||
							( rf_rmmin && (i == i_min) )
						){
							std::cout << "\tskipping die #" << i << std::endl;
							continue;
						}
						sum += out[i];
					}
					
					std::cout << "\t= " << sum << std::endl;
					
					//printf("%d;%d\n%d;%d\n",out[i_min],out[i_max],i_min,i_max);
					
					min = ( min > out[i_min])?out[i_min]:min;
					max = ( max < out[i_max])?out[i_max]:max;
					totalsum += sum;
					
					xroll_iter++;
					
				}while(rf_explosion && ( sum == ((int)hand * (int)next) ) );
				
				
				//Stack pushing
				if( !(rf_avg && !rf_avgSum) ){
					std::cout << "\tTotal sum =>" << totalsum << std::endl;
					NumberStack.push( totalsum );
				}
				if( rf_min ){
					std::cout << "\tStack<-" << min << std::endl;
					NumberStack.push( min );
				}
				if( rf_max ){
					std::cout << "\tStack<-" << max << std::endl;
					NumberStack.push( max );
				}
				if( rf_avg ){
					std::cout << "\tTotal average =>" << totalsum/( xroll_iter*(int)next ) << std::endl;
					NumberStack.push( totalsum/( xroll_iter*(int)next )  );	
				}
			
			}else{	NumberStack.push( 0 );	}
		}
		
		//Instructions
		else if( strcmp(instruction[IP],"J") == 0){
			NumberStack.push(next);
			std::cout << "JMP addr " << hand << std::endl;
			//-1 fixes a bug. dunno why.
			IP = (int)hand-1;
			
		}else if( strcmp(instruction[IP],"P") == 0){
			NumberStack.push(next);
			std::cout << "Popping " << hand << std::endl;
			
		}else if( strcmp(instruction[IP],"S") == 0){
			NumberStack.push(hand);
			NumberStack.push(next);
			
		}else if( strcmp(instruction[IP],"D") == 0){
			NumberStack.push(next);
			NumberStack.push(hand);
			NumberStack.push(hand);
			
		}else if( strcmp(instruction[IP],"?") == 0){
			NumberStack.push(next);
			std::cout << "Cond.:" << ((hand==0)?'0':'1') << std::endl;
			//Skip to ":"
			while(hand!=0 && strcmp(instruction[IP],":")!=0 ){	IP++;	}
			
		}else if( strcmp(instruction[IP],":") == 0){
			NumberStack.push(next);
			NumberStack.push(hand);
		
		//Logic	
		}else if( strcmp(instruction[IP],"=") == 0){
			NumberStack.push(next);
			NumberStack.push(hand);
			
			std::cout << "Equality:" << ((hand==next)?'0':'1') << "->Stack" << std::endl;
			
			NumberStack.push( (hand==next)?0:1  );
			
		}else if( strcmp(instruction[IP],"!=") == 0){
			NumberStack.push(next);
			
			NumberStack.push( (hand==0)?1:0  );
		}else if( strcmp(instruction[IP],">=") == 0){
			NumberStack.push(next);
			
			NumberStack.push( (next>=hand)?0:1  );
		}else if( strcmp(instruction[IP],"<=") == 0){
			NumberStack.push(next);
			
			NumberStack.push( (next<=hand)?0:1  );
		}
		
		//"Functions"
		else if( (strcmp(instruction[IP],"a") == 0) || (strcmp(instruction[IP],"abs") == 0) ){
			//Absolutwert
			std::cout << "abs(" << hand << ")=" << abs(hand) << std::endl;
			NumberStack.push(next);
			NumberStack.push( abs(hand) );
		}
		
		//Bitwise binary
		else if( strcmp(instruction[IP],"&") == 0){
			std::cout << next << '&' << hand << '=' << ((int)next&(int)hand) << std::endl;
			NumberStack.push((int)next&(int)hand);
		}else if( strcmp(instruction[IP],"|") == 0){
			std::cout << next << '|' << hand << '=' << ((int)next|(int)hand) << std::endl;
			NumberStack.push((int)next|(int)hand);
		}else if( strcmp(instruction[IP],"^") == 0){
			std::cout << next << '^' << hand << '=' << ((int)next^(int)hand) << std::endl;
			NumberStack.push((int)next^(int)hand);
		}else if( strcmp(instruction[IP],"!") == 0){
			std::cout << '!' << hand << '=' << ~(int)hand << std::endl;
			NumberStack.push(next);
			NumberStack.push(~(int)hand);
		}else if( strcmp(instruction[IP],"<") == 0){
			std::cout << next << '<' << hand << '=' << ((int)next << (int)hand) << std::endl;
			NumberStack.push(next);
			NumberStack.push( (int)next << (int)hand);
		}else if( strcmp(instruction[IP],">") == 0){
			std::cout << next << '>' << hand << '=' << ((int)next >> (int)hand) << std::endl;
			NumberStack.push( (int)next >> (int)hand);
		}
		//Numbers
		else{
			NumberStack.push( next );
			NumberStack.push( hand );
			std::cout << "Stack<-" << instruction[IP] << std::endl;
			NumberStack.push( std::stod( instruction[IP] ) );
		}	
  		
  	}
  	
	
	free(instruction);
	
	//std::cout << NumberStack.top() << std::endl;
	return NumberStack.top();

}
