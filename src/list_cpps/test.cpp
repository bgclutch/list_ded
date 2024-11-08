#include <stdio.h>

#include "../../src/list_headers/dumps.h"
#include "../../src/list_headers/list.h"
#include "../../src/list_headers/test.h"

List_Errors test_func(Node_Array* My_List, My_Dump_St* General_Dump)
{
    LIST_ERR(insert_list_head(My_List, 12), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(insert_list_head(My_List, 1), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(insert_list_head(My_List, 112), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(insert_list_head(My_List, 121), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(list_insert_after(My_List, 2, 8921), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(erase_list_tail(My_List), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(erase_list_head(My_List), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    LIST_ERR(list_erase(My_List, 3), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    // LIST_ERR(erase_list_head(My_List), INSERTION_ERROR);
    // my_dump(*My_List, General_Dump);

    // LIST_ERR(erase_list_head(My_List), INSERTION_ERROR);
    // my_dump(*My_List, General_Dump);

    // LIST_ERR(erase_list_head(My_List), INSERTION_ERROR);
    // my_dump(*My_List, General_Dump);

    LIST_ERR(erase_all(My_List), INSERTION_ERROR);
    my_dump(*My_List, General_Dump);

    return LIST_IS_OK;
}