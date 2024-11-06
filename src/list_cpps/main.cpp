#include <stdio.h>
#include <assert.h>

#include "../list_headers/list.h"
#include "../list_headers/dumps.h"
#include "../../lib_file_proc/file.h"

int main(void)
{
    Node_Array My_List = {};

    LIST_ERR(ctor_list(&My_List), LIST_CTOR_ERR);

    My_Dump_St General_Dump = {};

    my_dump(My_List, &General_Dump);

    LIST_ERR(insert_list_head(&My_List, 12), INSERTION_ERROR);
    my_dump(My_List, &General_Dump);

    LIST_ERR(insert_list_head(&My_List, 1), INSERTION_ERROR);
    my_dump(My_List, &General_Dump);

    LIST_ERR(insert_list_head(&My_List, 112), INSERTION_ERROR);
    my_dump(My_List, &General_Dump);

    LIST_ERR(insert_list_head(&My_List, 121), INSERTION_ERROR);
    my_dump(My_List, &General_Dump);

    // LIST_ERR(list_insert_after(&My_List, 0, 12), INSERTION_ERROR);
    // my_dump(My_List, &General_Dump);

    // LIST_ERR(list_insert_after(&My_List, 1, 1), INSERTION_ERROR);
    // my_dump(My_List, &General_Dump);

    // LIST_ERR(list_insert_after(&My_List, 2, 121), INSERTION_ERROR);
    // my_dump(My_List, &General_Dump);

    // LIST_ERR(erase_all(&My_List), ERASING_ERROR);
    // my_dump(My_List, &General_Dump);

    // LIST_ERR(list_insert_after(&My_List, 2, 90), INSERTION_ERROR);
    // my_dump(My_List, &General_Dump);

    close_file_html(General_Dump.HTML_DUMP);

    LIST_ERR(dtor_list(&My_List), LIST_DTOR_ERR);

    return 0;
}

