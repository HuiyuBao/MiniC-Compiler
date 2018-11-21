#ifndef _UTIL_H_
#define _UTIL_H_

Treenode *newvardefnode(char *name,int arrsize);
Treenode *newvardeclnode(char *name,int arrsize);
Treenode *newfuncdefnode(char *name,Treenode *c0,Treenode *c1);
Treenode *newfuncdeclnode(char *name,Treenode *c0);

Treenode *newstmtnode1(Treenode *c0);
Treenode *newstmtnode2(Treenode *c0,Treenode *c1);
Treenode *newstmtnode3(Treenode *c0,Treenode *c1,Treenode *c2);
Treenode *newstmtnode4(Treenode *c0,Treenode *c1);
Treenode *newstmtnode5(Treenode *tmp,Treenode *c0);
Treenode *newstmtnode6(Treenode *tmp,Treenode *c0,Treenode *c1);
Treenode *newstmtnode7(Treenode *c0);

Treenode *newexprnode1(Treenode *c0,Treenode *c1,int optmp);
Treenode *newexprnode2(Treenode *c0,Treenode *c1,int optmp);
Treenode *newexprnode3(Treenode *c0,Treenode *c1);
Treenode *newexprnode4(int numtmp);
Treenode *newexprnode5(Treenode *tmp);
Treenode *newexprnode6(Treenode *c0);
Treenode *newexprnode7(Treenode *c0);
Treenode *newexprnode8(Treenode *tmp,Treenode *c0);

Treenode *newidntnode(char *name);


string findident(char *NAME);

void genvardefn(Treenode *ro);
void genvarlist(Treenode *ro);
void genfuncdefn(Treenode *ro);
void genfuncdecl(Treenode *ro);
void genfuncbody(Treenode *ro);
void genparalist(Treenode *ro);
void genexp(Treenode *ro);
void genstmt(Treenode *ro);
void Generate(Treenode *root);


void Printree(Treenode *root,int dep);

#endif
