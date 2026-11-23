#ifndef GRAPHICSDRAWTREE
#define GRAPHICSDRAWTREE

FILE* DumpBegin ();
void  TreeDump  (FILE*  file, Tree_t* tree);
void  CreateHtml(FILE*  file, int     dump_num);
void  DrawGraph (Node_t node);
void  DrawNode  (FILE*  file, Node_t  node);
void  DumpEnd   (FILE*  file);

#endif
