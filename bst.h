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

typedef struct Iterator {
  Node_t *ptr;
  Node_t *root;
  int (*predicate)(int, int);
} Iterator_t;

/* Node interface */
Node_t *create_node(int data);
Node_t *insert_tree(Node_t *root, int data, int (*predicate)(int, int));
Node_t *erase_tree(Node_t *root, int data, int (*predicate)(int, int));
void inorder(Node_t *root);
void balance(Node_t *root);
/* necessory?? supporting iterators?? */

/* tree(set) interface */
void init_set(Tree_t *tree, int (*predicate)());
void disp(Tree_t *tree);
void insert(Tree_t *tree, int data);
void erase(Tree_t *tree, int data);
void clear(Tree_t *tree);
int size(Tree_t *tree);

/* Iterator interface */
void init_iterator(Iterator_t *iter, Tree_t *tree);
Iterator_t *find(Tree_t *tree, int data);
Iterator_t *begin(Tree_t *tree);
Iterator_t *end(Tree_t *tree);
Iterator_t *next(Iterator_t *iter);
int has_next(Iterator_t *iter);
Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, int data);
Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, int data);
#endif
