#ifndef BST_H
#define BST_H
typedef struct Node {
  int data; /* make this generic */
  struct Node *left;
  struct Node *right;
  int ht;
} Node_t;

typedef struct BST {
  Node_t *root;
  int (*predicate)(int, int);
} Tree_t;

/* Node interface */
Node_t *create_node(int data);
Node_t *insert_tree(Node_t *root, int data, int (*predicate)());
void inorder(Node_t *root);
void balance(Node_t *root);
Node_t *next(Node_t *node); /* necessory?? supporting iterators?? */

/* tree(set) interface */
void init_set(Tree_t *tree, int (*predicate)());
void disp(Tree_t *tree);
void insert(Tree_t *tree, int data);
void erase(Tree_t *tree, int data);
void clear(Tree_t *tree);
int count(Tree_t *tree);
Node_t *find(Tree_t *tree, int data);
int size(Tree_t *tree);
#endif
