#include <stdio.h>
#include <stdlib.h>

struct BTNode
{
    int data;           //使用int，方便调试
    struct BTNode *left;
    struct BTNode *right;
};

int copyData(int data)
{
    int ret = 0;

    //根据实际需求决定采用深拷贝或者浅拷贝。
    ret = data;

    return ret;
}

struct BTNode *copy(struct BTNode *root)
{
    struct BTNode *ret = NULL;

    if (root == NULL)
    {
        return NULL;
    }

    ret = (struct BTNode *)malloc(sizeof(struct BTNode));
    if (ret == NULL)
    {
        return NULL;
    }

    if (root->left != NULL)
    {
        ret->left = copy(root->left);
        if (ret->left == NULL)
        {
            //拷贝左子树失败
            free(ret);
            return NULL;
        }
    }
    else
    {
        ret->left = NULL;
    }

    if (root->right != NULL)
    {
        ret->right = copy(root->right);
        if (ret->right == NULL)
        {
            //拷贝右子树失败
            if (ret->left != NULL)
            {
                free(ret->left);
            }
            free(ret);
            return NULL;
        }
    }
    else
    {
        ret->right = NULL;
    }

    ret->data = copyData(root->data);

    return ret;
}

void printTree(struct BTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("*%p = %d\r\n", root, root->data);

    printTree(root->left);
    printTree(root->right);
}

struct BTNode *createNode(int i)
{
    struct BTNode *ret = NULL;

    ret = (struct BTNode *)malloc(sizeof(struct BTNode));
    if (ret == NULL)
    {
        return NULL;
    }

    ret->data = i;
    ret->right = NULL;
    ret->left = NULL;

    return ret;
}

void freeTree(struct BTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main()
{
    struct BTNode *root = createNode(0);
    struct BTNode *rootLeft = createNode(1);
    struct BTNode *rootRight = createNode(2);
    struct BTNode *rootLeftRight = createNode(3);
    struct BTNode *rootRightLeft = createNode(4);
    struct BTNode *rootRightLeftRigth = createNode(5);

    root->left = rootLeft;
    root->right = rootRight;
    rootLeft->right = rootLeftRight;
    rootRight->left = rootRightLeft;
    rootRightLeft->right = rootRightLeftRigth;

    struct BTNode *newRoot = copy(root);
    if (newRoot == NULL)
    {
        printf("copy root fail. please check memory.");
        return 0;
    }

    printTree(root);
    printTree(newRoot);

    freeTree(root);
    freeTree(newRoot);

    return 0;
}