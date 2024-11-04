#include <stdio.h>

#include "list_headers/list.h"
#include "lib_file_proc/file.h"

int main()
{
    List* list = {};

    FILE* dump_file = nullptr;
    FILE_ERR(file_read_open(&dump_file, DUMP_FILE_NAME), FILE_W_OPEN_ERR);

    LIST_ERR(ctor_list(list), LIST_CTOR_ERR);


    for(size_t index_list = LIST_START_INDEX; index_list < LIST_SIZE; index_list++)
    {
        list[index_list].data = index_list * 10;
        list[index_list].elem_index = index_list;
        list[index_list].prev = list[index_list - 1].elem_index;
        list[index_list].next = LIST_PHANTOM_INDEX;
    }


    LIST_ERR(dtor_list(list), LIST_DTOR_ERR);

    return 0;
}