/* read the source program from file to a 
buffer memory*/

char* readFile(char* Filename){

	FILE *read;
	

	read = fopen(Filename,"r");

	if( NULL == read ){
		printf("Error Reading File.Program Exiting");
		exit(1);
	}
	else{
		
		int i=0;
		char Buffer[MAXLENGTH * MAXLINE]={0};

		while(!feof(read))
			Buffer[i++]=fgetc(read);
		fclose(read);

		Buffer[i-1]=0;
		return Buffer;
	}

}

void writeFile(char* Filename,char* Buffer){

	FILE *write;

	write = fopen(Filename,"w");

	if( NULL == write ){
		printf("Error Writing  File.Program Exiting");
		exit(1);
	}
	else{
		while(*Buffer){
			fputc(*Buffer,write);
			Buffer++;
		}
		fclose(write);
	}
}


/*this function is used to build the symbol table*/

void buildSymolTable(char* Buffer,long Location){

	char temp[MAXLENGTH];
	int i=0,j=0;
	

	Location -= 1;

	while( Buffer[i] != '\0' ){

		/* get the mnemonic i.e the token*/
		while( isalnum(Buffer[i]) && Buffer[i] != ' ') {
			temp[j++] = Buffer[i++];
		}
		
		temp[j]=0;
		j=0;
		
		if( isMnemonic(temp) ){
		
		/* is the token is mnemonic then
		move to the next line*/

			while(Buffer[i] != '\n')	
				i++;	
			Location++;	/*update the location counter it it is a menmonic*/
			continue;
		}

		i++;

		if( isSymbol(temp) ){	
			/* add the symbols and loction to the symbol table*/
			addSymbol(temp,Location);
		}
		
	}

}

/*this function is used to add the symbols to the table
with the location*/

void addSymbol(char* SymbolName,long location){
	Symbols[count].location=location;
	strcpy(Symbols[count].symbolName,SymbolName);
	count++;
}

/*to list of the symbol table*/
void printSymbols(){
	int i;

	for(i=0;i<count;i++)
		printf("%s\t%d\n",Symbols[i].symbolName,Symbols[i].location);
}


/*convert into machine language*/
char* toMachineCode(char* Buffer,long Location){

	char mCode[MAXLENGTH * MAXLINE];
	int k=0,value;
	int MnFound,stopFound;

	stopFound = MnFound = FALSE;
	
	k+=sprintf(mCode+k,"%d ",Location);

	while( *Buffer ){
	Buffer = getToken(Buffer);

		switch(type){
			case MNEMONIC:

				if( stricmp(token,"START") == 0 ||
					stricmp(token,"END") == 0 ){

					while( *Buffer != '\n' )
						Buffer++;
					continue;
				}
				
				if(	stricmp(token,"DS") == 0 ){
					while( *Buffer != '\n' )
						Buffer++;
					
					break;
				}

				value = getOpCode(token);

				if( value == NOMNEMONIC )
					error("No Mnemonic Found in the Table or Error in Mnemonic",Location);

				k+=sprintf(mCode+k,"%.2d ",value);
				MnFound = TRUE;

				/* if the Mnemonic is READ or PRINT the First 
				operand is not used so insert 0*/

				if( stricmp(token,"STOP") == 0 ){
					k+=sprintf(mCode+k,"%.1d %.3d",0,0);
					stopFound = TRUE;
					MnFound = FALSE;
				}

				if( stricmp(token,"READ") == 0 ||
					stricmp(token,"PRINT") == 0	||
					stricmp(token,"DC") == 0	 )
						k+=sprintf(mCode+k,"%.1d ",0);
				
				
				break;
			case SYMBOL:
				if( MnFound ){
					if( NOT stopFound ){
				value = getSymbolLocation(token);

				if( value == NOSYMBOL )
					error("No Symbol Found in the Table",Location);

				k+=sprintf(mCode+k,"%d ",value);
					}
				}
				break;
			case REGISTER:
				value = getRegisterCode(token);

				if( value == NOREGISTER )
					error("No Register Code Found in the Table",Location);

				k+=sprintf(mCode+k,"%.1d ",value);
				break;
			case CONDITION:
				value = getConditionCode(token);

				if( value == NOCONDITION )
					error("No Condition Code Found in the Table",Location);

				k+=sprintf(mCode+k,"%.1d ",value);
				break;
			case VALUE:
				if( *token ){
				k+=sprintf(mCode+k,"%.3d ",atol(token));
				Buffer++;
				}
				break;
		}

		if( *Buffer == '\n'){
			getToken(Buffer);

			if( NOT ( stricmp(token,"END") == 0 ) ){
				Buffer++;
				k+=sprintf(mCode+k,"\n%d ",++Location);
				MnFound = FALSE;
			}
		}
	}
	
	return mCode;
}

/*convert into machine language*/
char* toObjCode(char* Buffer,long Location){

	int value;
	int MnFound = FALSE,stopFound = FALSE;

	FILE *fp;

	fp = fopen("objectcode.obj","w");

	putw(Location,fp);
	while( *Buffer ){
	Buffer = getToken(Buffer);

		switch(type){
			case MNEMONIC:

				if( stricmp(token,"START") == 0  ||
					stricmp(token,"END") == 0 ){

					while( *Buffer != '\n' )
						Buffer++;

					continue;
				}

				if(	stricmp(token,"DS") == 0 ){
					while( *Buffer != '\n' )
						Buffer++;
					break;
				}

				value = getOpCode(token);
				putw(value,fp);
				MnFound = TRUE;

				/* if the Mnemonic is READ or PRINT the First 
				operand is not used so insert 0*/

				if( stricmp(token,"STOP") == 0 ){
					putw(0,fp);putw(0,fp);
					
					putw(0,fp);putw(0,fp);putw(0,fp);

					stopFound = TRUE;
					MnFound = FALSE;
				}

				if( stricmp(token,"READ") == 0 ||
					stricmp(token,"PRINT") == 0	||
					stricmp(token,"DC") == 0	 ){
							putw(0,fp);
							putw(0,fp);
				}
				
				
				break;
			case SYMBOL:
				if( MnFound ){
					if( NOT stopFound ){
				value = getSymbolLocation(token);
				putw(value,fp);
					}
				}
				break;
			case REGISTER:
				value = getRegisterCode(token);
				putw(value,fp);
				break;
			case CONDITION:
				value = getConditionCode(token);
				putw(value,fp);
				break;
			case VALUE:
				if( *token ){
				putw(atol(token),fp);
				Buffer++;
				}
				break;
		}

		if( *Buffer == '\n'){
			getToken(Buffer);

			if( NOT ( stricmp(token,"END") == 0 ) ){
				Buffer++;
				putw(++Location,fp);
				MnFound = FALSE;
			}
		}
	}
	fclose(fp);
	return "";
}

void error(char* Message,long Position){
	printf("%s\nAt:%ld\nProgram Terminating\n",Message,Position);
	exit(1);
	return;
}