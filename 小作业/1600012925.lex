
number [0-9]+\.?|[0-9]*\.[0-9]+
/* 整型数字或浮点型数字 */
id [a-z]
/* 变量名,只支持26个小写字母的单字符变量名 */
%%

[ \t] {}
{number} {sscanf(yytext,"%lf",&yylval.val); return NUMBER;}  /* 是数字就读进yylval */
{id} {yylval.no=yytext[0]-'a'; return ID;}  /* 是变量就返回是第几个小写字母,变量值在yacc中赋 */
\n|. {return yytext[0];}
%%
