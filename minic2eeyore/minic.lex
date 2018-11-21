%{
/*
#define IF 10
#define ELSE 11
#define WHILE 12
#define RETURN 13
#define INT 14
#define MAIN 15
#define ID 16
#define NUMBER 17
#define ASSIGN 18
#define EQ 19
#define UEQ 20
#define GR 21
#define SM 22
#define AND 23
#define OR 24
#define ADD 25
#define SUB 26
#define MUL 27
#define DIV 28
#define MOD 29
#define NOT 30
*/
#include "globals.h"
#include <stdio.h>
#include <string.h>
char tokenString[MAXTOKENLEN]; //token string
int tokenval; // token value(if has)

void PR();
%}

%option yylineno

delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z_]
digit   [0-9]
id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

"//"[^\n]* {}
{ws}       {PR();}

"if"       {PR();return IF;}
"else"     {PR();return ELSE;}
"while"    {PR();return WHILE;}
"return"   {PR();return RETURN;}
"int"      {PR();return INT;}
"main"     {PR();strcpy(tokenString, yytext);return MAIN;}

{id}       {PR();strcpy(tokenString, yytext); return ID;}
{number}   {PR();tokenval = atoi(yytext); return NUMBER;}

"="        {PR();return ASSIGN;}
"=="       {PR();return EQ;}
"!="       {PR();return UEQ;}
">"        {PR();return GR;}
"<"        {PR();return SM;}
"&&"       {PR();return AND;}
"||"       {PR();return OR;}
"+"        {PR();return ADD;}
"-"        {PR();return SUB;}
"*"        {PR();return MUL;}
"/"        {PR();return DIV;}
"%"        {PR();return MOD;}
"!"        {PR();return NOT;}

";"        {PR();return ';';}
","        {PR();return ',';}
"("        {PR();return '(';}
")"        {PR();return ')';}
"["        {PR();return '[';}
"]"        {PR();return ']';}
"{"        {PR();return '{';}
"}"        {PR();return '}';}

%%

void PR()
{
    fprintf(stderr,"%s",yytext);
}

int yywrap()
{
    return 1;
}

void yyerror(char *message)
{
    if(fin_parse == 1)
        printf("\n%s\n",message);
    else
        printf("\nError happens at line %d\n%s\n",yylineno,message);
    exit(0);
}

/*
int gettoken()
{
    static int firsttime = TRUE;
    int currenttoken;
    if(firsttime)currenttoken = yylex();
    fprintf(stderr,"%s\n",yytext);
    return currenttoken;
}


int main()
{
    yyin = stdin;
    int t = 500;
    while(t--)
    {
        printf("%d\n",yylex());
    }
}
*/
