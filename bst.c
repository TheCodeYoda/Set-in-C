#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Node_t *create_node(int data)
{
  Node_t *node = malloc(sizeof(Node_t));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
}

Node_t *insert_tree(Node_t *root, int data)
{
  if (root == NULL) {
    return create_node(data);
  }
  if (data < root->data) {
    root->left = insert_tree(root->left, data);
  }
  else if (data > root->data) {
    root->right = insert_tree(root->right, data);
  }
  return root;
}

void insert(Tree_t *tree, int data)
{
  if (tree->root == NULL) {
    tree->root = insert_tree(tree->root, data);
  }
  else {
    insert_tree(tree->root, data);
  }
}

void init_set(Tree_t *tree)
{
  tree->root = NULL;
}

void inorder(Node_t *node)
{
  if (node == NULL)
    return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

void disp(Tree_t *tree)
{
  inorder(tree->root);
}

int main()
{
  Tree_t *tree = malloc(sizeof(Tree_t));
  init_set(tree);
  insert(tree, 5);
  insert(tree, 9);
  insert(tree, 15);
  insert(tree, 1);
  insert(tree, 2);
  insert(tree, 2);
  insert(tree, 4);
  disp(tree);
}
