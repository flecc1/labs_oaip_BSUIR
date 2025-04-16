#include"header_tree.h"

tree* List(int data)
{
    tree *t = (tree*)malloc(sizeof(tree));
    t->data = data;
    t->left = t->right = NULL;
    return t;
}

tree* reate(tree *root)
{
    tree *prev, *t;
    int N, b, find;
    N = getValidInt(1, INT32_MAX);

    if(!root)
    {
        N--;
        printf("введите значение корня\n");
        b = getValidInt(1, INT32_MAX);
        root = List(b);
    }

    for (int i = 1; i < N; i ++)
    {
        puts("введите данные ");
        b = getValidInt(1, INT32_MAX);

        t = root;
        find  = 0;

        while(t && !find)
        {
            prev = t;
            if(b == t->data)
            {
                find = 1;
                puts("такой уже есть ");
            }
            else
                if(b < t->data)
                t = t->left;
                else t = t-> right;
        }
        if(!find)
        {
            t = List(b);
            if(b < prev->data)
                prev->left = t;
            else 
                prev ->right = t;
        }
    }
    return root;
}



void add_list(tree *root, int key)
{
    tree *prev, *t;
    int find = 1;
    t = root;
    while(t && find)
    {
        prev = t;
        if(key == t -> data)
        {
            find = 0;
            puts("такой есть ");
        }
        else 
        if(key < t->data)
            t = t->left;
        else
            t = t->right;
    }
    if(find)
    {
        t = List(key);
        if(key < prev->data)
            prev -> left = t;
        else
            prev -> right = t;
    }
}


