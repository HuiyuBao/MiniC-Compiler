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

void givelineno(Treenode *t)
{
    t->lineno = yylineno;
}

void sprlineno(char *message,int lineno)
{
    sprintf(message,"Error happens at line %d\n",lineno);
}

Treenode *newvardefnode(char *name,int arrsize)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->lineno = yylineno;
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = VarDefK;
    t->arrnum = arrsize;
    strcpy(t->attr.name,name);
    return t;
}

Treenode *newvardeclnode(char *name,int arrsize)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = VarDeclK;
    t->arrnum = arrsize;
    strcpy(t->attr.name,name);
    return t;
}

Treenode *newfuncdefnode(char *name,Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = FuncDefK;
    strcpy(t->attr.name,name);
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newfuncdeclnode(char *name,Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = FuncDeclK;
    strcpy(t->attr.name,name);
    t->child[0] = c0;
    return t;
}

Treenode *newstmtnode1(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = StmtK;
    t->kind.stmt = BigStK;
    t->child[0] = c0;
    return t;
}

Treenode *newstmtnode2(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = StmtK;
    t->kind.stmt = IfK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newstmtnode3(Treenode *c0,Treenode *c1,Treenode *c2)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = StmtK;
    t->kind.stmt = IfElseK;
    t->child[0] = c0;
    t->child[1] = c1;
    t->child[2] = c2;
    return t;
}

Treenode *newstmtnode4(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = StmtK;
    t->kind.stmt = WhileK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newstmtnode5(Treenode *tmp,Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = StmtK;
    t->kind.stmt = AssignSK;
    strcpy(t->attr.name,tmp->attr.name);
    t->child[0] = c0;
    return t;
}

Treenode *newstmtnode6(Treenode *tmp,Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = StmtK;
    t->kind.stmt = AssignAK;
    strcpy(t->attr.name,tmp->attr.name);
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newstmtnode7(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = StmtK;
    t->kind.stmt = RetK;
    t->child[0] = c0;
    return t;
}

Treenode *newexprnode1(Treenode *c0,Treenode *c1,int optmp)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = CalOpK;
    if(optmp == 0)t->attr.calop = AddK;
    else if(optmp == 1)t->attr.calop = SubK;
    else if(optmp == 2)t->attr.calop = MulK;
    else if(optmp == 3)t->attr.calop = DivK;
    else if(optmp == 4)t->attr.calop = ModK;
    //t->type = Interger;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexprnode2(Treenode *c0,Treenode *c1,int optmp)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = LogOpK;
    if(optmp == 0)t->attr.logop = AndK;
    else if(optmp == 1)t->attr.logop = OrK;
    else if(optmp == 2)t->attr.logop = SmK;
    else if(optmp == 3)t->attr.logop = EqK;
    else if(optmp == 4)t->attr.logop = GrK;
    else if(optmp == 5)t->attr.logop = UeqK;
    //t->type = Boolean;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexprnode3(Treenode *c0,Treenode *c1)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = AridK;
    t->child[0] = c0;
    t->child[1] = c1;
    return t;
}

Treenode *newexprnode4(int numtmp)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = ConstK;
    t->attr.val = numtmp;
    return t;
}

Treenode *newexprnode5(Treenode *tmp)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = ExpK;
    t->kind.exp = IdK;
    strcpy(t->attr.name,tmp->attr.name);
    return t;
}

Treenode *newexprnode6(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = NotK;
    t->child[0] = c0;
    return t;
}

Treenode *newexprnode7(Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->nodekind = ExpK;
    t->kind.exp = MinusK;
    t->child[0] = c0;
    return t;
}

Treenode *newexprnode8(Treenode *tmp,Treenode *c0)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = ExpK;
    t->kind.exp = CallK;
    strcpy(t->attr.name,tmp->attr.name);
    t->child[0] = c0;
    return t;
}

Treenode *newidntnode(char *name)
{
    Treenode *t = (Treenode *)malloc(sizeof(Treenode));
    givelineno(t);
    t->attr.name = (char *)malloc(MAXTOKENLEN);
    t->nodekind = IdntK;
    strcpy(t->attr.name,name);
    return t;
}




Env *nowenv;
int labelcnt = 0;
int realcnt = 0;
int tmpcnt = 0;

string findident(Treenode *ro)
{
    Env *t = nowenv;
    string name = (string)(ro->attr.name);
    while(t!=NULL)
    {
        if(t->symTable.find(name)!=t->symTable.end())
            return t->symTable[name];
        if(t->funcPara.find(name)!=t->funcPara.end())
            return t->funcPara[name];
        t = t->pre;
    }
    char *message;
    message = new char [100];
    sprlineno(message,ro->lineno);
    sprintf(message+strlen(message),"variable %s is not defined\n",ro->attr.name);
    yyerror(message);
    return NULL;
}

void findfuncident(Treenode *ro)
{
    Env *t = nowenv;
    string name = (string)(ro->attr.name);
    while(t!=NULL)
    {
        if(t->delList.find(name)!=t->delList.end())
            return ;
        t = t->pre;
    }
    char *message;
    message = new char [100];
    sprlineno(message,ro->lineno);
    sprintf(message+strlen(message),"function %s is not defined\n",ro->attr.name);
    yyerror(message);
}

int findidclass(Treenode *ro)
{
    Env *t = nowenv;
    string name = (string)(ro->attr.name);
    while(t!=NULL)
    {
        if(t->symTable.find(name)!=t->symTable.end())
            return t->symClass[name];
        if(t->funcPara.find(name)!=t->funcPara.end())
            return t->paraClass[name];
        t = t->pre;
    }
}

void genvardefn(Treenode *ro)
{
    if(nowenv->symTable.find(ro->attr.name)!=nowenv->symTable.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"variable %s has been defined\n",ro->attr.name);
        yyerror(message);
    }
    if(nowenv->funcPara.find(ro->attr.name)!=nowenv->funcPara.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"%s has been defined as a function\n",ro->attr.name);
        yyerror(message);
    }
    string name = "T" +  to_string(realcnt++);
    nowenv->symTable[ro->attr.name] = name;
    nowenv->symClass[ro->attr.name] = ro->arrnum == 0 ? 0 : 1;
    if(ro->arrnum == 0)cout<<"var "<<name<<endl;
    else cout<<"var "<<ro->arrnum*4<<" "<<name<<endl;
}

void genvarlist(char *funcname,int tmplineno,Treenode *ro)
{
    string name;
    vali tmp;
    while(ro != NULL)
    {
        name = "p" +  to_string(nowenv->paracnt++);
        nowenv->funcPara[ro->attr.name] = name;
        nowenv->paraClass[ro->attr.name] = ro->arrnum == 0 ? 0 :1;
        tmp.patype[tmp.paracnt++] = ro->arrnum == 0 ? Interger : Array;
        ro = ro->sibling;
    }
    if(masterfunc.find(funcname) == masterfunc.end())
    {
        masterfunc[funcname] = tmp;
    }
    else if(!(tmp == masterfunc[funcname]))
    {
        char *message;
        message = new char[100];
        sprlineno(message,tmplineno);
        sprintf(message+strlen(message),"The defination of function has some conflicts with something before");
        yyerror(message);
    }
}

void genfuncdefn(Treenode *ro)
{
    if(nowenv->symTable.find(ro->attr.name)!=nowenv->symTable.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"%s has been defined as a variable\n",ro->attr.name);
        yyerror(message);
    }
    if(nowenv->funcPara.find(ro->attr.name)!=nowenv->funcPara.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"function %s has been defined\n",ro->attr.name);
        yyerror(message);
    }
    nowenv->delList[ro->attr.name] = 1;

    nowenv = new Env(nowenv);
    genvarlist(ro->attr.name,ro->lineno,ro->child[0]);
    cout<<"f_"<<ro->attr.name<<" ["<<nowenv->paracnt<<"]"<<endl;
    genfuncbody(ro->child[1]);
    cout<<"end f_"<<ro->attr.name<<endl;
    nowenv = nowenv->pre;
}

void genfuncdecl(Treenode *ro)
{
    int tmplineno = ro->lineno;
    if(nowenv->symTable.find(ro->attr.name)!=nowenv->symTable.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"%s has been defined as a variable\n",ro->attr.name);
        yyerror(message);
    }
    if(nowenv->funcPara.find(ro->attr.name)!=nowenv->funcPara.end())
    {
        char *message;
        message = new char[100];
        sprlineno(message,ro->lineno);
        sprintf(message+strlen(message),"function %s has been defined\n",ro->attr.name);
        yyerror(message);
    }
    nowenv->delList[ro->attr.name] = 0;
    if(strcmp(ro->attr.name,"getint")==0) nowenv->delList[ro->attr.name] = 1;
    else if(strcmp(ro->attr.name,"putchar")==0)nowenv->delList[ro->attr.name] = 1;
    else if(strcmp(ro->attr.name,"putint")==0)nowenv->delList[ro->attr.name] = 1;
    else if(strcmp(ro->attr.name,"getchar")==0)nowenv->delList[ro->attr.name] = 1;

    vali tmp;
    Treenode *li = ro->child[0];
    while(li!=NULL)
    {
        tmp.patype[tmp.paracnt++] = li->arrnum == 0 ? Interger : Array;
        li = li->sibling;
    }
    if(masterfunc.find(ro->attr.name) == masterfunc.end())
    {
        masterfunc[ro->attr.name] = tmp;
    }
    else if(!(tmp == masterfunc[ro->attr.name]))
    {
        char *message;
        message = new char[100];
        sprlineno(message,tmplineno);
        sprintf(message+strlen(message),"The declartion of function has some conflicts with something before");
        yyerror(message);
    }
}

void genfuncbody(Treenode *ro)
{
    while(ro != NULL)
    {
        if(ro->nodekind == FuncDeclK)genfuncdecl(ro);
        else genstmt(ro);
        ro = ro->sibling;
    }
}

void genparalist(char *funcname,int tmplineno,Treenode *ro)
{
    int count = 0;
    vali tmp = masterfunc[funcname];
    while(ro != NULL)
    {
        if(count >= tmp.paracnt)break;
        if(findidclass(ro) == 0 && tmp.patype[count] == Array)
        {
            char *message;
            message = new char[100];
            sprlineno(message,ro->lineno);
            sprintf(message+strlen(message),"variable %s can't be converted as an array",ro->attr.name);
            yyerror(message);
        }
        if(findidclass(ro) == 1 && tmp.patype[count] == Interger)
        {
            char *message;
            message = new char[100];
            sprlineno(message,ro->lineno);
            sprintf(message+strlen(message),"array %s can't be converted as a interger",ro->attr.name);
            yyerror(message);
        }
        cout<<"param ";
        cout<<findident(ro)<<endl;
        ro = ro->sibling;
        count ++ ;
    }
    if(ro != NULL)
    {
        char *message;
        message = new char[100];
        sprlineno(message,tmplineno);
        sprintf(message+strlen(message),"too many parameters for function %s\n",funcname);
        yyerror(message);
    }
    if(count < tmp.paracnt)
    {
        char *message;
        message = new char[100];
        sprlineno(message,tmplineno);
        sprintf(message+strlen(message),"too few parameters for function %s\n",funcname);
        yyerror(message);
    }
}

void genexp(Treenode *ro)
{
    char op21[10][7]={" + "," - "," * "," / "," % "};
    char op22[10][7]={" && "," || "," < "," == "," > "," != "};
    switch(ro->kind.exp)
    {
        case CalOpK:
        {
            genexp(ro->child[0]);
            genexp(ro->child[1]);
            if(ro->child[0]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[0]->attr.name);
                yyerror(message);
            }
            if(ro->child[1]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[1]->attr.name);
                yyerror(message);
            }
            ro->type = Interger;
            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = "<<ro->child[0]->tmpvarname
                  <<op21[ro->attr.calop]<<ro->child[1]->tmpvarname<<endl;
        }
        break;
        case LogOpK:
        {
            genexp(ro->child[0]);
            genexp(ro->child[1]);
            if(ro->child[0]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[0]->attr.name);
                yyerror(message);
            }
            if(ro->child[1]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[1]->attr.name);
                yyerror(message);
            }
            ro->type = Interger;
            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = "<<ro->child[0]->tmpvarname
                  <<op22[ro->attr.logop]<<ro->child[1]->tmpvarname<<endl;
        }
        break;
        case AridK:
        {
            genexp(ro->child[0]);
            int cla = ro->child[0]->type;
            if(cla == Interger)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is not an array\n",ro->child[0]->attr.name);
                yyerror(message);
            }
            ro->type = Interger;
            genexp(ro->child[1]);
            string tmpvar = "t" + to_string(tmpcnt++);
            cout<<"var "<<tmpvar<<endl;
            cout<<tmpvar<<" = 4 * "<<ro->child[1]->tmpvarname<<endl;

            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = "<<ro->child[0]->tmpvarname
                <<" ["<<tmpvar<<"] "<<endl;
        }
        break;
        case ConstK:
        {
            ro->type = Interger;
            ro->tmpvarname =  to_string(ro->attr.val);
        }
        break;
        case IdK:
        {
            ro->tmpvarname = findident(ro);
            if(findidclass(ro)==0)ro->type = Interger;
            else ro->type = Array;
        }
        break;
        case NotK:
        {
            genexp(ro->child[0]);
            if(ro->child[0]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[0]->attr.name);
                yyerror(message);
            }
            ro->type = Interger;
            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = ! "<<ro->child[0]->tmpvarname<<endl;
        }
        break;
        case MinusK:
        {
            genexp(ro->child[0]);
            if(ro->child[0]->type == Array)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->child[0]->attr.name);
                yyerror(message);
            }
            ro->type = Interger;
            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = - "<<ro->child[0]->tmpvarname<<endl;
        }
        break;
        case CallK:
        {
            findfuncident(ro);
            genparalist(ro->attr.name,ro->lineno,ro->child[0]);
            ro->type = Interger;
            ro->tmpvarname = "t" +  to_string(tmpcnt++);
            cout<<"var "<<ro->tmpvarname<<endl;
            cout<<ro->tmpvarname<<" = "<<"call f_"<<ro->attr.name<<endl;
        }
        break;
    }
}

void genstmt(Treenode *ro)
{
    if(ro->nodekind == VarDefK)
    {
        genvardefn(ro);
        return ;
    }
    switch(ro->kind.stmt)
    {
        case BigStK:
        {
            nowenv = new Env(nowenv);
            Treenode *t = ro->child[0];
            while(t != NULL)
            {
                genstmt(t);
                t=t->sibling;
            }
            nowenv = nowenv->pre;
        }
        break;
        case IfK:
        {
            genexp(ro->child[0]);
            string tlabelname = "l" +  to_string(labelcnt++);
            cout<<"if "<<ro->child[0]->tmpvarname<<" == 0 goto "
                <<tlabelname<<endl;
            genstmt(ro->child[1]);
            cout<<tlabelname<<":"<<endl;
        }
        break;
        case IfElseK:
        {
            genexp(ro->child[0]);
            string tlabelname1 = "l" +  to_string(labelcnt++);
            string tlabelname2 = "l" +  to_string(labelcnt++);
            cout<<"if "<<ro->child[0]->tmpvarname<<" == 0 goto "
                <<tlabelname1<<endl;
            genstmt(ro->child[1]);
            cout<<"goto "<<tlabelname2<<endl;
            cout<<tlabelname1<<":"<<endl;
            genstmt(ro->child[2]);
            cout<<tlabelname2<<":"<<endl;
        }
        break;
        case WhileK:
        {
            string tlabelname1 = "l" +  to_string(labelcnt++);
            string tlabelname2 = "l" +  to_string(labelcnt++);
            cout<<tlabelname1<<":"<<endl;
            genexp(ro->child[0]);
            cout<<"if "<<ro->child[0]->tmpvarname<<" == 0 goto "
                <<tlabelname2<<endl;
            genstmt(ro->child[1]);
            cout<<"goto "<<tlabelname1<<endl;
            cout<<tlabelname2<<":"<<endl;
        }
        break;
        case AssignSK:
        {
            int cla = findidclass(ro);
            if(cla == 1)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is an array address\n",ro->attr.name);
                yyerror(message);
            }
            genexp(ro->child[0]);
            cout<<findident(ro)<<" = "<<ro->child[0]->tmpvarname<<endl;
        }
        break;
        case AssignAK:
        {
            int cla = findidclass(ro);
            if(cla == 0)
            {
                char *message;
                message = new char[100];
                sprlineno(message,ro->lineno);
                sprintf(message+strlen(message),"%s is not an array\n",ro->attr.name);
                yyerror(message);
            }
            genexp(ro->child[0]);
            genexp(ro->child[1]);
            string tmpvar = "t" +  to_string(tmpcnt++);
            cout<<"var "<<tmpvar<<endl;
            cout<<tmpvar<<" = 4 * "<<ro->child[0]->tmpvarname<<endl;
            cout<<findident(ro)<<" ["<<tmpvar<<"] = "
                  <<ro->child[1]->tmpvarname<<endl;
        }
        break;
        case RetK:
        {
            genexp(ro->child[0]);
            cout<<"return "<<ro->child[0]->tmpvarname<<endl;
        }
        break;
    }
}

void Generate(Treenode *root)
{
    nowenv = new Env(NULL);
    while(root!=NULL)
    {
        if(root->nodekind == VarDefK)genvardefn(root);
        else if(root->nodekind == FuncDefK)genfuncdefn(root);
        else if(root->nodekind == FuncDeclK)genfuncdecl(root);
        root = root->sibling;
    }
    string name = (string)("main");
    if(nowenv->delList.find(name)==nowenv->delList.end() || nowenv->delList[name]==0)
    {
        yyerror("\nError!\nThere is no main function\n");
    }
}

/*
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
        else if(root->nodekind == VarDeclK)
        {
            printf("Varient Declear:");
            printf("%s ",root->attr.name);
            printf("%d\n",root->arrnum);
        }
        else if(root->nodekind == FuncDefK)
        {
            printf("Function Define:");
            printf("%s\n",root->attr.name);
        }
        else if(root->nodekind == FuncDeclK)
        {
            printf("Function Declear:");
            printf("%s\n",root->attr.name);
        }
        else if(root->nodekind == StmtK)
        {
            printf("Statement:");
            int tmp = root->kind.stmt;
            if(tmp == BigStK)printf("Big statement\n");
            else if(tmp == IfK)printf("If statement\n");
            else if(tmp == IfElseK)printf("If else statement\n");
            else if(tmp == WhileK)printf("While statement\n");
            else if(tmp == AssignSK){printf("assign varient %s\n",root->attr.name);}
            else if(tmp == AssignAK){printf("assign array %s\n",root->attr.name);}
            else if(tmp == RetK){printf("Return statement\n");}
        }
        else if(root->nodekind == ExpK)
        {
            printf("Expression:");
            int tmp = root->kind.exp;
            if(tmp == CalOpK)printf("calculator opreation %d\n",root->attr.calop);
            else if(tmp == LogOpK)printf("logical opreation %d\n",root->attr.logop);
            else if(tmp == AridK)printf("array index\n");
            else if(tmp == ConstK)printf("value %d\n",root->attr.val);
            else if(tmp == IdK)printf("Identifier %s\n",root->attr.name);
            else if(tmp == NotK)printf("Not expreession\n");
            else if(tmp == MinusK)printf("Minus expression\n");
            else if(tmp == CallK)printf("Call Function %s\n",root->attr.name);
        }
        else if(root->nodekind == IdntK)
        {
            printf("IDENTIFIER:%s\n",root->attr.name);
        }
        for(int i=0;i<MAXCHILDREN;i++)
            if(root->child[i]!=NULL)Printree(root->child[i],dep+1);

        root = root->sibling;
    }
}
*/
