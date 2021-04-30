#ifndef BST_H
#define BST_H
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node_t;

typedef struct BST {
  Node_t *root;
} Tree_t;

/* Node interface */
Node_t *create_node(int data);
Node_t *insert_tree(Node_t *root, int data);
void inorder(Node_t *root);
void balance(Node_t *root);

/* tree(set) interface */
void init_set(Tree_t *tree);
void disp(Tree_t *tree);
void insert(Tree_t *tree, int data);

#endif
