#ifndef TREE_OPERATIONS
#define TREE_OPERATIONS

Node_t* NewNode      (Elem_t  value,     Node_t* parent_node, char branch, int* node_count);
Node_t* GoDownTree   (Node_t* root_node);
void    AddNewAnswer (Node_t* current,   int*    node_count);
void    UserInterface(Node_t* root_node, int*    node_count);
enum    error_value TreeVerify(Node_t* root_node, Node_t* node);

#endif
