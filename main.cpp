// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "graphics.h"
#include "file_work.h"
#include "tree_op.h"
// g++ main.cpp graphics.cpp file_work.cpp tree_op.cpp -Wall -Wextra
int main(int argc, char* argv[])
{
    const char* tree_read = argv[1];
    const char* tree_print = argv[2];

    FILE* file = DumpBegin();
    (void)argc;                                     // STUB
    Tree_t tree = {};
    tree.root_node = ReadTree(tree_read, &tree);

    UserInterface(tree_print, &tree);

    TreeDump(file, &tree);
    DumpEnd(file);
    return 0;
}

