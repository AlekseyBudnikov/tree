#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct TREE
{
    int num;
    TREE *left;
    TREE *right;
};

TREE *head;

TREE *create(TREE *head,TREE *event,int num)
{
    if(!event)
    {
        event=(struct TREE *)malloc(sizeof(struct TREE));
        event->left=NULL;
        event->right=NULL;
        event->num=num;
        if(!head)
            return event;
        if(num<head->num)
            head->left=event;
        else
            head->right=event;
        return event;
    }

    if(num<event->num)
        create(event,event->left,num);
    else
        create(event,event->right,num);

    return head;
}

void list(TREE *head,int s,int j)
{
    int i;

    if(!head)
        return;

    switch(j)
    {
        case 0:
            list(head->right,s+1,j);
            for(i=0;i<s;++i)
                printf(" ");
            if(head->num)
                printf("%d\n",head->num);
            list(head->left,s+1,j);
            break;
        case 1:
            printf("%d ",head->num);
            list(head->left,s,j);
            list(head->right,s,j);
            break;
    }
}

TREE *find(TREE *head,int request)
{
    while(head->num!=request)
    {
        if(request<head->num)
            head=head->left;
        else
            head=head->right;
        if(head==NULL)
            break;
    }

    if(head!=NULL)
        printf("\nElement is found\n");
    else
        printf("\nElement not found\n");
}

TREE *del(TREE *head,int request)
{
    TREE *free_1;
    TREE *free_2;

    if(!head)
        {
            printf("\nElement not found\n");
            return head;
        }

    if(head->num==request)
    {
        if(head->left==head->right)
        {
            free(head);
            return NULL;
        }
        else if(head->left==NULL)
        {
            free_1=head->right;
            free(head);
            return free_1;
        }
        else if(head->right==NULL)
        {
            free_1=head->left;
            free(head);
            return free_1;
        }
        else
        {
            free_2=head->right;
            free_1=head->right;
            while(free_1->left)
                free_1=free_1->left;
            free_1->left=head->left;
            free(head);
            return free_2;
        }
    }

    if(head->num<request)
        head->right=del(head->right,request);
    else
        head->left=del(head->left,request);

    return head;
}

int menu(void);

int main()
{
    TREE *head=NULL;

    int i,n,req;

    for(;;)
    {
        switch(menu())
        {
            case 1:
                printf("Enter number: ");
                scanf("%d",&n);
                head=create(head,head,n);
                break;
            case 2:
                for(i=0;i<2;i++)
                    list(head,0,i);
                break;
            case 3:
                printf("Enter request: ");
                scanf("%d",&req);
                find(head,req);
                break;
            case 4:
                printf("Enter request: ");
                scanf("%d",&req);
                head=del(head,req);
                break;
            case 5:
                exit(0);
                break;
        }
    }

    return 0;
}

int menu()
{
    int c;

    printf("\n1. Add\n");
    printf("2. List\n");
    printf("3. Find\n");
    printf("4. Delete\n");
    printf("5. Exit\n");

    do
    {
        printf("\nCase: ");
        scanf("%d",&c);
        printf("\n");
    }
    while(c<0 || c>5);

    return c;
}
