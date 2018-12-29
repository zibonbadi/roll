#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <random>

int roll( int dice, int sides){

	std::random_device rng;

	int sum = 0;
	
	if(sides > 0){
		for(int i=0;i<dice;i++){
			std::cout << '\t' << dice << 'd' << sides << " (" << i << ") " ;
			int roll = ( rng()%(sides) )+1;
			sum += roll;
			std::cout << "-> " << roll << std::endl;
		}
		std::cout << "\t= " << sum << std::endl;
	}
	
	return sum;
}


double pRoll(const char* input){


	std::cout << "proll ver. 0.7: written by Zibon Badi.\ninput_expr: \"" << input << "\"\n\n";

	char* pch = strtok ((char*)input," ,;\n");
	int codeSize = 0;
	
	//Instruction Token StringArray
	char** instruction = (char**) calloc(1,sizeof(char**));
	//UPN-Code setup
	while (pch != NULL)
	{
	
		printf(">%d,%s\n",codeSize,pch );
		
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
		else if( strcmp(instruction[IP],"d") == 0){
			//Würfel AdB
			int out = roll((int)next, (int)hand);

			NumberStack.push( out );
		}else if( strcmp(instruction[IP],"d!") == 0){
			//Explodierender Würfel
			int total= 0;
			int out = 0;

			do{
				out = roll((int)next, (int)hand);
				total += out;
			}while(out == ((int)hand * (int)next) );
			std::cout << "\t=> " << total << std::endl;

			NumberStack.push( total );

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
			std::cout << instruction[IP] << ">Stack" << std::endl;
			NumberStack.push( std::stod( instruction[IP] ) );
		}	
  		
  	}
  	
	
	free(instruction);
	
	//std::cout << NumberStack.top() << std::endl;
	return NumberStack.top();

}
