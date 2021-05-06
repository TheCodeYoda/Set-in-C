#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/* Node interface */
static Node_t *create_node(void *data, int size_of_type);
static Node_t *insert_tree(Node_t *root, void *data, int (*predicate)(), int size_of_type);
static Node_t *erase_tree(Node_t *root, void *data, int (*predicate)());
static void inorder(Node_t *root, void (*printer)());

static int max(int a, int b)
{
  return (a > b) ? a : b;
}

static Node_t *find_ancestor(Node_t *anc, Node_t *root, void *data, int (*predicate)())
{
  if (root == NULL) {
    return NULL;
  }
  /* root->data <= data */
  if (predicate(root->data, data) == 1 || predicate(root->data, data) == -1) {
    if (anc && anc->left == root) {
      return anc;
    }
    else {
      return find_ancestor(root, root->right, data, predicate);
    }
  }
  /* data < root->data */
  if (predicate(data, root->data)) {
    return find_ancestor(root, root->left, data, predicate);
  }
}

static Node_t *inorder_successor_par(Node_t *node, Node_t *root, int (*predicate)())
{
  return find_ancestor(NULL, root, node->data, predicate);
}

static Node_t *inorder_successor(Node_t *node)
{
  Node_t *temp = node;
  temp = temp->right;
  while (temp->left) {
    temp = temp->left;
  }
  return temp;
}

static Node_t *create_node(void *data, int size_of_type)
{
  Node_t *node = malloc(sizeof(Node_t));
  node->data = malloc(size_of_type);
  memcpy(node->data, data, size_of_type);
  node->left = NULL;
  node->right = NULL;
  node->ht = 1;
  return node;
}

/* static int height(Node_t *node) */
/* { */
/*   if (node == NULL) { */
/*     return -1; */
/*   } */
/*   int left = 1 + height(node->left); */
/*   int right = 1 + height(node->right); */
/*   return max(left, right); */
/* } */

static int height(Node_t *node)
{
  if (node == NULL) {
    return 0;
  }
  return node->ht;
}

static int get_balance_factor(Node_t *node)
{
  if (node == NULL) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

static Node_t *rightRotate(Node_t *y)
{
  Node_t *x = y->left;
  Node_t *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->ht = 1 + max(height(y->left), height(y->right));
  x->ht = 1 + max(height(x->left), height(x->right));

  // Return new root
  return x;
}

// A utility function to left rotate subtree rooted with x
static Node_t *leftRotate(Node_t *x)
{
  /* printf("L rotating %d\n", x->data); */
  Node_t *y = x->right;
  Node_t *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->ht = 1 + max(height(x->left), height(x->right));
  y->ht = 1 + max(height(y->left), height(y->right));

  // Return new root
  return y;
}

static Node_t *insert_tree(Node_t *root, void *data, int (*predicate)(), int size_of_type)
{
  if (root == NULL) {
    return create_node(data, size_of_type);
  }
  if (predicate(data, root->data) == 1) {
    root->left = insert_tree(root->left, data, predicate, size_of_type);
  }
  else if (predicate(data, root->data) == 0) {
    root->right = insert_tree(root->right, data, predicate, size_of_type);
  }

  else {
    return root;
  }

  /* updation of ht */
  root->ht = 1 + max(height(root->left), height(root->right));

  /* compute balance factor */
  int balance = get_balance_factor(root);

  /* LL case */
  if (balance > 1 && predicate(data, root->left->data) == 1) {
    return rightRotate(root);
  }

  /* RR case */
  if (balance < -1 && predicate(data, root->right->data) == 0) {
    return leftRotate(root);
  }

  /* LR case */
  if (balance > 1 && predicate(data, root->left->data) == 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  /* RL case */
  if (balance < -1 && predicate(data, root->right->data) == 1) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void insert(Set *tree, void *data)
{
  tree->root = insert_tree(tree->root, data, tree->predicate, tree->size_of_type);
}

static Node_t *erase_tree(Node_t *root, void *data, int (*predicate)())
{
  if (root == NULL) {
    return NULL;
  }
  if (predicate(data, root->data) == 1) {
    root->left = erase_tree(root->left, data, predicate);
  }
  else if (predicate(data, root->data) == 0) {
    root->right = erase_tree(root->right, data, predicate);
  }
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      Node_t *temp = root->left ? root->left : root->right;

      // No child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      else {  // One child case
        *root = *temp;
      }  // Copy the contents of
         // the non-empty child
      free(temp);
    }
    else {
      // node with two children: Get the inorder
      // successor (smallest in the right subtree)
      Node_t *temp = inorder_successor(root);

      // Copy the inorder successor's data to this node
      root->data = temp->data;

      // Delete the inorder successor
      root->right = erase_tree(root->right, temp->data, predicate);
    }
  }

  if (root == NULL) {
    return root;
  }

  /* balancing here */

  /* updation of ht */
  root->ht = 1 + max(height(root->left), height(root->right));

  /* compute balance factor */
  int balance = get_balance_factor(root);

  /* LL case */
  if (balance > 1 && get_balance_factor(root->left) >= 0) {
    return rightRotate(root);
  }

  /* LR case */
  if (balance > 1 && get_balance_factor(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  /* RR case */
  if (balance < -1 && get_balance_factor(root->right) <= 0) {
    return leftRotate(root);
  }

  /* RL case */
  if (balance < -1 && get_balance_factor(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void erase(Set *tree, void *data)
{
  tree->root = erase_tree(tree->root, data, tree->predicate);
}

static int clear_tree(Node_t *node)
{
  if (node == NULL)
    return 1;
  int left = clear_tree(node->left);
  if (!left)
    free(node->left);
  int right = clear_tree(node->right);
  if (!right)
    free(node->right);
  return left ^ right;
}
void clear(Set *tree)
{
  if (!clear_tree(tree->root))
    free(tree->root);
  tree->root = NULL;
}

/* try to make it variable args */
Set *init_set(int (*predicate)(), int size_of_type)
{
  Set *temp = malloc(sizeof(Set));
  temp->root = NULL;
  temp->predicate = predicate;
  temp->size_of_type = size_of_type;
  return temp;
}

static void inorder(Node_t *node, void (*printer)())
{
  if (node == NULL)
    return;
  inorder(node->left, printer);
  printer(node->data);
  inorder(node->right, printer);
}

void disp(Iterator_t *begin, Iterator_t *end, void (*printer)())
{
  /* inorder(tree->root, printer); */
  while (has_next(begin) && begin->ptr != end->ptr) {
    printer(get_data(begin));
    next(begin);
  }
}

static void tree_size(Node_t *node, int *num)
{
  if (node == NULL)
    return;
  *num += 1;
  tree_size(node->left, num);
  tree_size(node->right, num);
}

int size(Set *tree)
{
  int num = 0;
  tree_size(tree->root, &num);
  return num;
}

/* Iterator interface */

void init_iterator(Iterator_t *iter, Set *tree)
{

  iter->ptr = NULL;
  iter->root = tree->root;
  iter->predicate = tree->predicate;
}

static Iterator_t *create_iterator(Node_t *node, Node_t *root, int (*predicate)())
{
  Iterator_t *temp = malloc(sizeof(Iterator_t));
  temp->ptr = node;
  temp->root = root;
  temp->predicate = predicate;
  return temp;
}

void *get_data(Iterator_t *it)
{
  if (it->ptr) {
    return it->ptr->data;
  }
}

Iterator_t *begin(Set *tree)
{
  Node_t *start = tree->root;
  if (!start) {
    return create_iterator(NULL, NULL, tree->predicate);
  }
  while (start->left != NULL) {
    start = start->left;
  }
  return create_iterator(start, tree->root, tree->predicate);
}

Iterator_t *end(Set *tree)
{
  Node_t *start = tree->root;
  if (!start) {
    return create_iterator(NULL, NULL, tree->predicate);
  }
  while (start != NULL) {
    start = start->right;
  }
  return create_iterator(start, tree->root, tree->predicate);
}

static Iterator_t *find_tree(Node_t *node, void *data, int (*comparator)(), int (*predicate)())
{
  if (node == NULL) {
    return create_iterator(NULL, NULL, predicate);
  }
  if (predicate(data, node->data) == 1) {
    return find_tree(node->left, data, comparator, predicate);
  }
  else if (predicate(data, node->data) == 0) {
    return find_tree(node->right, data, comparator, predicate);
  }
  else {
    if (comparator(data, node->data) == -1) {
      return create_iterator(node, NULL, predicate);
    }
    else {
      return create_iterator(NULL, NULL, predicate);
    }
  }
}

Iterator_t *find(Set *tree, void *data, int (*comparator)())
{
  return find_tree(tree->root, data, comparator, tree->predicate);
}

Iterator_t *next(Iterator_t *it)
{
  if (it->ptr->right != NULL) {
    it->ptr = inorder_successor(it->ptr);
  }
  else {
    it->ptr = inorder_successor_par(it->ptr, it->root, it->predicate);
  }
}

int has_next(Iterator_t *it)
{
  if (it->ptr == NULL) {
    return 0;
  }
  return 1;
}

Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)())
{
  while (has_next(begin) && begin->ptr != end->ptr) {
    if (comparator(get_data(begin), data) == 0 || comparator(get_data(begin), data) == -1) {
      return begin;
    }
    next(begin);
  }
  return begin;
}

Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)())
{
  while (has_next(begin) && begin->ptr != end->ptr) {
    if (comparator(get_data(begin), data) == 0) {
      return begin;
    }
    next(begin);
  }
  return begin;
}

void merge_tree(Set *set1, Set *set2, Node_t *node)
{
  if (!node) {
    return;
  }
  merge_tree(set1, set2, node->left);
  insert(set1, node->data);
  merge_tree(set1, set2, node->right);
}
void merge(Set *set1, Set *set2)
{
  merge_tree(set1, set2, set2->root);
}
