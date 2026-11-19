// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "graphics.h"

const char html_code[] = "meow.html";
const char graph_code[] = "meow.txt";

FILE* DumpBegin()
{
    FILE* file = fopen(html_code, "w");
    fprintf(file, "<!DOCTYPE html>\n"
        "<head>\n"
        "\t<title>List Dump</title>\n"
        "\t<link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
    );
    return file;
}

void DumpEnd(FILE* file)
{
    fprintf(file,
    "</body>\n"
    "</html>\n");
    fclose(file);
    system("start meow.html");
}

void TreeDump(FILE* file, Node_t node, int* dump_count)
{
    DrawGraph(node);
    // snprintf() - создаем форматированную строку и вставляем в system
    char command[150] = {};
    snprintf(command, sizeof(command), "dot -Tpng meow.txt -o meow%d.png", *dump_count);
    system(command);
    CreateHtml(file, *dump_count);
    (*dump_count)++;
}

void DrawGraph(Node_t node)
{
    FILE* g_file = fopen(graph_code, "w");
    fprintf(g_file, "digraph G {\n");
    fprintf(g_file, "bgcolor=\"#0a0b17\";\n");
    fprintf(g_file, "node[fontsize=12, color=\"#8bf3ff\","
        "style=\"rounded, filled\", fillcolor=\"#060844\","
        "fontname=\"Arial\", fontcolor=\"#8bf3ff\"];\n"
        "edge [style=solid, color=\"#24ffed\"];\n");

    DrawNode(g_file, node);

    fprintf(g_file, "}");
    fclose(g_file);
}

void DrawNode(FILE* file, Node_t node)
{
    fprintf(file, "\"%d\"[shape=record, label=\"{%s}\"];\n",
    node.index, node.data);
    if (node.left != NULL)
    {
        DrawNode(file, *node.left);
        fprintf(file, "\"%d\"->\"%d\";\n", node.index, node.left->index);
    }
    if (node.right != NULL)
    {
        DrawNode(file, *node.right);
        fprintf(file, "\"%d\"->\"%d\";\n", node.index, node.right->index);
    }
}

void CreateHtml(FILE* file, int dump_num)
{
    fprintf(file,
        "<!DOCTYPE html>\n"
        "<head>\n"
        "\t<title>Tree dump</title>\n"
        "\t<link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
        "\t<img src=\"meow%d.png\" alt=\"Graph\">\n",
        dump_num);
}
