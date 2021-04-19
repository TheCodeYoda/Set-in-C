#include<stdio.h>
#include<stdlib.h>
#include"bst.h"


Node_t* create_node(int data) {
    Node_t* node = malloc(sizeof(Node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
}


Node_t* insert(Node_t* root, int data) {
    if(root==NULL) {
	return create_node(data);
    }
    if(data<root->data)
	root->left = insert(root->left,data);
    else if(data>root->data)
	root->right = insert(root->right,data);
    return root;
    
}

void init_root(BST_t* tree) {
    tree->root=NULL;
}

void inorder(Node_t* node) {
    if(node==NULL)
	return;
    inorder(node->left);
    printf("%d ",node->data);
    inorder(node->right);
}

void traverse(BST_t* tree) {
    inorder(tree->root);
}

int main() {
    BST_t* tree = malloc(sizeof(BST_t));
    init_root(tree);
    tree->root = insert(tree->root,5);
    insert(tree->root,9);
    insert(tree->root,15);
    insert(tree->root,1);
    insert(tree->root,2);
    insert(tree->root,2);
    insert(tree->root,4);
    traverse(tree);
    
}
