#include <stdio.h>
#include <assert.h>

#include "../list_headers/list.h"
#include "../list_headers/dumps.h"
#include "../list_headers/test.h"
#include "../../lib_file_proc/file.h"

int main(void)
{
    Node_Array My_List = {};

    LIST_ERR(ctor_list(&My_List), LIST_CTOR_ERR);

    My_Dump_St General_Dump = {};

    my_dump(My_List, &General_Dump);

    LIST_ERR(test_func(&My_List, &General_Dump), TESTING_ERROR);

    close_file_html(General_Dump.HTML_DUMP);

    LIST_ERR(dtor_list(&My_List), LIST_DTOR_ERR);

    return 0;
}

