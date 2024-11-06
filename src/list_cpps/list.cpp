#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../../src/list_headers/list.h"


List_Errors ctor_list(Node_Array* My_List)
{
    assert(My_List);
    assert(!My_List->list);

    My_List->list = (List*)calloc(sizeof(List), (size_t)LIST_SIZE);

    if(My_List->list == nullptr)
        return LIST_CTOR_ERR;

    My_List->free = LIST_START_INDEX;

    default_list_fill(My_List);

    return LIST_IS_OK;
}

List_Errors dtor_list(Node_Array* My_List)
{
    free(My_List->list);

    My_List->list = nullptr;


    if(My_List->list != nullptr)
        return LIST_DTOR_ERR;

    return LIST_IS_OK;
}


List_Errors list_is_error(const List_Errors result, const char* name, const size_t line)
{
    assert(name);

    if(result != LIST_IS_OK)
    {
        fprintf(stderr, "Error here: %s:%lu\n\n", name, line);
        return MACRO_ERR;
    }

    return MACRO_GOOD;
}


void default_list_fill(Node_Array* My_List)
{
    assert(My_List);
    assert(My_List->list);

    My_List->list[LIST_PHANTOM_INDEX].data = LIST_POISON;

    My_List->list[LIST_PHANTOM_INDEX].next = 0;
    My_List->list[LIST_PHANTOM_INDEX].prev = 0;

    for(int index_list = LIST_START_INDEX; index_list < LIST_SIZE; index_list++)
    {
        My_List->list[index_list].data = LIST_POISON;
        My_List->list[index_list].prev = LIST_FREE_ATTR;
        My_List->list[index_list].next = LIST_PHANTOM_INDEX;
        My_List->list[index_list - 1].next = index_list;

        My_List->list[LIST_PHANTOM_INDEX].prev = LIST_PHANTOM_INDEX;
        My_List->list[LIST_PHANTOM_INDEX].next = LIST_PHANTOM_INDEX;
    }

}


List_Errors list_insert_after(Node_Array* My_List, const int pre_insert_index, const ListElem_t elem)
{
    assert(My_List);
    assert(My_List->list);

    if(fabs(pre_insert_index) >= LIST_SIZE)
        return INSERTION_ERROR;

    if(My_List->free == LIST_PHANTOM_INDEX)
    {
        fprintf(stderr, "NO MORE SPACE FOR INSERTIONS\n");
        return INSERTION_ERROR;
    }


    int insert_index = My_List->free;   // head (first free spot)

    My_List->free = My_List->list[My_List->free].next;

    My_List->list[insert_index].data = elem;                                    // put new elem to data
    My_List->list[insert_index].prev = pre_insert_index;                        // change prev for insert
    My_List->list[insert_index].next = My_List->list[pre_insert_index].next;    // change next for insert
    My_List->list[pre_insert_index].next = insert_index;                        // change next for pre_insert

    int tail_saver = My_List->list[LIST_PHANTOM_INDEX].prev;

    int following_index = My_List->list[insert_index].next;
    My_List->list[following_index].prev = My_List->list[pre_insert_index].next;   // change prev for post_insert

    My_List->list[LIST_PHANTOM_INDEX].next = insert_index;
    My_List->list[LIST_PHANTOM_INDEX].prev = tail_saver;

    if(My_List->list[insert_index].prev == LIST_PHANTOM_INDEX)
        My_List->list[LIST_PHANTOM_INDEX].prev = insert_index;

    return LIST_IS_OK;
}


List_Errors list_erase(Node_Array* My_List, const int erase_index) // make elem free
{
    assert(My_List);
    assert(My_List->list);

    if(My_List->list[LIST_PHANTOM_INDEX].next == 0)
    {
        fprintf(stderr, "NOTHING TO ERASE\n");
        return ERASING_ERROR;
    }

    if(fabs(erase_index) >= LIST_SIZE || My_List->list[erase_index].prev == LIST_FREE_ATTR)
        return ERASING_ERROR;

    int index_prev = My_List->list[erase_index].prev;
    int index_next = My_List->list[erase_index].next;

    My_List->list[index_prev].next = My_List->list[erase_index].next; // make prev elem point to next
    My_List->list[index_next].prev = My_List->list[erase_index].prev; // make next elem point to prev

    My_List->list[erase_index].prev = LIST_FREE_ATTR; // make erased elem empty by its attribute

    LIST_ERR(find_last_free(My_List, erase_index), FIND_LAST_FREE_ERR);

    My_List->list[erase_index].data = LIST_POISON;    // make erased elem empty


    if(My_List->list[index_next].prev == LIST_PHANTOM_INDEX)
        My_List->list[LIST_PHANTOM_INDEX].prev = index_next;

    return LIST_IS_OK;
}


List_Errors find_last_free(Node_Array* My_List, const int new_last_free)
{
    int list_index = My_List->free;

    if(list_index == LIST_PHANTOM_INDEX && My_List->list[list_index].next != LIST_PHANTOM_INDEX)
    {
        My_List->free = new_last_free;
        My_List->list[new_last_free].next = LIST_PHANTOM_INDEX;
        return LIST_IS_OK;
    }

    while(My_List->list[list_index].next != LIST_PHANTOM_INDEX)
    {
        if(My_List->list[list_index].prev != LIST_FREE_ATTR)
            return FIND_LAST_FREE_ERR;

        list_index = My_List->list[list_index].next;
    }

    My_List->list[list_index].next = new_last_free;
    My_List->list[new_last_free].next = LIST_PHANTOM_INDEX;

    return LIST_IS_OK;
}


List_Errors erase_list_tail(Node_Array* My_List)
{
    int head_saver = My_List->list[LIST_PHANTOM_INDEX].next;

    LIST_ERR(list_erase(My_List, get_list_tail(*My_List)), ERASING_ERROR);

    My_List->list[LIST_PHANTOM_INDEX].next = head_saver;

    return LIST_IS_OK;
}


List_Errors erase_list_head(Node_Array* My_List)
{
    int tail_saver = My_List->list[LIST_PHANTOM_INDEX].prev;

    int list_index = get_list_head(*My_List);

    My_List->list[LIST_PHANTOM_INDEX].next = My_List->list[list_index].prev;

    LIST_ERR(list_erase(My_List, list_index), ERASING_ERROR);


    My_List->list[LIST_PHANTOM_INDEX].prev = tail_saver;


    return LIST_IS_OK;
}


List_Errors insert_list_head(Node_Array* My_List, const int elem)
{
    LIST_ERR(list_insert_after(My_List, get_list_head(*My_List), elem), INSERTION_ERROR);

    return LIST_IS_OK;
}


List_Errors insert_list_tail(Node_Array* My_List, const int elem)
{
    int insertion_index = My_List->list[get_list_tail(*My_List)].prev;

    LIST_ERR(list_insert_after(My_List, insertion_index, elem), INSERTION_ERROR);

    return LIST_IS_OK;
}


int get_list_head(const Node_Array My_List)
{
    fprintf(stderr, "list's head is here:%d\n", My_List.list[LIST_PHANTOM_INDEX].next);

    return My_List.list[LIST_PHANTOM_INDEX].next;
}


int get_list_tail(const Node_Array My_List)
{
    fprintf(stderr, "list's tail is here:%d\n", My_List.list[LIST_PHANTOM_INDEX].prev);

    return My_List.list[LIST_PHANTOM_INDEX].prev;
}


int get_next_elem_index(const Node_Array My_List, const int current_index)
{
    fprintf(stderr, "next elem's index for elem:%d is here:%d\n", current_index, My_List.list[current_index].next);

    return My_List.list[current_index].next;
}


int get_prev_elem_index(const Node_Array My_List, const int current_index)
{
    fprintf(stderr, "prev elem's index for elem:%d is here:%d\n", current_index, My_List.list[current_index].prev);

    return My_List.list[current_index].prev;
}


List_Errors erase_all(Node_Array* My_List) // FIXME ERROR HERE
{
    int list_index = get_list_head(*My_List);

    while(list_index != LIST_PHANTOM_INDEX)
    {
        int list_index_new = My_List->list[list_index].prev;

        LIST_ERR(erase_list_head(My_List), ERASING_ERROR);

        list_index = list_index_new;
    }

    return LIST_IS_OK;
}


// List_Errors get_elem_by_index()
// {

// }