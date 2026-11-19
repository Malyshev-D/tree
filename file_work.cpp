// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tree_op.h"
#include "file_work.h"

const char tree_read[] = "tree.txt";

Node_t* ReadTree(int* node_count) // возвращаем корень
{
    FILE* file = fopen(tree_read, "r");
    if (file == 0)
    {
        printf("Error: file is equal NULL in file: %s in line %d", __FILE__, __LINE__);
        return NULL;
    }

    Node_t* root_node = ReadNode(file, 0, node_count);

    fclose(file);
    return root_node;
}

Node_t* ReadNode(FILE* file, Node_t* parent, int* node_count)
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
        Node_t* node = NewNode(data, parent, 0, node_count);
        node->left = ReadNode(file, node, node_count);
        node->right = ReadNode(file, node, node_count);
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
