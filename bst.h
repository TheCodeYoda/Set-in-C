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

/* tree(set) interface */
Tree_t *init_set(int (*predicate)(), int size_of_type); /* change this */
void disp(Tree_t *tree, void (*printer)());
void insert(Tree_t *tree, void *data);
void erase(Tree_t *tree, void *data);
void clear(Tree_t *tree);
int size(Tree_t *tree);
void merge(Tree_t *set1, Tree_t *set2);

/* Iterator interface */
void init_iterator(Iterator_t *iter, Tree_t *tree);
Iterator_t *find(Tree_t *tree, void *data, int (*comparator)());
Iterator_t *begin(Tree_t *tree);
Iterator_t *end(Tree_t *tree);
Iterator_t *next(Iterator_t *iter);
int has_next(Iterator_t *iter);
Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)());
Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)());
void *get_data(Iterator_t *it);
#endif

/* after making things generic user should provide 3 things */
/* 1. His own comparator taking void* params  */
/* 2. His own Predicate taking void* params  */
/* 3. His own printer taking void* params */
