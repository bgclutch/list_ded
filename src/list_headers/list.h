#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>


#define LIST_ERR(result, error) if(list_is_error(result, __FILE__, __LINE__) == MACRO_ERR) return error

const char const* DUMP_FILE_NAME = "dumps/list_dump.txt";

typedef int ListElem_t;

static const size_t LIST_SIZE = 10;

static const size_t LIST_START_INDEX = 1;

static const size_t LIST_PHANTOM_INDEX = 0;

static const ListElem_t LIST_POISON = 0x5051;


struct List
{
    ListElem_t data;
    int next;
    int prev;
    int elem_index;
};

enum List_Errors
{
    LIST_IS_OK    = 0x00,
    LIST_CTOR_ERR = 0x01,
    LIST_DTOR_ERR = 0x02,
    MACRO_ERR     = 0x03,
    MACRO_GOOD    = 0x04,
};


List_Errors ctor_list(List*);

List_Errors dtor_list(List*);

List_Errors list_is_error(const List_Errors result, const char* name, const size_t line);

void list_dump(List *list, FILE* dump_file);

#endif // LIST_H_