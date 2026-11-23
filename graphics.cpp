// #include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "graphics.h"

const char html_code[] = "meow.html";
const char graph_code[] = "meow.txt";

// начало дампа = открытие html файла
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

// закрытие файла
void DumpEnd(FILE* file)
{
    fprintf(file,
    "</body>\n"
    "</html>\n");
    fclose(file);
    system("start meow.html");
}

// дамп дерева
void TreeDump(FILE* file, Tree_t* tree)
{
    DrawGraph(*(tree->root_node));
    // snprintf() - создаем форматированную строку и вставляем в system
    char command[150] = {};
    snprintf(command, sizeof(command), "dot -Tpng meow.txt -o meow%d.png", tree->dump_count);
    system(command);
    CreateHtml(file, tree->dump_count);
    tree->dump_count++;
}

// рисуем граф
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

// рисуем узел, используем рекурсию
void DrawNode(FILE* file, Node_t node)
{
    fprintf(file, "\"%d\"[shape=record, label=\"{%s}\"];\n",
    node.index, node.data);

    // fprintf(file, "\"%d\"[shape=record, label=\"{data = %s|parent = %zu|{left = %zu|right = %zu}}\"];\n",
    // node.index, node.data, (size_t)node.parent, (size_t)node.left, (size_t)node.right);

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

// создание html файла
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
