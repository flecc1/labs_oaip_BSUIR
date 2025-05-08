#include"header.h"
#include <stdio.h>
#include <stdlib.h>

struct tree* tree_init(int data)
{
    struct tree *root = (struct tree*)malloc(sizeof(struct tree));
    if(root == NULL)
    {
        printf(COLOR_RED "ошибка выделения памяти\n" COLOR_RESET);
        exit(1);
    }
    root->item = data;
    root->left = root->right = NULL;
    return root;
}

struct tree* add_tree(struct tree* node, int data)
{
    if(node == NULL)
    {
        return tree_init(data);
    }

    if(data < node->item)
    {
        node->left = add_tree(node->left, data);
    }
    else
    {
        node->right = add_tree(node->right, data);
    }
    return node;
}

void symetry_printf(struct tree *root)
{
    if(root != NULL)
    {
        symetry_printf(root->left);
        printf("%d ", root->item);
        symetry_printf(root->right);
    }
}

void postorder_printf(struct tree *root)
{
    if(root != NULL)
    {
        postorder_printf(root->left);
        postorder_printf(root->right);
        printf("%d ", root->item);
    }
}

void preorder_printf(struct tree *root)
{
    if(root != NULL)
    {
        printf("%d ", root->item);
        preorder_printf(root->left);
        preorder_printf(root->right);
    }
}

void deltree(struct tree *root)
{
    if(root == NULL) 
    {
        return;
    }
    deltree(root->left);
    deltree(root->right);
    free(root);
    root = NULL;
}

struct tree *findmin(struct tree *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

struct tree *delnode(struct tree *root, int key)
{
    if(root == NULL)
    {
        printf(COLOR_CYAN "введеный элемент не найден\n" COLOR_RESET);
        return root;
    }
    if(key < root->item)
    {
        root->left = delnode(root->left, key);
    }
    else if(key > root->item)
    {
        root->right = delnode(root->right, key);
    }
    else 
    {
        if(root->left == NULL && root->right == NULL)
        {
            printf(COLOR_GREEN "элмент %d удален\n" COLOR_RESET, key);
            free(root);
            return NULL;
        }
        else if(root->left == NULL)
        {
            struct tree *vrem = root->right;
            free(root);
            printf(COLOR_GREEN "элмент %d удален\n" COLOR_RESET, key);
            return vrem;
        }
        else if(root->right == NULL)
        {
            struct tree *vrem = root->left;
            free(root);
            printf(COLOR_GREEN "элмент %d удален\n" COLOR_RESET, key);
            return vrem;
        }
        else 
        {
            struct tree *vrem = findmin(root->left);
            root->item = vrem->item;
            root->right = delnode(root->right, vrem->item);
        }
    }
    return root;
}

struct tree* poisk_in_tree(struct tree *root, int target)
{
    if(root == NULL)
    {
        printf(COLOR_CYAN "введеный элемент дерва не найден\n" COLOR_RESET);
        return NULL;
    }
    if(root->item == target)
    {
        printf(COLOR_GREEN "найден элемент - %d в исходном дереве\n" COLOR_RESET, target);
        return root;
    }
    if(target < root->item)
        return poisk_in_tree(root->left, target);
    else
        return poisk_in_tree(root->right, target);
}

struct tree *build_tree(int *arr, int index, int size)
{
    if(index >= size || *(arr + index) == -1)
    {
        return NULL;
    }
    
    struct tree *root = tree_init(*(arr + index));
    root->right = build_tree(arr, 2 * index + 1, size);
    root->left = build_tree(arr, 2 * index + 2, size);
    return root;
}

void printfTree_rot(struct tree *root, int level)
{
    if(root == NULL)
        return;
    
    printfTree_rot(root->right, level + 1);
    printf("\n");
    for(int i = 0; i < level; i++)
    {
        printf("        ");
    }
    printf(COLOR_YELLOW "%d\n" COLOR_RESET, root->item);

    printfTree_rot(root->left, level + 1);
}

void printTree(struct tree *root)
{
    printfTree_rot(root, 0);
}

void checkPusto(struct tree *root)
{
    if(root == NULL)
    {
        printf("Дерево пустое\n");
        return;
    }
}


struct tree *menu(struct tree *root)
{
    int exit = 0;
    while(!exit)
    {
        printf(COLOR_HEADER "\nМеню: \n" COLOR_RESET);
        printf("1. Обход дерева в прямом порядке (корень, левое поддерво, правое поддерево)\n");
        printf("2. Обход дерева в симетричном порядке (левое поддерево, корень, правое поддерево)\n");
        printf("3. Обход дерева в обратном порядке (левое поддерево, правое поддерево, корень)\n");
        printf("4. Добавить элемент дерева\n");
        printf("5. Удалить элемент дерева\n");
        printf("6. Найти элемент дерева\n");
        printf("7. Удалить дерево\n");
        printf("8. Вывод дерва на экран\n");
        printf("0, Создать дерево и массива\n");
        printf("9. Выход\n");
        int choice = getValidInt(0, 9);
        switch(choice)
        {
            case 0:
            {
                printf("\n");
                printf("введиет размер массива\n");
                int size = getValidInt(0, INT32_MAX);
                int *arr = createDynamicArray(size);
                fillArray(arr, size);
                root = build_tree(arr, 0, size);
                printf("\n");
                break;
            }
            case 1: 
            {
                if(root == NULL)
                {
                    printf("\n");
                    printf("дерево пустое\n");
                }
                else
                {
                    printf("\n");
                    printf("вывод дерева в прямом порядке\n");
                    preorder_printf(root);
                }
                break;
            }
            case 2:
            {
                if(root == NULL)
                {
                    printf("\n");
                    printf("дерево пустое\n");
                }
                else
                {
                    printf("\n");
                    printf("вывод дерева в симетричном порядке\n");
                    symetry_printf(root);
                }
                break;
            }
            case 3:
            {
                if(root == NULL)
                {
                    printf("\n");
                    printf("дерево пустое\n");
                }
                else
                {
                    printf("\n");
                    printf("вывод дерева в обратном порядке\n");
                    postorder_printf(root);
                }
                break;
            }
            case 4:
            {
                printf("\n");
                printf("Введите номер элемента который хотите добавить от %d до %d ", INT32_MIN, INT32_MAX);
                int key = getValidInt(INT32_MIN, INT32_MAX);
                root = add_tree(root, key);
                break;
            }
            case 5:
            {
                printf("\n");
                printf("Введите номер элемента который хотите удалить от %d до %d ", INT32_MIN, INT32_MAX);
                int key = getValidInt(INT32_MIN, INT32_MAX);
                root = delnode(root, key);
                break;
            }
            case 6:
            {
                printf("\n");
                printf("Введите номер элемента который хотите найти от %d до %d ", INT32_MIN, INT32_MAX);
                int key = getValidInt(INT32_MIN, INT32_MAX);
                root = poisk_in_tree(root, key);
                break; 
            }
            case 7:
            {
                deltree(root);
                root = NULL;
                break;
            }
            case 8:
            {
                if(root == NULL)
                {
                    printf("\n");
                    printf("дерево пустое\n");
                }
                else
                    printfTree_rot(root, 0);
                break;
            }
            case 9:
            {
                exit = 1;
                break;
            }
        }
    }
    return root;
}


int* createDynamicArray(int size)
{
    if (size <= 0) 
    {
        printf("\n");
        printf("массив не создан, создайте массив минимум на 1 элемент");
        return NULL;
    }
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr)
    {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    return arr;
}

void fillArray(int* arr, int size)
{
    if (!arr)
        return;

    printf("Введите %d элементов массива:\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("Элемент %d: ", i + 1);
        scanf("%d", &(*(arr + i)));
    }
}
