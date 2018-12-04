#ifndef _UTIL_H_
#define _UTIL_H_

Treenode *newvardefnode(char *name,int arrsize);
Treenode *newfuncdefnode(Treenode *fu,Treenode *c0,Treenode *c1);
Treenode *newrtvl(Treenode *x,int type);
Treenode *newexpnode1(Treenode *c0,Treenode *c1,Treenode *c2,int type);
Treenode *newexpnode2(Treenode *c0,Treenode *c1);
Treenode *newexpnode3(Treenode *c0,Treenode *c1);
Treenode *newexpnode4(Treenode *c0,Treenode *c1);
Treenode *newexpnode5(Treenode *c0,Treenode *c1,Treenode *c2);
Treenode *newexpnode6(Treenode *c0,Treenode *c1,Treenode *c2);
Treenode *newexpnode7(Treenode *c0,Treenode *c1,Treenode *c2,int type);
Treenode *newexpnode8(Treenode *c0);
Treenode *newexpnode9(Treenode *c0);
Treenode *newexpnode10(Treenode *c0);
Treenode *newexpnode11(Treenode *c0,Treenode *c1);
Treenode *newexpnode12(Treenode *c0);
Treenode *newidnode(char *name);
Treenode *newnumnode(int val);
Treenode *newlabnode(char *name);
Treenode *newfuncnode(char *name);

void init(Treenode *root);
void liveness(Treenode *root);
void Generate(Treenode *root);
void Printree(Treenode *root,int dep);


#endif
