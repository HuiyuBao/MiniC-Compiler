#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

#define MAXCHILDREN 10
#define MAXTOKENLEN 40

typedef int TokenType;

typedef enum{VarDefK,VarDeclK,FuncDefK,
            FuncDeclK,StmtK,ExpK,IdntK} NodeKind;
typedef enum{BigStK,IfK,IfElseK,WhileK
            ,AssignSK,AssignAK,RetK} StmtKind;
typedef enum{CalOpK,LogOpK,AridK,ConstK,IdK,
            NotK,MinusK,CallK} ExpKind;

typedef enum{Interger,Array}ExpType;

typedef enum{AddK,SubK,MulK,DivK,ModK}CalKind;
typedef enum{AndK,OrK,SmK,EqK,GrK,UeqK}LogKind;

typedef struct treenode
{
    struct treenode *child[MAXCHILDREN];
    struct treenode *sibling;
    int lineno;
    NodeKind nodekind;
    union{StmtKind stmt;ExpKind exp;}kind;
    union{CalKind calop;
          LogKind logop;
          int val;
          char *name;}attr;
    int arrnum; // 0 if sing var; else if arr
    ExpType type;
    string tmpvarname; // for the expression
    treenode()
    {
        for(int i=0;i<MAXCHILDREN;i++)child[i] = NULL;
        sibling = NULL;
    }
}Treenode;

typedef struct VALI
{
    int paracnt;
    ExpType patype[20];
    VALI()
    {
        paracnt = 0;
        memset(patype,0,sizeof(patype));
    }
    bool operator == (const VALI &o)const
    {
        if(paracnt != o.paracnt)return 0;
        for(int i=0;i<paracnt;i++)
            if(patype[i] != o.patype[i])return 0;
        return 1;
    }
}vali;

static map<string,vali>masterfunc;// record the function parameter in master branch

typedef struct environment
{
    struct environment *pre;
    map<string,string>symTable;
    map<string,int>symClass; // 0 for variable 1 for array
    map<string,int>delList; // 0 not define 1 define    for function
    map<string,string>funcPara;
    map<string,int>paraClass;// 0 for variable 1 for array
    int paracnt;
    int varcnt;
    environment(struct environment *_pre = NULL)
    {
        pre = _pre;
        varcnt = 0;
        paracnt = 0;
    }
}Env;

#endif
