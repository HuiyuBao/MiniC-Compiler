%{
#include <ctype.h>
#include <stdio.h>
#include <math.h>
double vtab[50];
/* 存放26个变量的对应值 */
%}

%union
{
    double val;
    int no;
}
/* 定义YYSTYPE类型,也就是yylval的变量类型 */
%token <val> NUMBER
/* 绑定NUMBER和val,就是说所有NUMBER词法单元的属性值都是double型的val */
%token <no> ID
/* 绑定ID和no,同上 */

%left '+' '-'
%left '*' '/'
%right UMINUS
/* 定义左结合的加减,优先级更高的左结合的乘除,优先级再高一些的右结合的负号 */
%type <val> expr
/* expr非终结符的属性值是val */
%%

lines : lines expr '\n' {printf("ans = %g\n",$2);} /* 输入了需要求值的表达式 */
      | lines ID '=' expr '\n' {vtab[$2]=$4;} /* 输入了给变量赋值的表达式,用expr的值更新vtab */
      | lines '\n'
      |
      ;
expr  : expr '+' expr  {$$ = $1 + $3;}
      | expr '-' expr  {$$ = $1 - $3;}
      | expr '*' expr  {$$ = $1 * $3;}
      | expr '/' expr  {$$ = $1 / $3;}
      | '(' expr ')'   {$$ = $2;} /* 以上正常的加减乘除括号,优先级已在第一部分定义 */
      | '-' expr %prec UMINUS {$$ = - $2;} /* 给取负一个和UMINUS相同的优先级 */
      | NUMBER
      | ID {$$ = vtab[$1];} /* 用vtab中的值替换此处出现的变量 */
      ;
%%
#include "lex.yy.c"
int yyerror(char *s)
{
    printf("%s\n",s);
    return 0;
}
