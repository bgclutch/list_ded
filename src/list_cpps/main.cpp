#include <stdio.h>
#include <assert.h>

#include "../list_headers/list.h"
#include "../../lib_file_proc/file.h"

int main(void)
{
    Node_Array My_List = {};

    LIST_ERR(ctor_list(&My_List), LIST_CTOR_ERR);

    FILE* dump_file = nullptr;
    FILE_ERR(file_write_open(&dump_file, DUMP_FILE_NAME), FILE_W_OPEN_ERR);

    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 0, 12), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 1, 1), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 2, 121), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 3, 8989), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 1, 5051), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 4, 5), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);

    LIST_ERR(list_insert_after(&My_List, 2, 909090), INSERTION_ERROR);
    list_dump(My_List.list, dump_file);


    // LIST_ERR(list_erase(&My_List, 2), ERASING_ERROR);
    // list_dump(My_List.list, dump_file);


    LIST_ERR(dtor_list(&My_List), LIST_DTOR_ERR);

    FILE_ERR(file_close(dump_file), FILE_CLOSE_ERR);

    return 0;
}