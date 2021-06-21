// file: treetest.c
//
// Description: Used to take input integers, create a Binary Search Tree
// based on them, and traverse through that BST
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"



// Takes input from user and return Binary Search Tree based on the
// values and prints preorder, inorder, and postorder traversals
// @param argc number of command line tokens
// @param argv array of C string values, the command line arguments
//
// @return 0 to tell the OS that the process ran successfully, OR
//         return 1 to tell the OS that there was an issue with
//         the usage of the program
int main(int argc,  char* argv[])
{
    if(argc != 2)
    {
        printf("usage: treetest #\n");
        return 1;
    }
    else if( (atoi(argv[1])) < 0)
    {
        printf("error: # must be greater than 0\n");
        return 1;
    }

    int MAX_VALUES = atoi(argv[1]);
    int data[MAX_VALUES];


    printf("Enter %d integer values to place in tree:\n", MAX_VALUES);

    for(int j = 0; j < MAX_VALUES; j++)
    {
        scanf("%d", &data[j]);
    }

    TreeNode *treetop = (TreeNode*)malloc(sizeof(TreeNode));
    treetop->right = treetop->left =  NULL;
    treetop->data = data[0];
    tree_build( &treetop, data, MAX_VALUES);

    printf("Input values:\n");
    for(int i = 0; i < MAX_VALUES; i++)
    {
        printf("%d\n", data[i]);
    }

    printf("Preorder:\n");
    tree_traverse(treetop, PREORDER);

    printf("Inorder:\n");
    tree_traverse(treetop, INORDER);

    printf("Postorder:\n");
    tree_traverse(treetop, POSTORDER);

    tree_destroy(treetop);

    return 0;
}

