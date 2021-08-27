#include <stdio.h>
#include <stdlib.h>
typedef struct BST
{
    int data;
    struct BST *left;
    struct BST *right;
} node;

node *create()
{
    node *tmp;
    tmp = (node *)malloc(sizeof(node));
    printf("Enter the data: ");
    scanf("%d", &tmp->data);
    tmp->left = tmp->right = NULL;
    return tmp;
}
void insert(node *root, node *tmp)
{
    if (tmp->data < root->data)
    {
        if (root->left != NULL)
            insert(root->left, tmp);
        else
        {
            root->left = tmp;
        }
    }
    if (tmp->data > root->data)
    {
        if (root->right != NULL)
            insert(root->right, tmp);
        else
        {
            root->right = tmp;
        }
    }
}
void preorder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void postorder(node *root)
{
    if (root != NULL)
    {
        preorder(root->left);
        preorder(root->right);
        printf("%d ", root->data);
    }
}
void order(node *root)
{
    int input;
    printf("Which order do you want to print:\n");
    printf("1. preorder\n2. inorder\n3. postorder\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
    {
        printf("preorder : ");
        preorder(root);
        printf("\n");
        break;
    }
    case 2:
    {
        printf("inorder : ");
        inorder(root);
        printf("\n");
        break;
    }
    case 3:
    {
        printf("postorder : ");
        postorder(root);
        printf("\n");
        break;
    }
    }
    printf("\n");
}
int findMax(node *root)
{
    if (root->right != NULL)
        findMax(root->right);
    else
        return root->data;
}
int findMin(node *root)
{
    if (root->left != NULL)
        findMin(root->left);
    else
        return root->data;
}
node *minValueNode(node *node)
{
    struct BST *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}
node *deleteNode(node *root, int key)
{
    // base case
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }

        node *temp = minValueNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main()
{
    char move;
    node *root = NULL, *tmp;
    do
    {
        tmp = create();
        if (root == NULL)
            root = tmp;
        else
            insert(root, tmp);
        order(root);
        printf("Do you want to add more data?(y/n): ");
        getchar();
        scanf("%c", &move);
    } while (move == 'Y' || move == 'y');
    printf("The maximum number is %d\n", findMax(root));
    printf("The minimum number is %d\n", findMin(root));
    deleteNode(root, 5);
    printf("Tree after deleting in inorer is: ");
    inorder(root);
    return 0;
}
