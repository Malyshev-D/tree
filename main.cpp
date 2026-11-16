#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "struct.h"
#include "graphics.h"

const char tree_write[] = "tree.txt";
const char tree_read[] = "tree.txt";

Node_t* CreateNode(Elem_t value, Node_t* parent_node, char branch, int* node_count);
void    PrintTree (FILE*  file,  Node_t* node);
Node_t* ReadTree  ();
Node_t* ReadNode  (FILE*  file,  Node_t* parent,      int* node_count);

int main()
{
    int dump_count = 0;
    Node_t* root_node = ReadTree();

    FILE* file = DumpBegin();
    TreeDump(file, *root_node, &dump_count);
    DumpEnd(file);
}

Node_t* ReadTree() // возвращаем корень
{
    FILE* file = fopen(tree_read, "r");
    if (file == 0)
    {
        printf("Error: file is equal NULL in file: %s in line %d", __FILE__, __LINE__);
        return NULL;
    }

    int node_count = 0;
    Node_t* root_node = ReadNode(file, 0, &node_count);
    fclose(file);
    return root_node;
}

Node_t* ReadNode(FILE* file, Node_t* parent, int* node_count)
{
    Elem_t data = 0;
    char sym = getc(file);
    if (fscanf(file, "%d", &data) == 1)
    {
        Node_t* node = CreateNode(data, parent, 0, node_count);
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
    fprintf(file, "(%d", node->data);

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

Node_t* CreateNode(Elem_t value, Node_t* parent_node, char branch, int* node_count)
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
