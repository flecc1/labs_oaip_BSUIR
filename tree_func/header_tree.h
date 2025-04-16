#include<stdio.h>
#include<stdlib.h>
#include "../mylib/header_Lib.h"


struct tree
{
    int data;
    tree *right, *left;
}*root;

tree* List(int data);
tree* reate(tree *root);
void add_list(tree *root, int key);
