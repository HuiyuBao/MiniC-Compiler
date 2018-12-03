%{
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
id      [Ttp]{digit}+
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
label   l[0-9]+
ffunc   f_{letter}({letter}|{digit})*

%%

"//"[^\n]* {}
{ws}       {PR();}

"if"       {PR();return IF;}
"var"      {PR();return VAR;}
"return"   {PR();return RETURN;}
"goto"     {PR();return GOTO;}
"call"     {PR();return CALL;}
"end"      {PR();return END;}
"param"    {PR();return PARAM;}

{id}       {PR();strcpy(tokenString, yytext); return ID;}
{number}   {PR();tokenval = atoi(yytext); return NUMBER;}
{label}    {PR();strcpy(tokenString, yytext); return LABEL;}
{ffunc}    {PR();strcpy(tokenString, yytext); return FUNC;}

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

':'        {PR();return ':';}
'['        {PR();return '[';}
']'        {PR();return ']';}

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
    printf("\n%s\n",message);
    exit(0);
}
