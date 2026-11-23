#ifndef HEARTOFIRON
#define HEARTOFIRON

typedef const char* Elem_t;

struct Node_t {
    int     index;
    Elem_t  data;
    Node_t* parent;
    Node_t* left;
    Node_t* right;
};

struct Tree_t {
    Node_t* root_node;
    int     node_count;
    int     dump_count;
};

enum error_value {
    NOERROR,
    NULLROOT,
    NEGNODECOUNT,
    NEGDUMPCOUNT,
    NULLNODE,
    WAYERROR
};

enum game_mode {
    EXIT,
    GUESS,
    SAVE
};

#endif
