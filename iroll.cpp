#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stack>


//Liste der Operatoren: [][0] = Zeichen; [][1] = Rang; [][2]= 0?Links:Rechts -Assoziativ	
const int operators[][3] = {	
				{(int)'(' , -1, -1 },
				{(int)')' , -1, -1 },
				{(int)'+' , 4, 0 },
				{(int)'-' , 4, 0 },
				{(int)'*' , 3, 0 },
				{(int)'/' , 3, 0 },
				//Power/Potenz-Funktion: Nicht Assoziativ
				//{(int)'p' , 2, 2 },
				{(int)'%' , 3, 0 },
				{(int)'d' , 3, 1 },
				{(int)'D' , 3, 1 },
				{(int)'a' , 1, 1 },
				{(int)'&' , 6, 0 },
				{(int)'|' , 7, 0 },
				{(int)'^' , 8, 0 },
				{(int)'!' , 1, 1 },
				{(int)'<' , 5, 0 },
				{(int)'>' , 5, 0 }	
			};	



const int *getOperatorData(char op){
	const int listSize = ( sizeof(operators)/sizeof(operators[0]));
	//Check Top Stack Operator
	for(int i=0;i<listSize;i++ ){
		if( (int)op == operators[i][0] ){	return operators[i];	}
	}
	
	
	
	return	(const int[]){-1,-1,-1};		
}


const char* iRoll_str(const char* input){

	/*/
		Infix -> Proll-Parser basierend auf
		Dijkstras Shunting-Yard-Algorithmus
	/*/
	
		
			
	char *argString = (char*) malloc(sizeof(char));
	strcat(argString, "(");
	strcat(argString, input);
	strcat(argString, ")");
	
	//std::cout << (int) *argString << ',' << argString << ',' << sizeof(argString)  << std::endl;
	
	
	
	/*/
	for(int i=1;i<argc;i++){	
		//std::cout << i << '-';
		
		
		//char* tmp = (char*) realloc(argString,sizeof(argString)+sizeof(argv[i]));
		//strcat(tmp, argString);
		//strcat(tmp, argv[i]);
		//strcat(tmp, " ");
		//argString = tmp;
		//free(tmp);
		
		
		strcat(argString, argv[i]);
		//std::cout << argv[i] << "... Done!\n";
	}
	
	strcat(argString, ")");
	
		
	//std::cout << "iRoll ver. 0.1: a Proll-Parser.\nwritten by Martin Funck\n" << std::endl;
	
	
	std::cout << '"' << argString << '"' << std::endl;
	
	/*/
	
	
	//std::string out = "";		
	char* out = (char*) malloc(sizeof(char));
	std::stack<char> OperatorStack;
	
	//Pushing...
	while ( (int)*argString != (int)'\0')
	{	
		//printf("%c",*argString);
		
		bool numberLoop = false;
		while( ((*argString >='0') && (*argString <= '9')) || *argString == '.' ){
				numberLoop = true;
				out = strncat(out,argString,1);
				argString++;
		}
		
		if( numberLoop ){	out = strcat(out," ");	}
		
		if( *argString == '('){
			OperatorStack.push(*argString);
		}else if( *argString == ')'){
			while( OperatorStack.top() != '(' )
			{
				out = strncat(out,&OperatorStack.top(),1 );
				out = strcat(out," ");
				OperatorStack.pop();
			}
			//Klammer poppen
			OperatorStack.pop();
		}else if ( (*argString == ' ') || (*argString == ',') || (*argString == ';')){
		}else{	
			
			
			if( !OperatorStack.empty() && (getOperatorData(*argString)[0] != -1) ){
				
				//std::cout << "Debug Print: TSO" << std::endl;
				const int *topStackOperator = getOperatorData(	OperatorStack.top()	);
				//std::cout << "Debug Print: TkO" << std::endl;
				
				const int *tokenOperator = getOperatorData(	*argString	);
				
				//std::cout << (char)topStackOperator[0] << ',' << (char)tokenOperator[0] << std::endl;
				
				//Precedence-Loop
				while(	(	(topStackOperator[1] < tokenOperator[1]) ||
				      		(	(topStackOperator[1] == tokenOperator[1]) &&
				      		 	(topStackOperator[2] == 0) )
				      	) && OperatorStack.top() != '(' ){
					
					out = strncat(out,&OperatorStack.top(),1 );
					out = strcat(out," ");
					OperatorStack.pop();
				}
				OperatorStack.push(*argString);
			}
			
			
		}
		
		argString++;	
  	}
  	
  	
  	while(  !OperatorStack.empty() ){
		std::cout << '"' << OperatorStack.top() << '"'<< std::endl;
		out = strncat(out,&OperatorStack.top(),1 );
		out = strcat(out," ");
		//printf("%c ",OperatorStack.top());
		OperatorStack.pop();		
	}
	
	
	//std::cout << "iroll_out: " << out << std::endl;
		
	return out;
}
