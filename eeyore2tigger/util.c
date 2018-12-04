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

Treenode *newfuncdefnode(Treenode *fu,Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = FuncDefK;
    strcpy(t->attr.name,fu->attr.name);
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newrtvl(Treenode *x,int type)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = RtK;
    if(type == 0)
    {
        t->speckind.rtvkind = VarK;
        t->attr.name = (char *)malloc(MAXTOKENLEN);
        strcpy(t->attr.name,x->attr.name);
    }
    else if(type == 1)
    {
        t->speckind.rtvkind = NumberK;
        t->attr.val = x->attr.val;
    }
    return t;
}

Treenode *newexpnode1(Treenode *c0,Treenode *c1,Treenode *c2,int type)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = TwOpK;
    if(type <= 4)t->twop = CalOpK;
    else t->twop = LogOpK;
    t->child[0] = c0;
    t->child[1] = c1;
    t->child[2] = c2;
    if(type == 0)t->attr.calop = AddK;
    else if(type == 1)t->attr.calop = SubK;
    else if(type == 2)t->attr.calop = MulK;
    else if(type == 3)t->attr.calop = DivK;
    else if(type == 4)t->attr.calop = ModK;
    else if(type == 5)t->attr.logop = AndK;
    else if(type == 6)t->attr.logop = OrK;
    else if(type == 7)t->attr.logop = SmK;
    else if(type == 8)t->attr.logop = EqK;
    else if(type == 9)t->attr.logop = GrK;
    else if(type == 10)t->attr.logop = UeqK;
    return t;
}

Treenode *newexpnode2(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = NotK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexpnode3(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = MinusK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexpnode4(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = SSK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexpnode5(Treenode *c0,Treenode *c1,Treenode *c2)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = ASK;
    t->child[0] = c0;
    t->child[1] = c1;
    t->child[2] = c2;
    return t;
}

Treenode *newexpnode6(Treenode *c0,Treenode *c1,Treenode *c2)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = SAK;
    t->child[0] = c0;
    t->child[1] = c1;
    t->child[2] = c2;
    return t;
}

Treenode *newexpnode7(Treenode *c0,Treenode *c1,Treenode *c2,int type)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = IFK;
    t->child[0] = c0;
    t->child[1] = c1;
    t->child[2] = c2;
    if(type == 0)t->attr.logop = AndK;
    else if(type == 1)t->attr.logop = OrK;
    else if(type == 2)t->attr.logop = SmK;
    else if(type == 3)t->attr.logop = EqK;
    else if(type == 4)t->attr.logop = GrK;
    else if(type == 5)t->attr.logop = UeqK;
    return t;
}

Treenode *newexpnode8(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = GotoK;
    t->child[0] = c0;
    return t;
}

Treenode *newexpnode9(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = LabelK;
    t->child[0] = c0;
    return t;
}

Treenode *newexpnode10(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = ParaK;
    t->child[0] = c0;
    return t;
}

Treenode *newexpnode11(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = CallK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexpnode12(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = ExpK;
    t->speckind.exp = RetK;
    t->child[0] = c0;
    return t;
}

Treenode *newidnode(char *name)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = IdK;
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    strcpy(t->attr.name,name);
    return t;
}

Treenode *newnumnode(int val)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = NumK;
    t->attr.val = val;
    return t;
}

Treenode *newlabnode(char *name)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = LabK;
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    strcpy(t->attr.name,name);
    return t;
}

Treenode *newfuncnode(char *name)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    t->nodekind = FunK;
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    strcpy(t->attr.name,name);
    return t;
}



void Printree(Treenode *root,int dep)
{
    while(root!=NULL)
    {
        for(int i=0;i<dep;i++)printf("    ");
        if(root->nodekind == VarDefK)
        {
            printf("Varient Define:");
            printf("%s ",root->attr.name);
            if (root->arrnum!=0)printf("%d",root->arrnum);
            printf("\n");
        }
        else if(root->nodekind == FuncDefK)
        {
            printf("Function Define:");
            printf("%s\n",root->attr.name);
        }
        else if(root->nodekind == RtK)
        {
            printf("Right Value:");
            if(root->speckind.rtvkind == VarK)printf("Varient:%s\n",root->attr.name);
            else printf("Interger:%d\n",root->attr.val);
        }
        else if(root->nodekind == ExpK)
        {
            printf("Expression:");
            int tmp = root->speckind.exp;
            if(tmp == TwOpK)
            {
                if(root->twop == CalOpK)printf("calculator opreation %d\n",root->attr.calop);
                else printf("logic operation %d\n",root->attr.logop);
            }
            else if(tmp == NotK)printf("Not expression\n");
            else if(tmp == MinusK)printf("Minus expression\n");
            else if(tmp == SSK)printf("Single with single valuing\n");
            else if(tmp == ASK)printf("Array with single valuing\n");
            else if(tmp == SAK)printf("Single with array valuing\n");
            else if(tmp == IFK)printf("If expression %d\n",root->attr.logop);
            else if(tmp == GotoK)printf("Goto expression\n");
            else if(tmp == LabelK)printf("Label expression\n");
            else if(tmp == ParaK)printf("Param expression\n");
            else if(tmp == CallK)printf("Call expression\n");
            else if(tmp == RetK)printf("Return expression\n");
        }
        else if(root->nodekind == IdK)
        {
            printf("IDENTIFIER:%s\n",root->attr.name);
        }
        else if(root->nodekind == NumK)
        {
            printf("Number:%d\n",root->attr.val);
        }
        else if(root->nodekind == LabK)
        {
            printf("Label:%s\n",root->attr.name);
        }
        else if(root->nodekind == FunK)
        {
            printf("Function:%s\n",root->attr.name);
        }

        for(int i=0;i<MAXCHILDREN;i++)
            if(root->child[i]!=NULL)Printree(root->child[i],dep+1);

        root = root->sibling;
    }
}
