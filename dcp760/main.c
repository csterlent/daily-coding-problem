#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int entry;
    struct Node *next;
};

struct LinkedList
{
    struct Node *head;
};

void append(struct LinkedList *list, int entry);
void shuffle(struct LinkedList *input);
void printContents(struct LinkedList input);

int main()
{
    struct LinkedList mylist;
    mylist.head = NULL;
    append(&mylist, 7);
    append(&mylist, 6);
    append(&mylist, 5);
    append(&mylist, 4);
    append(&mylist, 3);
    append(&mylist, 2);
    append(&mylist, 1);
    append(&mylist, 0);
    printContents(mylist);
    shuffle(&mylist);
    printContents(mylist);
    shuffle(&mylist);
    printContents(mylist);
    shuffle(&mylist);
    printContents(mylist);
    shuffle(&mylist);
    printContents(mylist);
}

void append(struct LinkedList *list, int entry)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->entry = entry;
    new->next = list->head;
    list->head = new;
}

void shuffle(struct LinkedList *input)
{
    if (!input->head)
    {
        return;
    }
    // Turn the linked list into a loop by attaching tail to head
    int count = 1;
    struct Node *n = input->head;
    while (n->next)
    {
        n = n->next;
        count++;
    }
    n->next = input->head;

    // Randomly decide what the element after n should be, then advance n and repeat
    for (int i = 0; i < count; i++)
    {
        int steps = arc4random_uniform(count-i-1);
        struct Node *before = n;
        for (int j = 0; j < steps; j++)
        {
            before = before->next;
        }
        struct Node *insert = before->next;
        before->next = before->next->next;
        insert->next = n->next;
        n->next = insert;
        n = insert;
    }
    
    // The elements have been randomized, except that input->head has not changed
    int steps = arc4random_uniform(count);
    for (int i = 0; i < steps; i++)
    {
        n = n->next;
    }
    struct Node *myhead = n->next;
    n->next = NULL;
    input->head = myhead;
}

void printContents(struct LinkedList input)
{
    struct Node *n = input.head;
    while (n)
    {
        printf("%d ", n->entry);
        n = n->next;
    }
    printf("\n");
}