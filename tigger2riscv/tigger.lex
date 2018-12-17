%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
string tokenString;

void PR();
%}

%option yylineno

delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z_]
digit   [0-9]
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
label   l[0-9]+
var     v[0-9]+
reg     s[0-9]|s1[01]|t[0-6]|a[0-7]|x0
ffunc   f_{letter}({letter}|{digit})*

%%

"//"[^\n]* {}
{ws}       {PR();}

{reg}      {PR();tokenString = yytext; return REG;}
{var}      {PR();tokenString = yytext; return VAR;}
{label}    {PR();tokenString = yytext; return LABEL;}
{ffunc}    {PR();tokenString = yytext+2; return FUNC;}
{number}   {PR();tokenString = yytext; return NUMBER;}

"end"      {PR();return END;}
"if"       {PR();return IF;}
"goto"     {PR();return GOTO;}
"call"     {PR();return CALL;}
"load"     {PR();return LOAD;}
"loadaddr" {PR();return LOADADDR;}
"store"    {PR();return STORE;}
"return"   {PR();return RETURN;}
"malloc"   {PR();return MALLOC;}

"+"        {PR();return ADD;}
"-"        {PR();return SUB;}
"*"        {PR();return MUL;}
"/"        {PR();return DIV;}
"%"        {PR();return MOD;}
"&&"       {PR();return AND;}
"||"       {PR();return OR;}
">"        {PR();return GR;}
"=="       {PR();return EQ;}
"<"        {PR();return SM;}
"!="       {PR();return NEQ;}
"!"        {PR();return NOT;}

"="        {PR();return '=';}
":"        {PR();return ':';}
"["        {PR();return '[';}
"]"        {PR();return ']';}

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
