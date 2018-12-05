#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <bitset>
using namespace std;

#define MAXCHILDREN 10
#define MAXTOKENLEN 40
#define BITLENGTH 100
#define REGNUM 28

typedef int TokenType;

typedef enum{VarDefK,FuncDefK,RtK,ExpK,
              IdK,NumK,LabK,FunK} NodeKind;
typedef enum{TwOpK,NotK,MinusK,SSK,ASK,SAK,IFK,
              GotoK,LabelK,ParaK,CallK,RetK} ExpKind;
typedef enum{VarK,NumberK}RtVKind;
typedef enum{CalOpK,LogOpK}TwopKind;
typedef enum{AddK,SubK,MulK,DivK,ModK}CalKind;
typedef enum{AndK,OrK,SmK,EqK,GrK,UeqK}LogKind;


typedef struct treenode
{
    struct treenode *child[MAXCHILDREN];
    struct treenode *sibling;
    struct treenode *presibling;
    struct treenode *succ[4];
    bitset<BITLENGTH>live;
    int numinfun;
    NodeKind nodekind;
    union{
          RtVKind rtvkind;
          ExpKind exp;}speckind;
    TwopKind twop;
    union{CalKind calop;
          LogKind logop;
          int val;
          char *name;}attr;
    int arrnum; // 0 if sing var; else if arr
    // if node is a function define, arrnum is the num of local variable
    treenode()
    {
        for(int i=0;i<MAXCHILDREN;i++)child[i] = NULL;
        sibling = NULL;
        presibling = NULL;
        arrnum = 0;
        live.reset();
    }
}Treenode;

typedef struct var
{
    int no;
    int localno;// -1 if global varient
    int regid;// where is the varient
    string tmpname;
    int edtm;
    string funcname;
    var()
    {
        regid = -1;
        localno = -1;
        edtm = -1;
    }
}Var;

struct reg
{
    int varsto;// what varient the reg store
    int wherereg;// where is the reg num
    bool useable;
    reg()
    {
        varsto = -1;
        wherereg = -1;
    }
};

static reg Reg[REGNUM];

static map<string,Treenode *>labpos; // where is the label
static map<string,Var *>symtab; //
static string revsear[BITLENGTH];

/*
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
*/

#endif
