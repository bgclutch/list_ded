#include <stdio.h>
#include <stdlib.h>

#include "list_headers/list.h"


List_Errors ctor_list(List* list)
{
    list = (List*)calloc(sizeof(List), LIST_SIZE);

    list->data = LIST_POISON;

    list->next = 0;
    list->prev = 0;
    list->elem_index = 0;

    return LIST_IS_OK;
}


List_Errors dtor_list(List* list)
{
    free(list);

    list = nullptr;

    return LIST_DTOR_ERR;
}


void list_dump(List *list, FILE* dump_file)
{
    fprintf(dump_file, "list begin:0x%p\n"
                       "list end:0x%p\n\n", list, list + sizeof(*list));

    for(size_t index_list = LIST_PHANTOM_INDEX; index_list < LIST_SIZE; index_list++)
    {
        List* place = list + index_list;

        fprintf(dump_file, "list value: %d\n"
                           "list prev: %d\n"
                           "LIST CURRENT: %d\n"
                           "list next: %d\n", place->data, place->prev, place->elem_index, place->next);
    }

}


List_Errors list_is_error(const List_Errors result, const char* name, const size_t line)
{
    if(result != LIST_IS_OK)
    {
        fprintf(stderr, "Error here: %s:%lu\n\n", name, line);
        return MACRO_ERR;
    }

    return MACRO_GOOD;
}