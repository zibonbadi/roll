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

	
	char* out = (char*) calloc(1,1);
	char *argString = NULL;
	argString = (char*) realloc(argString, strlen(input)+3);
	sprintf(argString, "(%s)",input );

	//std::cout << argString << ',' << strlen(argString) << std::endl;

	std::stack<char> OperatorStack;

	printf("iroll ver. 0.6.2\ninput_infix: %s\n\n",argString);
	
	//Pushing...
	while ( *argString != '\0')
	{
		//printf("\n[%s][%c]",out,*argString);
		
		if( ((*argString >='0') && (*argString <= '9')) || *argString == '.' ){
			
			while( ((*argString >='0') && (*argString <= '9')) || *argString == '.' ){
				//printf("{%c}",*argString);
				
				out = (char*)realloc(out,strlen(out)+2); 
				strncat(out,argString,1);
				//sprintf(out, "%s%c",out,*argString);
				
				argString++;
			}
			
			argString--;
			
			out = (char*)realloc(out,strlen(out)+2); 
			sprintf(out,"%s ",out );	
			//sprintf(out,"%s%d ",out,std::stod(out,0) );	
				
		}else if( *argString == '('){
			OperatorStack.push(*argString);
		}else if( *argString == ')'){
			while( OperatorStack.top() != '(' )
			{	
				out = (char*)realloc(out, strlen(out)+3); 
				sprintf(out, "%s%c ",out,OperatorStack.top());
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
					
					//printf("Stack >> %c;",OperatorStack.top() );
					
					out = (char*)realloc(out,strlen(out)+3);
					sprintf(out,"%s%c ",out,OperatorStack.top());
					OperatorStack.pop();
				}
				//printf("%c >> Stack\n",*argString );
				OperatorStack.push(*argString);
			}


		}
	
		argString++;
  	}


  	while(  !OperatorStack.empty() ){
		std::cout << '"' << OperatorStack.top() << '"'<< std::endl;
		out = (char*)realloc(out,strlen(out)+3); 
			//printf("Stack >> %c.",OperatorStack.top() );
		sprintf(out,"%s%c ",out,OperatorStack.top());
		OperatorStack.pop();
	}


	//std::cout << "iroll_out: " << out << std::endl;

	return out;
}
