#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "../../mylib/header_Lib.h"

#define COLOR_HEADER "\033[1;34m"
#define COLOR_TEXT "\033[0;37m"
#define COLOR_DATA "\033[0;32m"


struct tree
{
    int item;
    struct tree *right, *left;
};

struct tree* tree_init(int data);
struct tree* add_tree(struct tree* node, int data);
void symetry_printf(struct tree *root);
void preorder_printf(struct tree *root);
void postorder_printf(struct tree *root);
void deltree(struct tree *root);
struct tree *delnode(struct tree *root, int key);
struct tree* poisk_in_tree(struct tree *root, int target);
struct tree *build_tree_from_array(int *arr, int size);
void printfTree_rot(struct tree *root, int level);
void printTree(struct tree *root);
struct tree *menu(struct tree *root);
int* createDynamicArray(int size);
void fillArray(int* arr, int size);
void checkPusto(struct tree *root);
struct tree *find_min_in_tree(struct tree *root);
struct tree *find_max_in_tree(struct tree *root);