/*check wheather the
token is Mnenonic or not*/

int isMnemonic(char* Mn){

	int i=0;

	while( i<MAXMNEMONIC )
		if ( stricmp(MnTable[i++].opCodeName,Mn) == 0 )
			return TRUE;

	return FALSE;
}

/*check wheather the
token is Condition Code or not i.e
LT,LE,GT,GE,EQ,ANY
*/

int isCondition(char* Cond){
	int i;

	for(i=0;i<MAXCONDITION;i++)
		if( stricmp(Condition[i],Cond) == 0 )
			return TRUE;

	return FALSE;
}

/*check wheather the
token is given Symbol is Found
*/

int isSymbolFound(char* SymbolName){
	int i=0;

	for(i=0;i<count;i++)
		if( stricmp(SymbolName,Symbols[i].symbolName) == 0 )
			return TRUE;

	return FALSE;
}

/*to check wheather the token 
is a symbol or not*/

int isSymbol(char* LableName){
	return (NOT isMnemonic(LableName) && 
			NOT isRegister(LableName) &&
			NOT isCondition(LableName) &&
			NOT atol(LableName)		  &&
			NOT strcmp(LableName,"") == 0);
}

/*to check the token is a Register name*/
int isRegister(char* RegisterName){
	int i;

	for(i=0;i<MAXREGISTER;i++)
		if(stricmp(RegTable[i].registerName,RegisterName) == 0)
			return TRUE;

	return FALSE;
}