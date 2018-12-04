#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>
#include <map>
#include <bitset>
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




void genelabpos(Treenode *root)
{
    while(root!=NULL)
    {
        if(root->nodekind == ExpK && root->speckind.exp == LabelK)
        {
            string lname = (string)(root->child[0]->attr.name);
            labpos[lname] = root;
        }
        for(int i=0;i<MAXCHILDREN;i++)
            if(root->child[i]!=NULL)genelabpos(root->child[i]);
        root = root->sibling;
    }
}


void genesucc(Treenode *root)
{
    while(root!=NULL)
    {
        if(root->nodekind == VarDefK)
        {
            root = root->sibling;
            continue;
        }
        else
        {
            Treenode *t = root->child[1];
            while(t!=NULL)
            {
                if(t->nodekind == VarDefK)t->succ[0] = t->sibling;
                else if(t->speckind.exp == IFK)
                {
                    t->succ[0] = labpos[(string)(t->child[2]->attr.name)];
                    t->succ[1] = t->sibling;
                }
                else if(t->speckind.exp == GotoK)
                {
                    t->succ[0] = labpos[(string)(t->child[0]->attr.name)];
                }
                else if(t->speckind.exp != RetK)t->succ[0] = t->sibling;

                t = t->sibling;
            }
        }
        root = root->sibling;
    }
}

int glovarcnt;
int totlocvarcnt;
int maxparacnt;

void genesym(Treenode *root)
{
    Treenode *t = root;
    while(t!=NULL)
    {
        if(t->nodekind == VarDefK)
        {
            symtab[string(t->attr.name)] = (Var *)malloc(sizeof(var));
            symtab[string(t->attr.name)]->no = glovarcnt++;
        }
        t = t->sibling;
    }

    t = root;
    while(t!=NULL)
    {
        if(t->nodekind == FuncDefK)
        {
            Treenode *tt = t->child[1];
            while(tt!=NULL)
            {
                if(tt->nodekind == VarDefK && tt->arrnum != 0)
                {
                    symtab[string(tt->attr.name)] = (Var *)malloc(sizeof(var));
                    symtab[string(tt->attr.name)]->no = glovarcnt++;
                }
                tt = tt->sibling;
            }
        }
        t = t->sibling;
    }

    t = root;
    while(t!=NULL)
    {
        if(t->nodekind == FuncDefK)
        {
            if(t->child[0]->attr.val > maxparacnt)
                maxparacnt = t->child[0]->attr.val;
            Treenode *tt = t->child[1];
            while(tt!=NULL)
            {
                if(tt->nodekind == VarDefK && tt->arrnum == 0)
                {
                    string name = (string)(tt->attr.name);
                    symtab[name] = (Var *)malloc(sizeof(var));
                    symtab[name]->no = glovarcnt + totlocvarcnt;
                    symtab[name]->localno = t->arrnum;

                    totlocvarcnt++;
                    t->arrnum ++;

                    //cout<<name<<" "<<symtab[name]->no<<" "<<symtab[name]->localno<<endl;
                }
                tt = tt->sibling;
            }
        }
        //cout<<"aaaa"<<t->arrnum<<endl;
        t = t->sibling;
    }
}

void init(Treenode *root)
{
    genelabpos(root);
    genesucc(root);
    genesym(root);
}

void liveness(Treenode *root)
{
    Treenode *t;
    int tttttt;
    while(root!=NULL)
    {
        if(root->nodekind == FuncDefK)
        {
            t = root->child[1];

            Treenode *begin = (Treenode *)malloc(sizeof(Treenode));
            Treenode *end = (Treenode *)malloc(sizeof(Treenode));
            begin->sibling = t;
            t->presibling = begin;
            Treenode *pret = t;
            t = t->sibling;
            while(t!=NULL)
            {
                t->presibling = pret;
                pret = t;
                t = t->sibling;
            }
            pret->sibling = end;
            end->presibling = pret;
            // generate presibling for liveness


            bool change = true;
            while(change == true)
            {
                change = false;
                t = end->presibling;
                while(t != begin)
                {
                    bitset<BITLENGTH>tmp = t->live;
                    if(t->nodekind == VarDefK)
                    {
                        t->live = t->sibling->live;
                        t->live.reset(symtab[(string)(t->attr.name)]->no);
                    }
                    else
                    {
                        if(t->speckind.exp == IFK)
                        {
                            t->live.reset();
                            if(t->succ[0]!=NULL)t->live |= t->succ[0]->live;
                            if(t->succ[1]!=NULL)t->live |= t->succ[1]->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == RetK)
                        {
                            t->live = t->sibling->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == TwOpK)
                        {
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == NotK || t->speckind.exp == MinusK || t->speckind.exp == SSK)
                        {
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == ASK)
                        {
                            t->live = t->sibling->live;
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == SAK)
                        {
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == ParaK)
                        {
                            t->live = t->sibling->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == CallK)
                        {
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else t->live = t->sibling->live;
                    }
                    if(t->live != tmp)change = true;
                    t = t->presibling;
                }
            }
            begin->sibling->presibling = NULL;
            end->presibling->sibling = NULL;
            free(begin); free(end);
        }
        root = root->sibling;
    }
}

/*
void Printsingle(Treenode *root)
{
    if(root == NULL)
    {
        printf("There is nothing\n");
        return ;
    }
    if(root->nodekind == VarDefK)
    {
        printf("Varient Define:");
        printf("%s ",root->attr.name);
        if (root->arrnum!=0)printf("%d",root->arrnum);\
        printf("\n");
        cout<<"liveness: "<<root->live<<endl;
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
        //else if(tmp == LabelK)printf("Label expression:%s %d\n",root->child[0]->attr.name,root->sibling->nodekind);
        else if(tmp == ParaK)printf("Param expression\n");
        else if(tmp == CallK)printf("Call expression\n");
        else if(tmp == RetK)printf("Return expression\n");
        cout<<"liveness: "<<root->live<<endl;
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
}

void Printree(Treenode *root,int dep)
{
    while(root!=NULL)
    {
        for(int i=0;i<dep;i++)printf("    ");
        Printsingle(root);

        for(int i=0;i<MAXCHILDREN;i++)
            if(root->child[i]!=NULL)Printree(root->child[i],dep+1);


        if(root->nodekind == ExpK || root->nodekind == VarDefK)
        {
            printf("{\nsucc 1:\n");Printsingle(root->succ[0]);
            printf("succ 2:\n");Printsingle(root->succ[1]);printf("}\n");
        }

        root = root->sibling;
    }
}
*/
