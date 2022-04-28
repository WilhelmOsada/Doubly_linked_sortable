#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
int main()
{
    int val = 0;
    struct doubly_linked_list_t *dll1 = dll_create();
    if(!dll1)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartosci 1:");
    while(1)
    {
        if(!scanf("%d",&val))
        {
            printf("Incorrect input");
            dll_clear(dll1);
            free(dll1);
            return 1;
        }
        if(val == -1)   break;
        if(dll_push_back(dll1,val))
        {
            printf("Failed to allocate memory");
            dll_clear(dll1);
            free(dll1);
            return 8;
        }
    }
    while(getchar()!='\n');
    if(dll_size(dll1) < 1)
    {
        printf("Not enough data available");
        dll_clear(dll1);
        free(dll1);
        return 3;
    }
    int choice = 0;
    printf("Co chcesz zrobic?");
    if(!scanf("%d",&choice))
    {
        printf("Incorrect input");
        dll_clear(dll1);
        free(dll1);
        return 1;
    }
    if(choice == 0)
    {
        dll_sort_asc(dll1);
        dll_display(dll1);
        dll_display_reverse(dll1);
    }
    else if(choice == 1)
    {
        dll_sort_desc(dll1);
        dll_display(dll1);
        dll_display_reverse(dll1);
    }
    else
    {
        printf("Incorrect input data");
        dll_clear(dll1);
        free(dll1);
        return 2;
    }
    dll_clear(dll1);
    free(dll1);
    return 0;
}