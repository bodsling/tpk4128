#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
    struct list* list_t = NULL;
    list_t = (struct list*)malloc(sizeof(struct list));
    list_t->head = NULL;
    list_t->tail = NULL;
    list_t->length = 0;
    return list_t;

}

void list_delete(list_t list)
{
    free(list);

}

void list_insert(list_t list, int index, int data)
{
    struct node * counter = list->head;
    int n = 0;
    while (n< index)
    {
        counter = counter->next;
        n+=1;
    }
    struct node* new_node  = (struct node*)malloc(sizeof(struct node));
    new_node->next = counter->next;
    new_node->data = data;
    new_node->prev = counter;
    counter->next->prev = new_node;
    counter->next = new_node;
    list->length++;

}

void list_append(list_t list, int data)
{
    struct node* new_node  = (struct node*)malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    new_node->prev = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->length ++;
    }else if (list->tail==NULL)
    {
        list->tail = new_node;
        list->tail->prev = list->head;
        list->head->next = new_node; 
        list->length++;
    }else
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
        list->length ++;

    }
    
}

void list_print(list_t list)
{

    struct node * counter = list->head;
    while (counter != NULL)
    {
        printf("%i\n",counter->data);
        counter = counter->next;
    }
    

}

long list_sum(list_t list)
{
    struct node * counter = list->head;
    long sum = 0;
    while (counter != NULL)
    {
        sum += counter->data;
        counter = counter->next;
    }
    return sum;

}

int list_get(list_t list, int index)
{
    struct node * counter = list->head;
    int n = 0;
    while (n< index)
    {
        counter = counter->next;
        n+=1;
    }
    return counter->data;

}

int list_extract(list_t list, int index)
{
    struct node * counter = list->head;


    if (list->length == 1)
    {
        
        list->length--;
        free(list->head);
        list->head=NULL;
        return counter->data;
    }


    if (list->length == 2)
    {
        if(index == 0)
        {
            free(list->head);
            list->head = list->tail;
            list->head->prev = NULL;
            list->head->next = NULL;
            list->tail = NULL;
            list->length = 1;
            return counter->data;
        }else
        {

            counter = list->tail;
            list->head->prev = NULL;
            list->head->next = NULL;
            free(list->tail);
            list->tail = NULL;
            list->length = 1;
            return counter->data;
        }
        
    }

    if (index == 0)
    {
        
        counter->next->prev = NULL;
        list->head = counter->next;
        list->length--;
        free(counter);
        return counter->data;
    }
    int n = 0;
    while (n< index)
    {
        counter = counter->next;
        n+=1;
    }
    if (counter->next == NULL)
    {
        counter->prev->next = NULL;
        list->tail = counter->prev;
        list->length--;
        free(counter);
        return counter->data;
    }else
    {
        counter->prev->next = counter->next;
        counter->next->prev = counter->prev;
        list->length--;
        free(counter);
        return counter->data;
    }
    
    

    
}
