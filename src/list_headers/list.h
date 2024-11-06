#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>


#define LIST_ERR(result, error) if(list_is_error(result, __FILE__, __LINE__) == MACRO_ERR) return error


typedef int ListElem_t;

static const int LIST_FREE_ATTR = -1;

static const int LIST_PHANTOM_INDEX = 0;

static const int LIST_START_INDEX = 1;

static const int LIST_SIZE = 10;

static const ListElem_t LIST_POISON = 0x5051;


struct List
{
    ListElem_t data;
    int next;
    int prev;
};

struct Node_Array
{
    List* list;
    int free;
};

enum List_Errors
{
    LIST_IS_OK         = 0x00,
    LIST_CTOR_ERR      = 0x01,
    LIST_DTOR_ERR      = 0x02,
    MACRO_ERR          = 0x03,
    MACRO_GOOD         = 0x04,
    FIND_LAST_FREE_ERR = 0x05,
    INSERTION_ERROR    = 0x06,
    ERASING_ERROR      = 0x07,
};


List_Errors ctor_list(Node_Array*);

List_Errors dtor_list(Node_Array*);

List_Errors list_is_error(const List_Errors result, const char* name, const size_t line);

void default_list_fill(Node_Array*);

List_Errors list_insert_after(Node_Array*, const int pre_insert_index, const ListElem_t elem);

List_Errors list_erase(Node_Array*, const int erase_index);

List_Errors find_last_free(Node_Array* My_List, const int new_last_free);

int get_list_head(const Node_Array My_List);

int get_list_tail(const Node_Array My_List);

int get_next_elem_index(const Node_Array My_List, const int current_index);

int get_prev_elem_index(const Node_Array My_List, const int current_index);

List_Errors insert_list_head(Node_Array* My_List, const int elem);

List_Errors insert_list_tail(Node_Array* My_List, const int elem);

List_Errors erase_list_head(Node_Array* My_List);

List_Errors erase_list_tail(Node_Array* My_List);

List_Errors erase_all(Node_Array* My_List);

#endif // LIST_H_