#ifndef bst_H
#define bst_H

#define NODE_NOT_FOUND    0

typedef struct _node_ node;

struct _node_
{
    int key_;
    node *left_;
    node *right_;
};

int (*comparer_fct_ptr)(int, int);

void init_compare_function_ptr( int(*comp)(int left, int right));

node* insert_node(node* root, int key);

node* find_node(node* root, int key);

node* delete_node(node* root, int key);

void dispose_tree(node* root);


#endif
