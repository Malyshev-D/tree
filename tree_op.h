#ifndef TREE_OPERATIONS
#define TREE_OPERATIONS

Node_t*          NewNode      (Elem_t value, Node_t* parent_node, Tree_t* tree);
void             GoDownTree   (Tree_t* tree);
void             AddNewAnswer (Node_t* current, Tree_t* tree);
void             UserInterface(const char* filename, Tree_t* tree);
enum error_value TreeVerify   (Tree_t* tree, Node_t* node);

#endif
