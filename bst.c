#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int max(int a, int b)
{
  return (a > b) ? a : b;
}

Node_t *inorder_successor(Node_t *node)
{
  Node_t *temp = node;
  temp = temp->right;
  while (temp->left) {
    temp = temp->left;
  }
  return temp;
}

Node_t *create_node(int data)
{
  Node_t *node = malloc(sizeof(Node_t));
  node->data = data;
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

Node_t *insert_tree(Node_t *root, int data, int (*predicate)(int, int))
{
  if (root == NULL) {
    return create_node(data);
  }
  if (predicate(data, root->data) == 1) {
    root->left = insert_tree(root->left, data, predicate);
  }
  else if (predicate(data, root->data) == 0) {
    root->right = insert_tree(root->right, data, predicate);
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

void insert(Tree_t *tree, int data)
{
  if (tree->root == NULL) {
    tree->root = insert_tree(tree->root, data, tree->predicate);
  }
  else {
    tree->root = insert_tree(tree->root, data, tree->predicate);
  }
}

Node_t *erase_tree(Node_t *root, int data, int (*predicate)(int, int))
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
      struct Node *temp = root->left ? root->left : root->right;

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
      struct Node *temp = inorder_successor(root);

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

void erase(Tree_t *tree, int data)
{
  tree->root = erase_tree(tree->root, data, tree->predicate);
}

/* try to make it variable args */
void init_set(Tree_t *tree, int (*predicate)())
{
  tree->root = NULL;
  tree->predicate = predicate;
}

void inorder(Node_t *node)
{
  if (node == NULL)
    return;
  inorder(node->left);
  printf("%d %d %d\n", node->data, node->ht, get_balance_factor(node));
  inorder(node->right);
}

void disp(Tree_t *tree)
{
  inorder(tree->root);
}

static void tree_size(Node_t *node, int *num)
{
  if (node == NULL)
    return;
  *num += 1;
  tree_size(node->left, num);
  tree_size(node->right, num);
}

int size(Tree_t *tree)
{
  int num = 0;
  tree_size(tree->root, &num);
  return num;
}

int default_predicate(int a, int b)
{
  if (a < b) {
    return 1;
  }
  else if (a > b) {
    return 0;
  }
  return -1;
}

int my_predicate(int a, int b)
{
  if ((a % 3) < (b % 3)) {
    return 1;
  }
  else if ((a % 3) > (b % 3)) {
    return 0;
  }
  return -1;
}

/* Iterator interface */

void init_iterator(Iterator_t *iter, Tree_t *tree)
{
  iter->ptr = tree->root;
}

static Iterator_t *create_iterator(Node_t *node)
{
  Iterator_t *temp = malloc(sizeof(Iterator_t));
  temp->ptr = node;
  return temp;
}

static int get_data(Iterator_t *it)
{
  if (it->ptr) {
    return it->ptr->data;
  }
}

Iterator_t *begin(Tree_t *tree)
{
  Node_t *start = tree->root;
  while (start->left != NULL) {
    start = start->left;
  }
  Iterator_t *iter = create_iterator(start);
  return iter;
}

Iterator_t *end(Tree_t *tree)
{
  Node_t *start = tree->root;
  while (start->right != NULL) {
    start = start->right;
  }
  Iterator_t *iter = create_iterator(start);
  return iter;
}

static Iterator_t *find_tree(Node_t *node, int data)
{
  if (node == NULL) {
    return create_iterator(NULL);
  }
  if (data < node->data) {
    return find_tree(node->left, data);
  }
  else if (data > node->data) {
    return find_tree(node->right, data);
  }
  else {
    return create_iterator(node);
  }
}

Iterator_t *find(Tree_t *tree, int data)
{
  return find_tree(tree->root, data);
}

Iterator_t *next(Node_t *node)
{
  /* TODO */
}

int main()
{
  Tree_t *tree = malloc(sizeof(Tree_t));
  init_set(tree, default_predicate);
  insert(tree, 1);
  insert(tree, 3);
  insert(tree, 5);
  insert(tree, 7);
  insert(tree, 1);
  insert(tree, 2);
  insert(tree, 2);
  insert(tree, 4);
  printf("Size : %d\n", size(tree));

  erase(tree, 2);
  erase(tree, 4);
  erase(tree, 7);

  printf("Size : %d\n", size(tree));

  insert(tree, 2);
  insert(tree, 2);
  insert(tree, 4);

  printf("Size : %d\n", size(tree));
  /* printf("%d\n", tree->root->data); */
  /* printf("%d\n", tree->root->left->data); */
  /* printf("%d\n", tree->root->right->data); */
  /* printf("%d\n", tree->root->left->left->data); */
  /* printf("%d\n", tree->root->left->right->data); */
  /* printf("%d\n", tree->root->left->right->right->data); */
  disp(tree);

  Iterator_t *it_start;
  it_start = begin(tree);
  printf("iter_start : %d\n", get_data(it_start));

  Iterator_t *it_end;
  it_end = end(tree);
  printf("iter_start : %d\n", get_data(it_end));

  Iterator_t *res = find(tree, 7);
  if (res->ptr == NULL) {
    printf("\n not found!!");
  }
  else {
    printf("res : %d\n", get_data(res));
  }
}
