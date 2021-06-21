//
// file: bst.c
// Program for creating Binary Search Trees and traversing through them
//
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//Builds BSTs
void tree_build( TreeNode **rootptr, const int data[], const int num)
{
    for(int i = 0; i < num; i++)
    {
        TreeNode *node, *parent;
        node = (TreeNode*)malloc(sizeof(TreeNode));
        node->data = data[i];
        node->left = node->right = NULL;
        TreeNode* curr = *rootptr;
        if(rootptr == NULL)
            rootptr = &node;
        else
        {
            while(curr)
            {
                parent = curr;
                if(node->data > curr->data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
            if(node->data > parent->data)
                parent->right = node;
            else if(node->data < parent->data)
                parent->left = node;
            else //value in the tree
                free(node);
        }
    }
}


//traverses thruogh the BST with a given traversal type
void tree_traverse(const TreeNode* root, const TraversalType type)
{

    if(type == PREORDER)
    {
        if(root != NULL)
        {
            printf("%d\n",root->data);
            tree_traverse(root->left, PREORDER);
            tree_traverse(root->right, PREORDER);
        }
    }
    else if(type == INORDER)
    {
        if(root != NULL)
        {
            tree_traverse(root->left, INORDER);
            printf ("%d\n",root->data);
            tree_traverse(root->right, INORDER);
        }

    }
    else if(type == POSTORDER)
    {
        if(root != NULL)
        {
            tree_traverse(root->left, POSTORDER);
            tree_traverse(root->right, POSTORDER);
            printf("%d\n",root->data);
        }

    }

}


//Cleans up memory of the BST
void tree_destroy(TreeNode *root)
{
  if (root==NULL)
    return;

  tree_destroy(root->left);
  tree_destroy(root->right);

  free(root);
}
