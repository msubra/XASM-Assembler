#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

/* some limits used in the program */
#define MAXLINE 80
#define MAXLENGTH 80
#define MAXSYMBOLS 100
#define MAXMNEMONIC 16
#define MAXREGISTER 4
#define MAXCONDITION 6

/* error codes */
#define NOMNEMONIC	-1
#define NOSYMBOL	-2
#define NOREGISTER	-3
#define NOCONDITION	-4

#define NOT !
#define TRUE 1
#define FALSE NOT TRUE
#define NOERROR 1

/* definition for symbol table */
typedef struct _symTbl{
	char	symbolName[MAXLENGTH];
	int		location;
}SymbolTable;

/* definition for Mnemonic table */
typedef struct _mnTbl{
	char	opCodeName[MAXLENGTH];
	int		opCode;
}MnemonicTable;

/* definition for Register table */
typedef struct _regTbl{
	char	registerName[5];
	int		registerNo;
}RegisterTable;

/* type of instruction */
enum _instruction {MNEMONIC,REGISTER,SYMBOL,CONDITION,VALUE};

typedef enum _instruction INSTRUCTION;

/* to read and write source program*/
char*	readFile		(char*);
void	writeFile		(char*,char*);

/*to build symboltable and to print*/
void	buildSymolTable	(char*,long);
void	addSymbol		(char*,long);
void	printSymbols	(void);	

/*these function are used to check the
given tokens*/
int		isMnemonic		(char*);
int		isSymbol		(char*);
int		isRegister		(char*);
int		isSymbolFound	(char*);
int		isCondition		(char*);

/*these functions are used to get the
values of the token*/
long	getLocation		(char[]);
int		getSymbolLocation(char*);
int		getRegisterCode	(char*);
int		getOpCode		(char*);
char*	getToken		(char*);
int		getConditionCode(char*);

void	error			(char*,long);
/*function to convert into machine code and to object code*/
char*	toMachineCode	(char*,long);
char*	toObjCode		(char*,long);

/*for storing the symbols*/
SymbolTable Symbols[MAXSYMBOLS];

/*for storing the Mnemonics*/
MnemonicTable	MnTable[MAXMNEMONIC]=
{ 
	"STOP",0	,"ADD",1	,"SUB",2	,"MULT",3	,"MOVER",4,
	"MOVEM",5	,"COMP",6	,"BC",7		,"DIV",8	,"READ",9,
	"PRINT",10	,"DC",0		,"DS",0		,"CMP",0	,"START",0,
	"END",0
};
	
/*for storing the Registers*/
RegisterTable RegTable[MAXREGISTER]=
{
	"AREG"	,	1,
	"BREG"	,	2,
	"CREG"	,	3,
	"DREG"	,	4
};

/*for storing the Condition values*/
char Condition[MAXCONDITION][4] = 
{
	"LT","LE","EQ","GT","GE","ANY"
};


int count=0;
INSTRUCTION	type;
char token[MAXLENGTH];