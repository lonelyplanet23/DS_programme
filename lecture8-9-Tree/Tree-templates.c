#include<stdio.h>

struct node{
    Datatype data;
    struct node *lchild, *rchild
};
typedef struct node btnode;
typedef struct *node btnodeptr;
