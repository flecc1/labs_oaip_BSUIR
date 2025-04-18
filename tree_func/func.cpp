#include"header_tree.h"

tree* List(int data)
{
    tree *t = (tree*)malloc(sizeof(tree));
    t->item = data;
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
            if(b == t->item)
            {
                find = 1;
                puts("такой уже есть ");
            }
            else
                if(b < t->item)
                t = t->left;
                else t = t-> right;
        }
        if(!find)
        {
            t = List(b);
            if(b < prev->item)
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
        if(key == t -> item)
        {
            find = 0;
            puts("такой есть ");
        }
        else 
        if(key < t->item)
            t = t->left;
        else
            t = t->right;
    }
    if(find)
    {
        t = List(key);
        if(key < prev->item)
            prev -> left = t;
        else
            prev -> right = t;
    }
}


void add_tree(struct tree **p, int a)
{
    struct tree *tmp;
    while(*p)
    {
        if((*p)->item == a)
        {
            puts("такой элемент уже есть");
            return;
        }
        if((*p)->item > a)
        {
            p = &(*p)->left;
        }
        else 
        {
            p = &(*p)->right;
        }
        if(!(*p = (struct tree *)malloc(sizeof(**p))))
        {
            puts("нет оп для добавления");
            return;
        }
        (*p)->item = a;
        (*p)->left = (*p)->right = NULL;
    } 
}


void add_item(int a, struct tree **p)
{
    int c;
    if(!*p)
    {
        if(!(*p = (struct tree *)calloc(1, sizeof(**p))));
        {
            puts("нет оп для добавления");
            return;
        }
        (*p)->item = a;
        (*p)->left = (*p)->right = NULL;
    }
    else 
    {
        c = ((*p)->item) - a;
        if(c > 0)
        {
            add_item(a, &((*p)->left));
        }
        else if(c < 0)
        {
            add_item(a, &((*p)->right));
        }
        else 
            printf("элемент %d уже есть\n", a);
    }
}


