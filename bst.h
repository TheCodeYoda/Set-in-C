#ifndef BST_H
#define BST_H
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node_t;

typedef struct BST {
    Node_t* root;
}BST_t;

Node_t* create_node(int data);
Node_t* insert(Node_t* tree,int data);
void inorder(Node_t* node);
void init_root(BST_t* tree);
void traverse(BST_t* tree);
#endif
