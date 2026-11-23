#ifndef WORKING_WTH_FILES
#define WORKING_WTH_FILES

void    PrintTree (FILE*       file, Node_t* node);
Node_t* ReadNode  (FILE*       file, Node_t* parent, Tree_t* tree);
Node_t* ReadTree  (const char* name, Tree_t* tree);

#endif
