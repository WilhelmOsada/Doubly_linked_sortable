#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include <string.h>
struct doubly_linked_list_t* dll_create()
{
    struct doubly_linked_list_t *ret = calloc(1,sizeof(struct doubly_linked_list_t));
    if(!ret)    return NULL;
    return ret;
}
int dll_size(const struct doubly_linked_list_t* dll)
{
    if (!dll) return -1;
    struct node_t *temp = dll->tail;
    int size = 0;
    while(temp)
    {
        size++;
        temp = temp->prev;
    }
    return size;
}
int dll_push_back(struct doubly_linked_list_t* dll, int value)
{
    if(!dll)    return 1;
    if(!dll->tail)
    {
        dll->tail = calloc(1,sizeof(struct node_t));
        if(!dll->tail)  return 2;
        dll->tail->data = value;
        dll->head = dll->tail;
        dll->head->next = NULL;
        dll->head->prev = NULL;
    }
    else
    {
        dll->tail->next = calloc(1,sizeof(struct node_t));
        if(!dll->tail->next)  return 2;
        dll->tail->next->prev = dll->tail;
        dll->tail = dll->tail->next;
        dll->tail->next = NULL;
        dll->tail->data = value;
    }
    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value)
{
    if(!dll)    return 1;
    if(!dll->head)
    {
        dll->head = calloc(1,sizeof(struct node_t));
        if(!dll->head)  return 2;
        dll->head->data = value;
        dll->tail = dll->head;
        dll->head->next = NULL;
        dll->head->prev = NULL;
    }
    else
    {
        dll->head->prev = calloc(1,sizeof(struct node_t));
        if(!dll->head->prev)  return 2;
        dll->head->prev->next = dll->head;
        dll->head = dll->head->prev;
        dll->head->prev = NULL;
        dll->head->data = value;
    }
    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if (!dll || !dll->head)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if(dll_size(dll) == 1)
    {
        int ret = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code) *err_code = 0;
        return ret;
    }
    else
    {
        struct node_t *temp = dll->head;
        int ret = temp->data;
        dll->head = dll->head->next;
        if (dll->head) dll->head->prev = NULL;
        free(temp);
        if(err_code) *err_code = 0;
        return ret;
    }
}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if (!dll || !dll->tail)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if(dll_size(dll) == 1)
    {
        int ret = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code) *err_code = 0;
        return ret;
    }
    else
    {
        struct node_t *temp = dll->tail;
        int ret = temp->data;
        dll->tail = dll->tail->prev;
        if (dll->tail) dll->tail->next = NULL;
        free(temp);
        if(err_code) *err_code = 0;
        return ret;
    }

}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code)
{
    if (!dll || !dll->tail)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if(err_code) *err_code = 0;
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code)
{
    if (!dll || !dll->head)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if(err_code) *err_code = 0;
    return dll->head->data;
}
struct node_t* dll_begin(struct doubly_linked_list_t* dll)
{
    if(!dll)    return NULL;
    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll)
{
    if(!dll)    return NULL;
    return dll->tail;
}


int dll_is_empty(const struct doubly_linked_list_t* dll)
{
    if(!dll)    return -1;
    if(dll->head || dll->tail)  return 0;
    return 1;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if(!dll)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    struct node_t *temp = dll->head;
    for(unsigned int i = 0 ; i < index ; i++)
    {
        temp = temp->next;
        if(!temp)
        {
            if(err_code) *err_code = 1;
            return 1;
        }
    }
    if(err_code) *err_code = 0;
    return temp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value)
{
    if (!dll) return 1;
    int size = dll_size(dll);
    if((unsigned int)size < index) return 1;
    if (index == (unsigned int)size)
    {
        int ret = dll_push_back(dll, value);
        return ret;
    }
    if (index == 0)
    {
        int ret = dll_push_front(dll, value);
        return ret;
    }
    struct node_t *temp = dll->head;
    for(unsigned int i = 0 ; i < index ; i++) temp = temp->next;
    struct node_t *ins = calloc(1,sizeof(struct node_t));
    if (!ins) return 2;
    ins->data = value;
    ins->prev = temp->prev;
    ins->next = temp;
    temp->prev->next = ins;
    temp->prev = ins;
    return 0;
}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if(!dll)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    int size = dll_size(dll);
    if(size <= 0)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if((unsigned int)size <= index)
    {
        if(err_code) *err_code = 1;
        return 1;
    }
    if (index == 0)
    {
        int ret = dll_pop_front(dll, err_code);
        return ret;
    }
    if (index == (unsigned int)size - 1)
    {
        int ret = dll_pop_back(dll, err_code);
        return ret;
    }
    struct node_t *del = dll->head;
    for(unsigned int i = 0 ; i < index ; i++)
    {
        del = del->next;
        if(!del)    return 1;
    }
    struct node_t *nxt = del->next;
    struct node_t *prv = del->prev;
    int ret = del->data;
    free(del);
    if(prv) prv->next = nxt;
    if(nxt) nxt->prev = prv;
    if(err_code) *err_code = 0;
    return ret;
}

void dll_clear(struct doubly_linked_list_t* dll)
{
    if(dll)
    {
        struct node_t *del = dll->head;
        while(del)
        {
            dll->head = del;
            del = del->next;
            free(dll->head);
        }
        dll->head = NULL;
        dll->tail = NULL;
    }
}

void dll_display(const struct doubly_linked_list_t* dll)
{
    if(dll && dll->head)
    {
        struct node_t *disp = dll->head;
        for( ; disp ; disp = disp->next) printf("%d ",disp->data);
        printf("\n");
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll)
{
    if(dll && dll->tail)
    {
        struct node_t *disp = dll->tail;
        for( ; disp ; disp = disp->prev) printf("%d ",disp->data);
        printf("\n");
    }
}
int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(!dll1 || !dll2) return 1;
    if(!dll2->head && !dll1->head) return 1;
    if(!dll2->head && dll1->head)   return 0;
    if(!dll1->head && dll2->head)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    struct node_t* next;
    struct node_t* add_next;
    struct node_t* cur = dll1->head;
    struct node_t* add = dll2->head;
    for(int i = 0 ; i < dll_size(dll1) ; i++)
    {
        if(!cur || !add)    break;
        next = cur->next;
        add_next = add->next;

        cur->next = add;
        add->prev = cur;
        if(next)
        {
            add->next = next;
            next->prev = add;
        }

        cur = next;
        add = add_next;
    }
    if(!cur) dll1->tail = dll2->tail;
    dll2->tail = NULL;
    dll2->head = NULL;
    return 0;
}
int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(!dll1 || !dll2) return 1;
    if(!dll2->head) return 0;
    if(!dll1->head)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    dll1->head->prev = dll2->tail;
    dll2->tail->next = dll1->head;
    dll1->head = dll2->head;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}
int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(!dll1 || !dll2) return 1;
    if(!dll2->head) return 0;
    if(!dll1->tail)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    dll1->tail->next = dll2->head;
    dll2->head->prev = dll1->tail;
    dll1->tail = dll2->tail;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}
void node_switch(struct node_t *left, struct node_t *right)
{
    struct node_t *temp = left->prev;
    if (temp)
    {
        temp->next = right;
        right->prev = temp;
    }
    else right->prev = NULL;
    temp = right->next;
    if (temp)
    {
        temp->prev = left;
        left->next = temp;
    }
    else left->next = NULL;
    left->prev = right;
    right->next = left;
}
int dll_sort_asc(struct doubly_linked_list_t* dll)
{
    if(!dll || !dll->head)    return 1;
    for(int i = 0 ; i < 2 * dll_size(dll) ; i++)
    {
        struct node_t *node = dll->head;
        while(1)
        {
            if(!node || !node->next)    break;
            if(node->data > node->next->data)
            {
                if(node == dll->head) dll->head = node->next;
                if(node->next == dll->tail) dll->tail = node;
                node_switch(node,node->next);
            }else node = node->next;
        }
    }
    return 0;
}
int dll_sort_desc(struct doubly_linked_list_t* dll)
{
    if(!dll || !dll->head)    return 1;
    for(int i = 0 ; i < 2 * dll_size(dll) ; i++)
    {
        struct node_t *node = dll->head;
        while(1)
        {
            if(!node || !node->next)    break;
            if(node->data < node->next->data)
            {
                if(node == dll->head) dll->head = node->next;
                if(node->next == dll->tail) dll->tail = node;
                node_switch(node,node->next);
            }else node = node->next;
        }
    }
    return 0;
}