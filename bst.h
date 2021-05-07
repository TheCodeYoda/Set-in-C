#ifndef BST_H
#  define BST_H

typedef struct Node {
  void *data;
  struct Node *left;
  struct Node *right;
  int ht;
} Node_t;

typedef struct BST {
  Node_t *root;
  int (*predicate)();
  int size_of_type;
} Set;

typedef struct Iterator {
  Node_t *ptr;
  Node_t *root;
  int (*predicate)();
} Iterator_t;

/* tree(set) interface */
Set *init_set(int (*predicate)(), int size_of_type);
void disp(Iterator_t *begin, Iterator_t *end, void (*printer)());
void insert(Set *tree, void *data);
void erase(Set *tree, void *data);
void clear(Set *tree);
int size(Set *tree);
void merge(Set *set1, Set *set2);

/* Iterator interface */
void init_iterator(Iterator_t *iter, Set *tree);
Iterator_t *find(Set *tree, void *data, int (*comparator)());
Iterator_t *begin(Set *tree);
Iterator_t *end(Set *tree);
Iterator_t *rbegin(Set *tree);
Iterator_t *rend(Set *tree);
void next(Iterator_t *iter);
void prev(Iterator_t *iter);
int has_next(Iterator_t *iter);
Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)());
Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)());
void *get_data(Iterator_t *it);
#endif

/* after making things generic user should provide 3 things */
/* 1. His own comparator taking void* params  */
/* 2. His own Predicate taking void* params  */
/* 3. His own printer taking void* params */
