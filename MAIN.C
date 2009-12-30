/*  This program is to convert the ASM Codes into its
respective machine code
author:MaheshWaran.S B.E-II year CSE
*/

#include "d:\cfiles\asm\xasm\decl.h"
#include "d:\cfiles\asm\xasm\check.h"
#include "d:\cfiles\asm\xasm\get.h"
#include "d:\cfiles\asm\xasm\xasm.h"

void main(){

	char buf[MAXLINE * MAXLENGTH]={0};
	char asmCode[MAXLINE * MAXLENGTH]={0};
	char inFileName[MAXLENGTH]={0};
	char outFileName[MAXLENGTH]={0};
	long locCounter; /*location Counter for the program*/

	printf("\t\t\tXASM Assembler\n\n");

	printf("Enter the FileName to read:");	/*get the assembly filename*/
	gets(inFileName);

	printf("Enter the FileName to write:");	/*get the assembly filename*/
	gets(outFileName);

	printf("\n\nAssembly Code\n\n");

	/* read the content of the file into a buffer */
	strcpy(buf,readFile(inFileName) );
	
	/* get the starting location of the program */
	locCounter=getLocation(buf);
	
	/* build the symbol table */
	buildSymolTable(buf,locCounter);

	/* it converts the asm code to machine code*/
	
	strcpy(asmCode , toMachineCode(buf,locCounter) );
	puts(asmCode);

	/* write the assembly code into a file */
	writeFile(outFileName,asmCode);
	toObjCode(buf,locCounter);
	
	getch();
	return;
}