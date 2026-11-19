// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "graphics.h"
#include "file_work.h"
#include "tree_op.h"

int main()
{
    int dump_count = 0;
    int node_count = 0;
    FILE* file = DumpBegin();

    Node_t* root_node = ReadTree(&node_count);

    UserInterface(root_node, &node_count);
    TreeDump(file, *root_node, &dump_count);
    DumpEnd(file);
    return 0;
}

