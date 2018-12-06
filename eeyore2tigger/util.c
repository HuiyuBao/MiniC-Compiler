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
    int lineno;

    while(t!=NULL)
    {
        if(t->nodekind == FuncDefK)
        {
            Treenode *tmp = t->child[1];
            lineno = 0;
            while(tmp!=NULL)
            {
                tmp->numinfun = ++lineno;
                tmp = tmp->sibling;
            }
        }
        t = t->sibling;
    }

    t = root;
    while(t!=NULL)
    {
        if(t->nodekind == VarDefK)
        {
            symtab[string(t->attr.name)] = new Var;
            symtab[string(t->attr.name)]->no = glovarcnt;
            symtab[string(t->attr.name)]->tmpname = "v" + to_string(glovarcnt);
            revsear[glovarcnt] = string(t->attr.name);
            glovarcnt++;
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
                    symtab[string(tt->attr.name)] = new Var;
                    symtab[string(tt->attr.name)]->no = glovarcnt;
                    symtab[string(t->attr.name)]->tmpname = "v" + to_string(glovarcnt);
                    revsear[glovarcnt] = string(t->attr.name);
                    glovarcnt++;
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
                    symtab[name] = new Var;
                    symtab[name]->no = glovarcnt + totlocvarcnt;
                    symtab[name]->localno = t->arrnum;
                    symtab[name]->deftime = tt->numinfun;
                    revsear[glovarcnt + totlocvarcnt] = name;

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
    for(int i=0;i<8;i++)
    {
        string name = "p" + to_string(i);
        symtab[name] = new Var;
        int xno = glovarcnt + totlocvarcnt + i;
        revsear[xno] = name;
        symtab[name]->no = xno;
        symtab[name]->regid = 20 + i;
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
    Treenode *tmp = root;
    Treenode *t;
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
                            //printf("a\n");
                            if(t->succ[0]!=NULL)t->live |= t->succ[0]->live;
                            if(t->succ[1]!=NULL)t->live |= t->succ[1]->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == RetK)
                        {
                            //printf("b\n");
                            t->live = t->sibling->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == TwOpK)
                        {
                            //printf("c\n");
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == NotK || t->speckind.exp == MinusK || t->speckind.exp == SSK)
                        {
                            //printf("d\n");
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == ASK)
                        {
                            //printf("e\n");
                            t->live = t->sibling->live;
                            if(t->child[1]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[1]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == SAK)
                        {
                            //printf("f\n");
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                            if(t->child[2]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[2]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == ParaK)
                        {
                            //printf("g\n");
                            t->live = t->sibling->live;
                            if(t->child[0]->speckind.rtvkind == VarK)t->live.set(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else if(t->speckind.exp == CallK)
                        {
                            //printf("h\n");
                            t->live = t->sibling->live;
                            t->live.reset(symtab[(string)(t->child[0]->attr.name)]->no);
                        }
                        else if(t->succ[0]!=NULL)t->live = t->succ[0]->live;
                        else t->live = tmp;
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

    root = tmp;
    Treenode *be;
    while(root!=NULL)
    {
        if(root->nodekind == FuncDefK)
        {
            t = root->child[1];
            while(t!=NULL)
            {
                if(t->speckind.exp == GotoK && labpos[t->child[0]->attr.name]->numinfun < t->numinfun)
                {
                    be = labpos[t->child[0]->attr.name];
                    Treenode *thro = be, *throo;
                    while(thro!=t->sibling)
                    {
                        for(int i=0;i<glovarcnt;i++)
                            if(thro->live[i] == 1)
                            {
                                throo = be;
                                while(throo!=t->sibling)
                                {
                                    throo->live.set(i);
                                    throo = throo->sibling;
                                }
                            }
                        for(int i=glovarcnt;i<glovarcnt+totlocvarcnt;i++)
                            if(thro->live[i] == 1 && symtab[revsear[i]]->deftime < be->numinfun)
                            {
                                throo = be;
                                while(throo!=t->sibling)
                                {
                                    throo->live.set(i);
                                    throo = throo->sibling;
                                }
                            }
                        thro = thro->sibling;
                    }
                }
                t = t->sibling;
            }
        }
        root = root->sibling;
    }
}

string regname[] = {"x0","s0","s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11",
                      "t0","t1","t2","t3","t4","t5","t6","a0","a1","a2","a3","a4","a5","a6","a7"};
// x0=0  t3(16):array op  t4(17)&t5(18):const  t6(19):swap
//  No:1-16 and no-used a reg can be used


void genvardef(Treenode *root)
{
    Var *tmp = symtab[string(root->attr.name)];
    //tmp->tmpname = "v" + to_string(tmp->no);
    if(root->arrnum == 0)cout<<tmp->tmpname<<" = 0"<<endl;
    else cout<<tmp->tmpname<<" = malloc "<<root->arrnum<<endl;
}

Var vainrg[10000];
int vainrgnum;
int ifprint = 0;

void expire(int no,int real)
{
    int i;
    if(no == -1)return ;
    if(Reg[no].varsto == -1)return ;
    for(i=0;i<vainrgnum;i++)
        if(vainrg[i].regid == no)break;
        //printf("%d ",vainrg[i].regid);
    //printf("something %d %d %d %d\n",i,no,vainrg[i].regid,vainrg[i].no);
    if(vainrg[i].no < glovarcnt)
    {
        if(ifprint)cout<<endl<<"expire reg:"<<regname[no]<<" var:"<<revsear[vainrg[i].no]<<endl;
        cout<<"t6"<<" = "<<regname[no]<<endl;
        cout<<"load v"<<vainrg[i].no<<" "<<regname[no]<<endl;
        cout<<"loadaddr v"<<vainrg[i].no<<" t3"<<endl;
        cout<<"t3[0] = t6"<<endl;
        if(ifprint)cout<<endl;
    }
    else
    {
        if(ifprint)cout<<endl<<"expire reg:"<<regname[no]<<" var:"<<revsear[vainrg[i].no]<<endl;
        cout<<"t6 = "<<regname[no]<<endl;
        cout<<"load "<<vainrg[i].localno<<" "<<regname[no]<<endl;
        cout<<"store t6 "<<vainrg[i].localno<<endl;
        if(ifprint)cout<<endl;
    }
    if(real == 1)
    {
        Var *tmp = symtab[revsear[vainrg[i].no]];
        tmp->regid = -1;
        Reg[no].varsto = -1;
        Reg[no].wherereg = -1;
        vainrg[i].regid = -1;
        vainrg[i].edtm = -1;
    }
}

void setalloc(Treenode *root,Var *vari,int no,string funcname)
{
    int i;
    if(vari->no < glovarcnt)
    {
        if(ifprint)cout<<endl<<"setalloc "<<no<<" reg:"<<regname[no]<<" var:"<<revsear[vari->no]<<endl;
        cout<<"t6"<<" = "<<regname[no]<<endl;
        cout<<"load v"<<vari->no<<" "<<regname[no]<<endl;
        cout<<"loadaddr v"<<vari->no<<" t3"<<endl;
        cout<<"t3[0] = t6"<<endl;
        if(ifprint)cout<<endl;
    }
    else
    {
        if(ifprint)cout<<endl<<"setalloc "<<no<<" reg:"<<regname[no]<<" var:"<<revsear[vari->no]<<endl;
        cout<<"t6"<<" = "<<regname[no]<<endl;
        cout<<"load "<<vari->localno<<" "<<regname[no]<<endl;
        cout<<"store t6 "<<vari->localno<<endl;
        if(ifprint)cout<<endl;
    }
    vari->regid = no;
    //printf("give value here : %d %d\n",vari->regid,vari->no);
    Reg[no].varsto = vari->no;
    Reg[no].wherereg = vari->no;

    int nowline = root->numinfun;
    Var tmp = *vari;

    while(root->sibling != NULL && (root->live[vari->no] == 1 || root->sibling->live[vari->no] == 1))
          root = root->sibling;
    if(root->live[vari->no] == 0)tmp.edtm = root->numinfun - 1;
    else tmp.edtm = root->numinfun;
    tmp.funcname = funcname;
    vainrg[vainrgnum++] = tmp;
    //printf("the value of i is %d\n",i);
}

bool cmp(Var a, Var b)
{
    return a.edtm > b.edtm;
}

int linearscan()
{
    sort(vainrg,vainrg+vainrgnum,cmp);
    /*
    for(int i=0;i<REGNUM;i++)
    {
        printf("aaaaa %d %d ",vainrg[i].regid,vainrg[i].edtm);
        cout<<revsear[vainrg[i].no]<<endl;;
    }
    */
    //cout<<"aaaaaa "<<vainrg[0].regid<<" "<<vainrg[0].edtm;
    return vainrg[0].regid;
}

int regallo(Treenode *root,Var *vari,string funcname)
{
    int i,j;
    if(vari->regid != -1)return vari->regid;
    int order[REGNUM] = {13,14,15,1,2,3,4,5,6,7,8,9,10,11,12,0,16,17,18,19,20,21,22,23,24,25,26,27};
    for(j=0;j<REGNUM;j++)
    {
        i = order[j];
        if(Reg[i].useable == 0)continue;
        if(Reg[i].varsto!=-1 && root->live[Reg[i].varsto] == 0)
            expire(i,1);
        if(Reg[i].varsto == -1)
        {
            setalloc(root,vari,i,funcname);
            return i;
        }
    }
    /*
    for(j=0;j<REGNUM;j++)
    {
        i = order[j];
        if(Reg[i].varsto != -1)
            if(root->live[Reg[i].varsto] == 0)
            {
                expire(i,1);
                setalloc(root,vari,i,funcname);
                return i;
            }
    }
    */
    i = linearscan();
    expire(i,1);
    setalloc(root,vari,i,funcname);
    return i;
}

void genexp1(Treenode *root,string funcname)
{
    int rg1,rg2,rg;
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[1]->attr.val<<endl;
    }
    if(root->child[2]->speckind.rtvkind == VarK)
    {
        string name = root->child[2]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg2 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg2 = 18;
        cout<<"t5 = "<<root->child[2]->attr.val<<endl;
    }
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = "<<regname[rg1];
    if(root->twop == CalOpK)
    {
        int ttt = root->attr.calop;
        if(ttt == AddK)cout<<" + ";
        else if(ttt == SubK)cout<<" - ";
        else if(ttt == MulK)cout<<" * ";
        else if(ttt == DivK)cout<<" / ";
        else cout<<" % ";
    }
    else
    {
        int ttt = root->attr.logop;
        if(ttt == AndK)cout<<" && ";
        else if(ttt == OrK)cout<<" || ";
        else if(ttt == SmK)cout<<" < ";
        else if(ttt == EqK)cout<<" == ";
        else if(ttt == GrK)cout<<" > ";
        else cout<<" != ";
    }
    cout<<regname[rg2]<<endl;
}

void genexp2(Treenode *root,string funcname)
{
    int rg,rg1;
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[1]->attr.val<<endl;
    }
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = !"<<regname[rg1]<<endl;
}

void genexp3(Treenode *root,string funcname)
{
    int rg,rg1;
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[1]->attr.val<<endl;
    }
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = -"<<regname[rg1]<<endl;
}

void genexp4(Treenode *root,string funcname)
{
    int rg,rg1;
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[1]->attr.val<<endl;
    }
    //cout<<symtab[string(root->child[0]->attr.name)]->no<<endl;;
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = "<<regname[rg1]<<endl;
}

void genexp5(Treenode *root,string funcname)
{
    int rg1,rg2;
    cout<<"loadaddr "<<symtab[string(root->child[0]->attr.name)]->tmpname<<" t3"<<endl;
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[1]->attr.val<<endl;
    }
    cout<<"t3 = t3 + "<<regname[rg1]<<endl;
    if(root->child[2]->speckind.rtvkind == VarK)
    {
        string name = root->child[2]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg2 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg2 = 18;
        cout<<"t5 = "<<root->child[2]->attr.val<<endl;
    }
    cout<<"t3[0] = "<<regname[rg2]<<endl;
}

void genexp6(Treenode *root,string funcname)
{
    int rg,rg2;
    cout<<"loadaddr "<<symtab[string(root->child[1]->attr.name)]->tmpname<<" t3"<<endl;
    if(root->child[2]->speckind.rtvkind == VarK)
    {
        string name = root->child[2]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg2 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg2 = 18;
        cout<<"t5 = "<<root->child[2]->attr.val<<endl;
    }
    cout<<"t3 = t3 + "<<regname[rg2]<<endl;
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = t3[0]"<<endl;
}

void genexp7(Treenode *root,string funcname)
{
    int rg1,rg2;
    if(root->child[0]->speckind.rtvkind == VarK)
    {
        string name = root->child[0]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[0]->attr.val<<endl;
    }
    if(root->child[1]->speckind.rtvkind == VarK)
    {
        string name = root->child[1]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg2 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg2 = 18;
        cout<<"t5 = "<<root->child[1]->attr.val<<endl;
    }
    cout<<"if "<<regname[rg1];

    int ttt = root->attr.logop;
    if(ttt == AndK)cout<<" && ";
    else if(ttt == OrK)cout<<" || ";
    else if(ttt == SmK)cout<<" < ";
    else if(ttt == EqK)cout<<" == ";
    else if(ttt == GrK)cout<<" > ";
    else cout<<" != ";

    cout<<regname[rg2]<<" goto "<<root->child[2]->attr.name<<endl;
}

void genexp8(Treenode *root,string funcname)
{
    /*
    for(int i=0;i<vainrgnum;i++)
        if(vainrg[i].funcname == funcname)
            expire(vainrg[i].regid,1);
    */
    cout<<"goto "<<root->child[0]->attr.name<<endl;
}

void genexp9(Treenode *root,string funcname)
{
    cout<<root->child[0]->attr.name<<":"<<endl;
    /*
    for(int i=0;i<vainrgnum;i++)
        if(vainrg[i].funcname == funcname)
            expire(vainrg[i].regid,1);
    */
}

void genexp10(Treenode *root,int pnum,string funcname)
{
    int rg1;
    if(root->child[0]->speckind.rtvkind == VarK)
    {
        string name = root->child[0]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[0]->attr.val<<endl;
    }
    cout<<regname[19+pnum]<<" = "<<regname[rg1]<<endl;
}

void genexp11(Treenode *root,string funcname)
{
    int rg;
    /*
    for(int i=0;i<vainrgnum;i++)
        if(vainrg[i].funcname == funcname)
            expire(vainrg[i].regid,1);
    */
    cout<<"call "<<root->child[1]->attr.name<<endl;
    rg = regallo(root,symtab[string(root->child[0]->attr.name)],funcname);
    cout<<regname[rg]<<" = a0"<<endl;
}

void genexp12(Treenode *root,string funcname)
{
    int rg1;
    if(root->child[0]->speckind.rtvkind == VarK)
    {
        string name = root->child[0]->attr.name;
        //if(symtab.count(name)>0 && symtab[name]->regid!=-1)
            //expire(symtab[name]->regid,1);
        rg1 = regallo(root,symtab[name],funcname);
    }
    else
    {
        rg1 = 17;
        cout<<"t4 = "<<root->child[0]->attr.val<<endl;
    }
    cout<<"a0 = "<<regname[rg1]<<endl;
    if(root->sibling == NULL)
    {
        for(int i=0;i<vainrgnum;i++)
            if(vainrg[i].funcname == funcname)
                expire(vainrg[i].regid,1);
    }
    else
    {
        for(int i=0;i<vainrgnum;i++)
            if(vainrg[i].funcname == funcname)
                expire(vainrg[i].regid,0);
    }
    cout<<"return"<<endl;
}

void genexp(Treenode *root,string funcname)
{
    int pnum = 0;
    while(root!=NULL)
    {
        if(root->nodekind == ExpK)
        {
            if(root->speckind.exp == TwOpK)genexp1(root,funcname);
            else if(root->speckind.exp == NotK)genexp2(root,funcname);
            else if(root->speckind.exp == MinusK)genexp3(root,funcname);
            else if(root->speckind.exp == SSK)genexp4(root,funcname);
            else if(root->speckind.exp == ASK)genexp5(root,funcname);
            else if(root->speckind.exp == SAK)genexp6(root,funcname);
            else if(root->speckind.exp == IFK)genexp7(root,funcname);
            else if(root->speckind.exp == GotoK)genexp8(root,funcname);
            else if(root->speckind.exp == LabelK)genexp9(root,funcname);
            else if(root->speckind.exp == ParaK)
            {
                pnum++;
                genexp10(root,pnum,funcname);
            }
            else if(root->speckind.exp == CallK)
            {
                pnum = 0;
                genexp11(root,funcname);
            }
            else if(root->speckind.exp == RetK)genexp12(root,funcname);
            /*
            if(root->speckind.exp != RetK)
            {
                for(int i=0;i<vainrgnum;i++)
                    if(vainrg[i].funcname == funcname)
                        expire(vainrg[i].regid,1);
            }
            */
        }
        root = root->sibling;
    }
}

void genfundef(Treenode *root)
{
    cout<<root->attr.name<<" ["<<root->child[0]->attr.val<<"]["<<root->arrnum<<"]"<<endl;

    for(int i=0;i<REGNUM;i++)Reg[i].useable = 1;
    Reg[0].useable = 0;
    for(int i=-4;i<8;i++)Reg[20+i].useable = 0;

    genexp(root->child[1],(string)(root->attr.name));
    cout<<"end "<<root->attr.name<<endl;
}

void Generate(Treenode *root)
{
    Treenode *tmp = root;
    while(root!=NULL)
    {
        if(root->nodekind == VarDefK)genvardef(root);

        else
        {
            Treenode *t = root->child[1];
            while(t!=NULL)
            {
                if(t->nodekind == VarDefK && t->arrnum != 0)genvardef(t);
                t = t->sibling;
            }
        }
        root = root->sibling;
    }

    root = tmp;
    while(root!=NULL)
    {
        if(root->nodekind == FuncDefK)genfundef(root);
        root = root->sibling;
    }

}


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
        if (root->arrnum!=0)printf("%d",root->arrnum);
        printf("\n");
        cout<<"liveness: "<<root->live<<endl;
    }
    else if(root->nodekind == FuncDefK)
    {
        printf("Function Define: ");
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

        /*
        if(root->nodekind == ExpK || root->nodekind == VarDefK)
        {
            printf("{\nsucc 1:\n");Printsingle(root->succ[0]);
            printf("succ 2:\n");Printsingle(root->succ[1]);printf("}\n");
        }
        */
        root = root->sibling;
    }
}
