/* this is used to get the 
starting location of the program*/

long getLocation(char Loc[]){

	char temp[MAXLENGTH];
	int i=0,j=0,k=0;

	while(Loc[k] ==' ' || Loc[k] == '\t')
		k++;

	while(Loc[k] != ' ' && Loc[k] != '\t' && Loc[k] != NULL)
		temp[i++] = Loc[k++];

		if( stricmp(temp,"START") ){ /*to know the starting location of the program*/
			j=0;
		
			while(Loc[k] ==' ' || Loc[k] == '\t')
					k++;
			while(Loc[k] != '\n'){
				temp[j++] = Loc[k++];
			}

		}

		return atol(temp);
}


/*to get the register code for the given register */
int	getRegisterCode(char* RegisterName){
	int i;

	for(i=0;i<MAXREGISTER;i++)
		if( stricmp(RegTable[i].registerName,RegisterName) == 0 )
			return	RegTable[i].registerNo;

	return NOREGISTER;
}

/*to get the condition code for the given condition */
int getConditionCode(char* Cond){
	
	int i;

	for(i=0;i<MAXCONDITION;i++)
		if( stricmp(Condition[i],Cond) == 0 )
			return i+1;

	return NOCONDITION;
}

/*to get location of the given symbol*/
int getSymbolLocation(char* SymbolName){
	int i;

	for(i=0;i<count;i++)
		if( stricmp(Symbols[i].symbolName,SymbolName) == 0 )
			return	Symbols[i].location;

	return NOSYMBOL;
}

/*to get the opcode for the given mnemonic*/
int getOpCode(char* MnemonicName){

	int i;

	for(i=0;i<MAXMNEMONIC;i++)
		if( stricmp(MnTable[i].opCodeName,MnemonicName) == 0 )
			return MnTable[i].opCode;

	return NOMNEMONIC;
}

/*this function isolates the source codes into tokens
with the delimiters.the delimiters are ' ' , ',' , ' \n'
' \' '. with the help of these delimiters we isolate the program
and split up into tokens.

  the tokes are of various type
  a. Mnemonic
  b. Value
  c. Register
  d. Symbol
  d. Condition
*/
char* getToken(char* Buffer){

	register char *temp;
	int i=0;

	type = -1;
	temp = token;
	*temp = '\0';

	while( *Buffer != '\0' ){

		if(! *Buffer)
			return temp;

		while( *Buffer == ' ' || *Buffer == ',' || 
			   *Buffer == '\'' || *Buffer == '\n'
			   || *Buffer == '\t')
			Buffer++;
		 
		while( isalnum(*Buffer) && *Buffer != ' ') {
			*temp++ = *Buffer++;
		}

		*temp='\0';

		if( isMnemonic(token) )
			type = MNEMONIC;
		else
			if( isSymbol(token) )
				type = SYMBOL;
		else
			if( isRegister(token) )
				type = REGISTER;
		else
			if( isCondition(token) )
				type = CONDITION;
		else
			type = VALUE;
		
		return Buffer;
	}

	return NULL;
	
}
