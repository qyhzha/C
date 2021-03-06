#include "LinkList.h"
#include <stdio.h>

int main()
{
    LinkList *list = LinkListCreate();

    if (list != NULL)
    {
        int i;

        printf("len = %d\n", LinkListLength(list));

        for (i = 0; i < 10; i++)
        {
            LinkListInsertBack(list, i);
        }

        printf("len = %d\n", LinkListLength(list));

        for (i = 0; i < 5; i++)
        {
            LinkListDelete(list, 0, NULL);
        }

        printf("len = %d\n", LinkListLength(list));

        i = 0;
        printf("begin printf\n");
        LinkListForEach(list)
        {
            printf("list[%d] = %d\n", i, LinkListEntry(list));
        }
        printf("end printf\n");

        LinkListDestroy(list);
    }

    return 0;
}