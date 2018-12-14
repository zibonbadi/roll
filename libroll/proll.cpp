#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <random>

int roll( int dice, int sides){
	
	std::random_device rng;	
		
	int sum = 0;
	for(int i=0;i<dice;i++){	
		std::cout << dice << 'd' << sides << " (" << i << ") " ;
		int roll = ( rng()%(sides) )+1;
		sum += roll;
		std::cout << "-> " << roll << std::endl;
	}
	std::cout << "= " << sum << std::endl;	
	
	return sum;
}


double pRoll(const char* input){

	
	std::cout << "proll ver. 0.6\nwritten by Martin Funck\n\ninput_expr: \"" << input << "\"\n\n";
	
	char* in = (char*)malloc(sizeof(char));
	strcpy(in, input);
	char* pch = strtok (in," ,;");
	
	double hand = 0;
	double next = 0;
	
	std::stack<double> NumberStack;
	
	//Pushing...
	while (pch != NULL)
	{	
		if( !NumberStack.empty() ){
			hand = NumberStack.top();
			NumberStack.pop();
			next = NumberStack.top();
			NumberStack.pop();
		}
			
			
		if( *pch == '+'){
			std::cout << next << '+' << hand << '=' << next+hand << std::endl;
			NumberStack.push(hand+next);
		}else if( *pch == '-'){
			std::cout << next << '-' << hand << '=' << next-hand << std::endl;
			NumberStack.push(next-hand);
		}else if( *pch == '*'){
			std::cout << next << '*' << hand << '=' << next*hand << std::endl;
			NumberStack.push(hand*next);
		}else if( *pch == '/'){	
			std::cout << next << '/' << hand << '=' << next/hand << std::endl;
			NumberStack.push(next/hand);
		}else if( *pch == '%'){	
			std::cout << next << '%' << hand << '=' << (( abs((int)next*(int)hand)+(int)next )%(int)hand) << std::endl;
			NumberStack.push(  ( abs((int)next*(int)hand)+(int)next ) %(int)hand);
		}else if( *pch == 'a'){
			//Absolutwert	
			std::cout << "abs(" << hand << ")=" << abs(hand) << std::endl;
			NumberStack.push(next);
			NumberStack.push( abs(hand) );
		}else if( *pch == 'd'){
			//Würfel AdB
			int out = roll((int)next, (int)hand);
			
			NumberStack.push( out );
		}else if( *pch == 'D'){
			//Explodierender Würfel	
			int total= 0;
			int out = 0;
			
			do{		
				out = roll((int)next, (int)hand);
				total += out;
			}while(out == ((int)hand * (int)next) );
			std::cout << "=> " << total << std::endl;
		
			NumberStack.push( total );
			
		}else if( *pch == '&'){	
			std::cout << next << '&' << hand << '=' << ((int)next&(int)hand) << std::endl;
			NumberStack.push((int)next&(int)hand);
		}else if( *pch == '|'){	
			std::cout << next << '|' << hand << '=' << ((int)next|(int)hand) << std::endl;
			NumberStack.push((int)next|(int)hand);
		}else if( *pch == '^'){	
			std::cout << next << '^' << hand << '=' << ((int)next^(int)hand) << std::endl;
			NumberStack.push((int)next^(int)hand);
		}else if( *pch == '!'){	
			std::cout << '!' << hand << '=' << ~(int)hand << std::endl;
			NumberStack.push(next);
			NumberStack.push(~(int)hand);
		}else if( *pch == '<'){	
			std::cout << next << '<' << hand << '=' << ((int)next << (int)hand) << std::endl;
			NumberStack.push(next);
			NumberStack.push( (int)next << (int)hand);
		}else if( *pch == '>'){	
			std::cout << next << '>' << hand << '=' << ((int)next >> (int)hand) << std::endl;
			NumberStack.push( (int)next >> (int)hand);
		}else{	
			NumberStack.push( next );
			NumberStack.push( hand );
			NumberStack.push( std::stod( pch ) );
		}
		
		pch = strtok (NULL, " ,;");
  	}
	
	
	
	//std::cout << NumberStack.top() << std::endl;
	return NumberStack.top();
	
}
