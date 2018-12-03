%{
#include "globals.h"
#include "util.h"

#define YYSTYPE Treenode*
static Treenode *savedTree;
static int fin_parse;

static int yylex();

extern char tokenString[MAXTOKENLEN];
extern int tokenval;

extern void yyerror(char *message);
extern int yylex();

}

%left OR
%left AND
%left EQ UEQ
%left GR SM
%left ADD SUB
%left MUL DIV MOD
%right NOT MINUS

%token IF VAR RETURN GOTO
%token CALL END PARAM
%token ASSIGN ID NUMBER LABEL FUNC

%%

Goal: S {$$ = $1; savedTree = $$;}
    ;

S: S T
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

T: VarDefn {$$ = $1;}
 | FuncDefn {$$ = $1;}
 ;

VarDefn: VAR Identifier {$$ = newvardefnode($2->attr.name,0);}
       | VAR NUMBER Identifier {$$ = newvardefnode($3->attr.name,tokenval);}
       ;

FuncDefn: Func '[' Num ']' FuncBody END Func
          {$$ = newfuncdefnode($1,$3,$5);}
        ;

FuncBody: FuncBody U
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

RtValue: Identifier {$$ = newrtvl($1,0);}
          | Num {$$ = newrtvl($1,1);}
          ;

U: Vardefn {$$ = $1;}
 | Expression {$$ = $1;}
 ;

Expression: Identifier ASSIGN RtValue ADD RtValue {$$ = newexpnode1($1,$3,$5,0);}
          | Identifier ASSIGN RtValue SUB RtValue {$$ = newexpnode1($1,$3,$5,1);}
          | Identifier ASSIGN RtValue MUL RtValue {$$ = newexpnode1($1,$3,$5,2);}
          | Identifier ASSIGN RtValue DIV RtValue {$$ = newexpnode1($1,$3,$5,3);}
          | Identifier ASSIGN RtValue MOD RtValue {$$ = newexpnode1($1,$3,$5,4);}

          | NOT RtValue {$$ = newexpnode2($2);}
          | SUB RtValue %prec MINUS {$$ = newexpnode3($2);}

          | Identifier ASSIGN RtValue {$$ = newexpnode4($1,$3);}
          | Identifier '[' RtValue ']' ASSIGN RtValue {$$ = newexpnode5($1,$3,$6);}
          | Identifier ASSIGN Identifier '[' RtValue ']' {$$ = newexpnode6($1,$3,$5);}

          | IF RtValue AND RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,0);}
          | IF RtValue OR RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,1);}
          | IF RtValue SM RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,2);}
          | IF RtValue EQ RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,3);}
          | IF RtValue GR RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,4);}
          | IF RtValue UEQ RtValue GOTO Label {$$ = newexpnode7($2,$4,$6,5);}

          | GOTO Label {$$ = newexpnode8($2);}
          | Label ':' {$$ = newexpnode9($1);}
          | PARAM RtValue {$$ = newexpnode10($2);}
          | Identifier ASSIGN CALL Func {$$ = newexpnode11($1,$4);}
          | RETURN RtValue {SS = newexpnode12($2);}
          ;

Identifier: ID {$$ = newidnode(tokenString);}
          ;

Num: NUMBER {$$ = newnumnode(tokenval);}
   ;

label: LABEL {$$ = newlabnode(tokenString);}
     ;

Func: FUNC {$$ = newfuncnode(tokenString);}
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
    yyparse();
    PrintTree(savedTree,0);
    return 0;
}
