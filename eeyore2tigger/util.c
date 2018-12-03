#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>
#include <map>
#include "globals.h"
#include "util.h"
using namespace std;
extern int yylineno;
extern void yyerror(char *message);
extern Treenode *savedTree;

Treenode *newvardefnode(char *name,int arrsize)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = VarDefK;
    strcpy(t->attr.name,name);
    t->arrnum = arrsize;
    return t;
}

Treenode
