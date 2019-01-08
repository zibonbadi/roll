#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stack>


//Liste der Operatoren: [][0] = Zeichen; [][1] = Rang; [][2]= 0?Links:Rechts -Assoziativ
struct Operator{
	char* op = nullptr;
	int rank = 0;
	int assoc = 0;

} operators[] = {
				//Arithmetic
				{"(" , -1, -1 },
				{")" , -1, -1 },
				{"+" , 4, 0 },
				{"-" , 4, 0 },
				{"*" , 3, 0 },
				{"/" , 3, 0 },
				{"%" , 3, 0 },
				//Roll
				{"d" , 3, 1 },
				//{"d!" , 3, 1 },
				//Instructions
				{"J" , 0, 1 },
				{"P" , 0, 1 },
				{"S" , 0, 0 },
				{"D" , 0, 1 },
				
				//Logic
				{"?" , 11, 1 },
				{":" , 11, 1 },
				{"=" , 7, 0 },
				{"!=" , 7, 0 },
				{">=" , 6, 0 },
				{"<=" , 6, 0 },
				
				//Functions
				{"a" , 1, 1 },
				{"abs" , 1, 1 },
				//Power/Potenz-Funktion: Nicht Assoziativ
				//{"p" , 2, 2 },
				
				//Bitwise
				{"&" , 8, 0 },
				{"|" , 9, 0 },
				{"^" , 10, 0 },	
				{"!" , 1, 1 },
				{"<" , 5, 0 },
				{">" , 5, 0 }
			};



struct Operator getOperatorData(char* op){
	const int listSize = ( sizeof(operators)/sizeof(operators[0]));
	//Check Top Stack Operator
	
	if( *op == 'd' && *(op+1) != '\0' ){	return getOperatorData("d");	}
	for(int i=0;i<listSize;i++ ){
		if( strcmp(op, operators[i].op) == 0 ){	return operators[i];	}
	}
	
	return {nullptr,-1,-1};
}


const char* iRoll_str(const char* input){

	/*/
		Infix -> Proll-Parser basierend auf
		Dijkstras Shunting-Yard-Algorithmus
	/*/

	
	std::string out = "";
	char *argString = (char*) calloc( (strlen(input)+5), sizeof(char));
	sprintf(argString, "( %s )",input );
	
	std::stack<char*> OperatorStack;

	printf("iroll v0.8.1: written by Zibon Badi.\ninput_infix: %s\n\n",argString);
	
	int exprSize = 0;
	
	char** token = (char**) calloc(1,sizeof(char**)); 
	
	//Tokenization
	//printf("Create Tokens...\n");
	argString = strtok( argString, " ,;\n");
	while (argString != NULL)
	{
		//printf("\tTkRealloc(%d)\n",exprSize);
		
		//Extend instruction memory
		token = (char**) realloc(token, sizeof(char*)*(exprSize+1) );
		//printf("\tTkAppend(%d)\n",exprSize);
		
		//Append new instruction
		token[exprSize] = argString;
		exprSize++;
		
		//printf("\tTkTokenize(%d)\n",exprSize-1);
		argString = strtok(NULL, " ,;\n");
  	}
	
	//Parsing loop
	//printf("Parse Code...\n");
	for(int t=0;t<exprSize;t++){
		
		//printf("%s [%s]\n",out.c_str() ,token[t] );	
		
		try{
			//Token ist Zahl
			double tDouble = std::stod( token[t] );
			
			out.append( token[t]);
			out.append( " ");
				
		}catch( std::invalid_argument &ia){
		
			if( strcmp(token[t],"(")==0 ){
				OperatorStack.push( token[t] );
			}else if( strcmp(token[t],")")==0 ){
				
				while( strcmp(OperatorStack.top(),"(")!=0  )
				{	
					//printf("Normal Bracket: OP '%s';\n", OperatorStack.top() );
					out.append( OperatorStack.top() );
					out.append( " " );
					OperatorStack.pop();
				}
				//Klammer poppen
				OperatorStack.pop();
			}else if( (getOperatorData( token[t] ).op != nullptr) ){

				//std::cout << "Debug Print: TSO" << std::endl;
				struct Operator topStackOperator = getOperatorData(	OperatorStack.top()	);
				//std::cout << "Debug Print: TkO" << std::endl;
				struct Operator tokenOperator = getOperatorData(	token[t]	);

				//std::cout << topStackOperator.op << ',' << tokenOperator.op << std::endl;

				//Precedence-Loop
				while(	!OperatorStack.empty()	&&
					(
						(topStackOperator.rank < tokenOperator.rank )	||
				      		(	(topStackOperator.rank == tokenOperator.rank ) &&
				      		 	(topStackOperator.assoc == 0)
				      		)
				      	) && strcmp(OperatorStack.top(),"(")!=0 ){
					
					//printf("Stack >> %s;\n",OperatorStack.top() );
					
					out.append( OperatorStack.top() );
					out.append( " " );
					OperatorStack.pop();
				}
				//printf("%s >> Stack;\n",token[t] );
				OperatorStack.push(token[t]);
			}
	
		}
				
		
	}	

  	while(  !OperatorStack.empty() ){
		std::cout << "Excess Operator \"" << OperatorStack.top() << '"'<< std::endl;
		out.append( OperatorStack.top() );
		out.append( " " );
		OperatorStack.pop();
	}

	char* CStrOut = (char*) calloc(1,sizeof(char*));
	strncpy(CStrOut, out.c_str(), out.length()+1 );
	
	//std::cout << "[" << CStrOut << "]\n";
	
	return CStrOut;
}
