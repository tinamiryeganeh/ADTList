#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

// Type 1 (Recommend!!): List is a list with extra node structure
typedef struct NodeObj
{
    int data;
    struct NodeObj *next;
} NodeObj;
typedef NodeObj *Node;

typedef struct ListObj
{
    Node head;
    int length;
} ListObj;

//constructor for node
Node newNode(int x)
{
    Node nptr = malloc(sizeof(NodeObj));
    nptr->next = NULL;
    nptr->data = x;
    return nptr;
}
// Dectructor for Node
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

//constructor for list
List newList(void)
{
    List lptr = malloc(sizeof(ListObj));
    lptr->head = NULL;
    lptr->length = 0;
    return lptr;
}

// Destructor for list
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        // clear(*pL);
        system("clear");
        free(*pL);
        *pL = NULL;
    }
}
int length(List L)
{
    if (L == NULL)
    {
        printf("In length()\n");
        printf("List Error: calling getLength() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}
// returns index of element with highest value,
// throws an error if L is empty, or L does not exist.
// return value varies from 0..length(L)-1
int max(List L)
{
    Node ptr = L->head;
    int maxData = ptr->data;
    int index = 0;
    if (length(L) == 0)
    {
        printf("In max()\n");
        printf("List Error: calling getLength() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (L->length) - 1; i++)
    {
        if (maxData < ptr->next->data)
        {
            maxData = ptr->next->data;
            index = i + 1;
        }
        ptr = ptr->next;
    }
    return index;
}

// returns the index of first occurence of i in L.
// returns -1 if i is not found in L.
int find(List L, int i)
{
    int foundedIndex = -1;
    Node ptr = L->head;
    for (int counter = 0; counter < (L->length) - 1; counter++)
    {
        if (ptr->data == i)
        {
            foundedIndex = counter;
        }
        ptr = ptr->next;
    }
    return foundedIndex;
}

// deletes the ith element of L and return the data of it.
// throws an error if L has less than i+1 elements.
int delElement(List L, int i)
{
    int len = L->length;
    Node ptr = L->head;
    Node tempPtr;
    int deletedValue;
    if (L == NULL){
        printf("In delElement()\n");
        printf("List Error: calling getLength() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (i == 0)
    {
        //delete head
        deletedValue = ptr->data;
        L->head = ptr->next;
        free(ptr);
        L->length--;
    }
    else if (i >= len)
    {
        printf("Error");
    }
    else
    {
        for (int count = 1; count <= i; count++)
        {
            tempPtr = ptr->next;           
            ptr->next = ptr->next->next;
            deletedValue = tempPtr->data;
            free(tempPtr);
            // free(tempPtr->next);
            L->length--;
            ptr = ptr->next;
        }
    }
    return deletedValue;
}

void appendList(List L, int i)
{
    //printf("in append list\n");
    Node N = newNode(i);
    Node ptr = L->head;
    if (ptr == NULL)
    {
        L->head = N;
        N->next = NULL;
        L->length = 1;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = N;
        N->next = NULL;
        L->length++;
    }
}

//Print Polynomial sorted form
void printList(List L)
{
    Node cue = L->head;
    while (cue != NULL)
    {
        printf("%d, ", cue->data);
        cue = cue->next;
    }
    printf("\n");
}

