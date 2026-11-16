#ifndef HEARTOFIRON
#define HEARTOFIRON

typedef int Elem_t;

struct Node_t {
    int index;
    Elem_t data;
    Node_t* parent;
    Node_t* left;
    Node_t* right;
};

#endif
