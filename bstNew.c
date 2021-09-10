#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *newNode(int key)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->data = key;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}
struct node *insert(struct node *node, int key)
{
    if (node == NULL)
        return newNode(key);
    else if (node->data > key)
        node->left = insert(node->left, key);
    else if (node->data < key)
        node->right = insert(node->right, key);

    return node;
}
void preorder(struct node *node)
{
    if (node != NULL)
    {
        printf("%d->", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(struct node *node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d->", node->data);
        inorder(node->right);
    }
}

//finding the inorder successor
struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *node, int data)
{
    if (node == NULL)
        return node;

    if (data < node->data)
        node->left = deleteNode(node->left, data);
    else if (data > node->data)
        node->right = deleteNode(node->right, data);

    else
    {
        //for one or zero child
        if (node->left == NULL)
        {
            struct node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct node *temp = node->left;
            free(node);
            return temp;
        }

        // for a node with two children
        struct node *temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}

int main()
{
    struct node *myNode = newNode(8);

    myNode = insert(myNode, 3);
    myNode = insert(myNode, 10);
    myNode = insert(myNode, 1);
    myNode = insert(myNode, 6);
    myNode = insert(myNode, 7);
    myNode = insert(myNode, 11);
    myNode = insert(myNode, 14);
    myNode = insert(myNode, 4);

    printf("Inorder traversal: ");
    inorder(myNode);
    printf("\nPreorder traversal: ");
    preorder(myNode);

    printf("\nAfter deleting 10\n");
    myNode = deleteNode(myNode, 10);
    printf("\nInorder traversal: ");
    inorder(myNode);
    printf("\nPreorder traversal: ");
    preorder(myNode);
}
