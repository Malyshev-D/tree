// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tree_op.h"
#include "file_work.h"

// читалка дерева из файла
Node_t* ReadTree(const char* name, Tree_t* tree)
{
    FILE* file = fopen(name, "r");
    if (file == 0)
    {
        printf("Error: file is equal NULL in file: %s in line %d", __FILE__, __LINE__);
        return NULL;
    }

    Node_t* root_node = ReadNode(file, 0, tree);

    fclose(file);
    return root_node;
}

// рекурсивное чтение одного узла
Node_t* ReadNode(FILE* file, Node_t* parent, Tree_t* tree)
{
    Elem_t data = 0;
    char sym = getc(file);
    char string[100] = {};

    if ((sym = getc(file)) == '"')
    {
        sym = getc(file);
        for (int idx = 0; sym != '"'; idx++)
        {
            string[idx] = sym;
            sym = getc(file);
        }
        data = strdup(string);
        Node_t* node = NewNode(data, parent, tree);
        node->left = ReadNode(file, node, tree);
        node->right = ReadNode(file, node, tree);
        sym = getc(file);
        return node;
    }
    else
    {
        sym = getc(file);
        while (sym != ')')
            sym = getc(file);
        return 0;
    }
}

// печать дерева
void PrintTree(FILE* file, Node_t* node)
{
    fprintf(file, "(\"%s\"", node->data);

    if (node->left)
        PrintTree(file, node->left);
    else
        fprintf(file, "(nil)");

    if (node->right)
        PrintTree(file, node->right);
    else
        fprintf(file, "(nil)");

    fprintf(file, ")");
}
