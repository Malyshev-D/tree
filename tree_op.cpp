#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tree_op.h"
#include "file_work.h"

const char tree_to_write[] = "tree.txt";

Node_t* NewNode(Elem_t value, Node_t* parent_node, char branch, int* node_count)
{
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));
    node->data = value;
    (*node_count)++;
    node->index = *node_count;
    node->parent = parent_node;
    if (branch == 'l')
        parent_node->left = node;
    if (branch == 'r')
        parent_node->right = node;

    return node;
}

void UserInterface(Node_t* root_node, int* node_count)
{
    int option = 0;
    while (true)
    {
        printf("Choose the game mode:\n[exit=0 / just guess=1 / guess and append=2 / save current tree=3]\n");
        scanf("%d", &option);
        switch (option)
        {
            case 0:
                printf("See you on winter exams\n");
                return;
            case 1:
                GoDownTree(root_node);
                putchar('\n');
                break;
            case 2:
                AddNewAnswer(GoDownTree(root_node), node_count);
                break;
            case 3:
                FILE* print_file = fopen(tree_to_write, "w");
                PrintTree(print_file, root_node);
                fclose(print_file);
        }
    }
}

Node_t* GoDownTree(Node_t* root_node)
{
    Node_t* current = root_node;
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
    printf("%s", current->data);
    return current;
}

void AddNewAnswer(Node_t* current, int* node_count)
{
    int dir = 0;
    printf("?\n[yes = 1 / no = 0] ");
    scanf("%d", &dir);
    if (dir == 0)
    {
        printf("Who did you guess?\n");
        char string[100] = {};
        char sym = getchar();
        int idx = 0;
        for (idx = 0; (sym = getchar()) != '\n'; idx++)
        {
            string[idx] = sym;
        }
        NewNode(current->data, current, 'l', node_count);
        NewNode(strdup(string), current, 'r', node_count);

        printf("What's the difference between %s and %s?\n", current->data, string);
        for (idx = 0; (sym = getchar()) != '\n'; idx++)
        {
            string[idx] = sym;
        }
        string[idx] = '?';
        string[idx + 1] = '\0';
        current->data = strdup(string);
    }
}

enum error_value TreeVerify(Node_t* root_node, Node_t* node)
{
    Node_t* current = node;
    while (current->parent != NULL)
    {
        current = current->parent;
    }
    if (current != root_node)
    {
        printf("TREE VERIFICATION FAILED! ROOT_NODE IS UNACCESSIBLE TO THE CURRENT NODE! PLEASE GO TOUCH GRASS!\n");
        return WAYERROR;
    }
    return NOERROR;
}
