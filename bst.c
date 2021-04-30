#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int max(int a, int b)
{
  return (a > b) ? a : b;
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
    root->left = leftRotate(root);
    return rightRotate(root);
  }

  /* RL case */
  if (balance < -1 && predicate(data, root->right->data) == 1) {
    root->right = rightRotate(root);
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

int main()
{
  Tree_t *tree = malloc(sizeof(Tree_t));
  init_set(tree, default_predicate);
  insert(tree, 5);
  insert(tree, 9);
  insert(tree, 15);
  insert(tree, 1);
  insert(tree, 2);
  /* insert(tree, 2); */
  insert(tree, 4);

  printf("%d\n", tree->root->data);
  printf("%d\n", tree->root->left->data);
  printf("%d\n", tree->root->right->data);
  /* printf("%d\n", tree->root->left->left->data); */
  /* printf("%d\n", tree->root->left->right->data); */
  /* printf("%d\n", tree->root->left->right->right->data); */
  disp(tree);
}
