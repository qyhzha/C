#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *reverse(struct ListNode *node, struct ListNode *next)
{
    if(next == NULL)
    {
        return node;
    }

    struct ListNode *pHead = reverse(next, next->next);

    next->next = node;

    return pHead;
}

struct ListNode* ReverseList(struct ListNode* pHead )
{
    return reverse(NULL, pHead);
}

int main()
{
    struct ListNode *head =  (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *node = head;

    node->val = -1;

    for(int i = 0; i < 10; i++)
    {
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));

        node = node->next;
        node->val = i;
        node->next = NULL;
    }

    head = ReverseList(head);
    node = head;

    while(node != NULL)
    {
        printf("data(%d)\r\n", node->val);

        node = node->next;
    }

    return 0;
}
