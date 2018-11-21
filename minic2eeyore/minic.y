%{
#include "globals.h"
#include "util.h"
#define dfltarrsize 200

#define YYSTYPE Treenode*
static Treenode *savedTree;
static int fin_parse;

static int yylex();

extern char tokenString[MAXTOKENLEN];
extern int tokenval;

extern void yyerror(char *message);
extern int yylex();

%}

%left OR
%left AND
%left EQ UEQ
%left GR SM
%left ADD SUB
%left MUL DIV MOD
%right NOT MINUS

%token IF ELSE WHILE
%token RETURN INT MAIN
%token ID NUMBER ASSIGN

%%

Goal: S {$$ = $1; savedTree = $$;}
    ;

S: S T
   {
      YYSTYPE t = $1;
      if(t!=NULL)
      {
          while(t->sibling != NULL)t=t->sibling;
          t->sibling = $2;
          $$ = $1;
      }
      else $$ = $2;
   }
 | {$$ = NULL;}
 ;

T: VarDefn {$$ = $1;}
 | FuncDefn {$$ = $1;}
 | FuncDecl {$$ = $1;}
 ;

VarDefn: Type Identifier ';' {$$ = newvardefnode($2->attr.name,0);}
       | Type Identifier '[' NUMBER ']' ';' {$$ = newvardefnode($2->attr.name, tokenval);}
       ;

ValDecl: Type Identifier {$$ = newvardeclnode($2->attr.name,0);}
       | Type Identifier '[' NUMBER ']' {$$ = newvardeclnode($2->attr.name, tokenval);}
       | Type Identifier '[' ']' {$$ = newvardeclnode($2->attr.name,dfltarrsize);}
       ;

FuncDefn: Type Identifier '(' Varlist ')' '{' FuncBody '}'
          {$$ = newfuncdefnode($2->attr.name,$4,$7);}
        ;

Varlist: ValDecl {$$ = $1;}
       | Varlist ',' ValDecl
       {
          YYSTYPE t = $1;
          while(t->sibling != NULL)t = t->sibling;
          t->sibling = $3;
          $$ = $1;
       }
       | {$$ = NULL;}
       ;

FuncBody: FuncBody U
          {
             YYSTYPE t = $1;
             if(t!=NULL)
             {
                 while(t->sibling != NULL)t=t->sibling;
                 t->sibling = $2;
                 $$ = $1;
             }
             else $$ = $2;
          }
        | {$$ = NULL;}
        ;

U: FuncDecl {$$ = $1;}
 | Statement {$$ = $1;}
 ;

FuncDecl: Type Identifier '(' Varlist ')' ';'
        {$$ = newfuncdeclnode($2->attr.name,$4);}
        ;

Type : INT
     ;

Statementline: Statementline Statement
               {
                  YYSTYPE t = $1;
                  if(t != NULL)
                  {
                      while(t->sibling != NULL)t=t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                  }
                  else $$ = $2;
               }
               | {$$ = NULL;}
               ;

Statement: '{' Statementline '}' {$$ = newstmtnode1($2);}
         | IF '(' Expression ')' Statement{$$ = newstmtnode2($3,$5);}
         | IF '(' Expression ')' Statement ELSE Statement {$$ = newstmtnode3($3,$5,$7);}
         | WHILE '(' Expression ')' Statement {$$ = newstmtnode4($3,$5);}
         | Identifier ASSIGN Expression ';' {$$ = newstmtnode5($1,$3);}
         | Identifier '[' Expression ']' ASSIGN Expression ';'{$$ = newstmtnode6($1,$3,$6);}
         | VarDefn {$$ = $1;}
         | RETURN Expression ';' {$$ = newstmtnode7($2);}
         ;

Expression: Expression ADD Expression {$$ = newexprnode1($1,$3,0);}
          | Expression SUB Expression {$$ = newexprnode1($1,$3,1);}
          | Expression MUL Expression {$$ = newexprnode1($1,$3,2);}
          | Expression DIV Expression {$$ = newexprnode1($1,$3,3);}
          | Expression MOD Expression {$$ = newexprnode1($1,$3,4);}
          | Expression AND Expression {$$ = newexprnode2($1,$3,0);}
          | Expression OR Expression {$$ = newexprnode2($1,$3,1);}
          | Expression SM Expression {$$ = newexprnode2($1,$3,2);}
          | Expression EQ Expression {$$ = newexprnode2($1,$3,3);}
          | Expression GR Expression {$$ = newexprnode2($1,$3,4);}
          | Expression UEQ Expression {$$ = newexprnode2($1,$3,5);}
          | Expression '[' Expression ']' {$$ = newexprnode3($1,$3);}
          | NUMBER {$$ = newexprnode4(tokenval);}
          | Identifier {$$ = newexprnode5($1);}
          | NOT Expression {$$ = newexprnode6($2);}
          | SUB Expression %prec MINUS {$$ = newexprnode7($2);}
          | '(' Expression ')' {$$ = $2;}
          | Identifier '(' identlist ')' {$$ = newexprnode8($1,$3);}
          ;

identlist: Identifier {$$ = $1;}
         | identlist ',' Identifier
           {
              YYSTYPE t = $1;
              while(t->sibling != NULL)t = t->sibling;
              t->sibling = $3;
              $$ = $1;
           }
         | {$$ = NULL;}
         ;

Identifier: ID {$$ = newidntnode(tokenString);}
          | MAIN {$$ = newidntnode(tokenString);}
          ;

%%
#include "lex.yy.c"

int main(int argc,char **argv)
{
    if(argc > 1)
    {
        FILE *file1;
        file1 = fopen(argv[1],"r");
        yyin = file1;
    }
    fin_parse = 0;
    yyparse();
    fin_parse = 1;
    //freopen("ee.out","w",stdout);
    //Printree(savedTree,0);
    //printf("\n\n\n");
    Generate(savedTree);
    fclose(yyin);
    return 0;
}
