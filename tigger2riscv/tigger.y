%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define YYSTYPE string

extern string tokenString;
extern void yyerror(char *message);
extern int yylex();

int stack_size;
int failnum = 0;
%}

%left OR
%left AND
%left EQ NEQ
%left GR SM
%left ADD SUB
%left MUL DIV MOD
%right NOT MINUS

%token REG VAR LABEL FUNC NUMBER
%token END IF GOTO CALL LOAD
%token LOADADDR STORE RETURN MALLOC

%%

Program: Program FuncDefn
       | Program VarDefn
       |
       ;

VarDefn: Variable '=' num
        {
            printf("    .global %s\n",$1.c_str());
            printf("    .section .sdata\n");
            printf("    .align 2\n");
            printf("    .type %s, @object\n",$1.c_str());
            printf("    .size %s, 4\n",$1.c_str());
            printf("%s:\n",$1.c_str());
            printf("    .word 0\n");
        }
       | Variable '=' MALLOC num
        {
            printf("    .comm %s,%d,4\n",$1.c_str(),stoi($4)*4);
        }
       ;

FuncDefn: Function '[' num ']' '[' num ']'
        {
            stack_size = (stoi($6) / 4 + 1) * 16;
            printf("    .text\n");
            printf("    .align 2\n");
            printf("    .global %s\n",$1.c_str());
            printf("    .type %s,@function\n",$1.c_str());
            printf("%s:\n",$1.c_str());
            printf("    add sp,sp,-%d\n",stack_size);
            printf("    sw ra,%d(sp)\n",stack_size-4);
        }
        FuncBody
        END Function
        {
            printf("    .size %s,.-%s\n",$1.c_str(),$1.c_str());
            stack_size = 0;
        }
        ;

FuncBody: FuncBody Expression
        | Expression
        ;

Expression: reg '=' reg ADD reg
            {printf("    add %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg SUB reg
            {printf("    sub %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg MUL reg
            {printf("    mul %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg DIV reg
            {printf("    div %s,%s,%s\"n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg MOD reg
            {printf("    rem %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg SM reg
            {printf("    slt %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg GR reg
            {printf("    sgt %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg AND reg
            {printf("    seqz %s,%s\n",$1.c_str(),$3.c_str());
             printf("    add %s,%s,-1\n",$1.c_str(),$1.c_str());
             printf("    and %s,%s,%s\n",$1.c_str(),$1.c_str(),$5.c_str());
             printf("    snez %s,%s\n",$1.c_str(),$1.c_str());}
          | reg '=' reg OR reg
            {printf("    or %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());
             printf("    snez %s,%s\n",$1.c_str(),$1.c_str());}
          | reg '=' reg NEQ reg
            {printf("    xor %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());
             printf("    snez %s,%s\n",$1.c_str(),$1.c_str());}
          | reg '=' reg EQ reg
            {printf("    xor %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());
             printf("    seqz %s,%s\n",$1.c_str(),$1.c_str());}
          | reg '=' reg ADD num
            {printf("    add %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' reg SM num
            {printf("    slti %s,%s,%s\n",$1.c_str(),$3.c_str(),$5.c_str());}
          | reg '=' SUB reg %prec MINUS
            {printf("    sub %s,x0,%s\n",$1.c_str(),$4.c_str());}
          | reg '=' NOT reg
            {printf("    seqz %s,%s\n",$1.c_str(),$4.c_str());}
          | reg '=' reg
            {printf("    mv %s,%s\n",$1.c_str(),$3.c_str());}
          | reg '=' num
            {printf("    li %s,%s\n",$1.c_str(),$3.c_str());}
          | reg '[' num ']' '=' reg
            {printf("    sw %s,%s(%s)\n",$6.c_str(),$3.c_str(),$1.c_str());}
          | reg '=' reg '[' num ']'
            {printf("    lw %s,%s(%s)\n",$1.c_str(),$5.c_str(),$3.c_str());}
          | IF reg SM reg GOTO label
            {printf("    blt %s,%s,.%s\n",$2.c_str(),$4.c_str(),$6.c_str());}
          | IF reg GR reg GOTO label
            {printf("    bgt %s,%s,.%s\n",$2.c_str(),$4.c_str(),$6.c_str());}
          | IF reg NEQ reg GOTO label
            {printf("    bne %s,%s,.%s\n",$2.c_str(),$4.c_str(),$6.c_str());}
          | IF reg EQ reg GOTO label
            {printf("    beq %s,%s,.%s\n",$2.c_str(),$4.c_str(),$6.c_str());}
          | IF reg OR reg GOTO label
            {printf("    bne %s,x0,%s\n",$2.c_str(),$6.c_str());
             printf("    bne %s,x0,%s\n",$2.c_str(),$6.c_str());}
          | IF reg AND reg GOTO label
            {printf("    beq %s,x0,.fail%d\n",$2.c_str(),failnum);
             printf("    beq %s,x0,%s\n",$2.c_str(),$6.c_str());
             printf(".fail%d\n",failnum++);}
          | GOTO label
            {printf("    j .%s\n",$2.c_str());}
          | label ':'
            {printf(".%s:\n",$1.c_str());}
          | CALL Function
            {printf("    call %s\n",$2.c_str());}
          | STORE reg num
            {printf("    sw %s,%d(sp)\n",$2.c_str(),stoi($3)*4);}
          | LOAD num reg
            {printf("    lw %s,%d(sp)\n",$3.c_str(),stoi($2)*4);}
          | LOAD Variable reg
            {printf("    lui %s,%%hi(%s)\n",$3.c_str(),$2.c_str());
             printf("    lw %s,%%lo(%s)(%s)\n",$3.c_str(),$2.c_str(),$3.c_str());}
          | LOADADDR num reg
            {printf("    add %s,sp,%d\n",$3.c_str(),stoi($2)*4);}
          | LOADADDR Variable reg
            {printf("    lui %s,%%hi(%s)\n",$3.c_str(),$2.c_str());
             printf("    add %s,%s,%%lo(%s)\n",$3.c_str(),$3.c_str(),$2.c_str());}
          | RETURN
            {printf("    lw ra,%d(sp)\n",stack_size-4);
             printf("    add sp,sp,%d\n",stack_size);
             printf("    jr ra\n");}
          ;

reg: REG {$$ = tokenString;}
    ;

Variable: VAR {$$ = tokenString;}
        ;

Function: FUNC {$$ = tokenString;}
        ;

label: LABEL {$$ = tokenString;}
     ;

num: NUMBER {$$ = tokenString;}
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
    return 0;
}
