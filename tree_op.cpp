#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tree_op.h"
#include "file_work.h"

// создание узла
Node_t* NewNode(Elem_t value, Node_t* parent_node, Tree_t* tree)
{
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));

    if (node == NULL)
    {
        printf("CALLOC RETURNED NULL IN %s %s:%d\n", __FILE__, __FUNCTION__, __LINE__);
        return NULL;
    }

    node->data = value;
    tree->node_count++;
    node->index = tree->node_count;
    node->parent = parent_node;
    return node;
}

// пользовательский интерфейс
void UserInterface(const char* filename, Tree_t* tree)
{
    int option = 0;
    while (true)
    {
        printf("Choose the game mode:\n[exit=0 / guess the country=1 / save current tree=2]\n");
        scanf("%d", &option);
        switch (option)
        {
            case EXIT:
                printf("See you on winter exams\n");
                return;
            case GUESS:
                GoDownTree(tree);
                break;
            case SAVE:
                FILE* print_file = fopen(filename, "w");
                PrintTree(print_file, tree->root_node);
                fclose(print_file);
        }
    }
}

// обход дерева и добавление нового ответа
void GoDownTree(Tree_t* tree)
{
    Node_t* current = tree->root_node;
    int dir = 0;
    while (current->left != 0 && current->right != 0)
    {
        printf("%s\n", current->data);
        printf("[yes = 1 / no = 0] ");

        scanf("%d", &dir);
        if (dir == 1)
            current = current->left;
        else
            current = current->right;
    }
    printf("%s?\n[yes = 1 / no = 0]", current->data);

    scanf("%d", &dir);
    if (dir == 0)
        AddNewAnswer(current, tree);
}

// добавление нового ответа
void AddNewAnswer(Node_t* current, Tree_t* tree)
{
    printf("Who did you guess?\n");
    char string[100] = {};
    char sym = getchar();
    int idx = 0;
    for (idx = 0; (sym = getchar()) != '\n'; idx++)
    {
        string[idx] = sym;
    }
    current->left = NewNode(current->data, current, tree);
    if (TreeVerify(tree, current->left) != NOERROR)
        return ;
    current->right = NewNode(strdup(string), current, tree);
    if (TreeVerify(tree, current->right) != NOERROR)
        return ;

    printf("What's the difference between %s and %s?\n", current->data, string);
    for (idx = 0; (sym = getchar()) != '\n'; idx++)
    {
        string[idx] = sym;
    }
    string[idx] = '?';
    string[idx + 1] = '\0';
    current->data = strdup(string);
    if (TreeVerify(tree, current) != NOERROR)
        return ;
}

// верификатор
enum error_value TreeVerify(Tree_t* tree, Node_t* node)
{
    if (tree == NULL)
    {
        printf("TREE VERIFICATION FAILED! TREE POINTER IS NULL! PLEASE TAKE A COFFEE BREAK!\n");
        return NULLROOT;
    }
    if (tree->root_node == NULL)
    {
        printf("TREE VERIFICATION FAILED! ROOT NODE POINTER IS NULL! PLEASE GO OUTSIDE!\n");
        return NULLNODE;
    }
    if (tree->node_count < 0)
    {
        printf("TREE VERIFICATION FAILED! NODE COUNTER IS BELOW ZERO! PLEASE GO OUT!\n");
        return NEGNODECOUNT;
    }
    if (tree->dump_count < 0)
    {
        printf("TREE VERIFICATION FAILED! DUMP COUNTER IS BELOW ZERO! PLEASE STAND UP AND MOVE!\n");
        return NEGDUMPCOUNT;
    }
    if (node == NULL)
    {
        printf("TREE VERIFICATION FAILED! NODE POINTER IS NULL! PLEASE TAKE A SHOWER!\n");
        return NULLNODE;
    }

    Node_t* current = node;
    while (current->parent != NULL)
    {
        current = current->parent;
    }
    if (current != tree->root_node)
    {
        printf("TREE VERIFICATION FAILED! ROOT_NODE IS UNACCESSIBLE TO THE CURRENT NODE! PLEASE GO TOUCH GRASS!\n");
        return WAYERROR;
    }
    return NOERROR;
}
