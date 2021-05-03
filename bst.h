#ifndef BST_H
#  define BST_H
typedef struct Node {
  void *data; /* make this generic */
  struct Node *left;
  struct Node *right;
  int ht;
} Node_t;

typedef struct BST {
  Node_t *root;
  int (*predicate)();
  int size_of_type;
} Tree_t;

typedef struct Iterator {
  Node_t *ptr;
  Node_t *root;
  int (*predicate)();
} Iterator_t;

/* Node interface */
/* Node_t *create_node(void *data, int size_of_type); */
/* Node_t *insert_tree(Node_t *root, void *data, int (*predicate)(), int size_of_type); */
/* Node_t *erase_tree(Node_t *root, void *data, int (*predicate)()); */
/* void inorder(Node_t *root, void (*printer)()); */
/* void balance(Node_t *root); */
/* necessory?? supporting iterators?? */

/* tree(set) interface */
Tree_t *init_set(int (*predicate)(), int size_of_type); /* change this */
void disp(Tree_t *tree, void (*printer)());
void insert(Tree_t *tree, void *data);
void erase(Tree_t *tree, void *data);
void clear(Tree_t *tree);
int size(Tree_t *tree);

/* Iterator interface */
void init_iterator(Iterator_t *iter, Tree_t *tree);
Iterator_t *find(Tree_t *tree, void *data, int (*comparator)());
Iterator_t *begin(Tree_t *tree);
Iterator_t *end(Tree_t *tree);
Iterator_t *next(Iterator_t *iter);
int has_next(Iterator_t *iter);
Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data);
Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data);
#endif

/* after making things generic user should provide 3 things */
/* 1. His own comparator taking void* params  */
/* 2. His own Predicate taking void* params  */
/* 3. His own printer taking void* params */
