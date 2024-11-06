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

    graph_dump(My_List, General_Dump.GRAPH_DUMP);

    // fprintf(stderr, "enter 'c'\n");
    // int input = 0;
    // while((input = getchar()) != 'c')
    // {
    //     fprintf(stderr, "enter 'c'\n");
    // }

    LIST_ERR(list_insert_after(&My_List, 0, 12), INSERTION_ERROR);
    // text_dump(My_List.list, General_Dump.TXT_DUMP);
    // graph_dump(My_List, General_Dump.GRAPH_DUMP);
    my_dump(My_List, General_Dump);

    LIST_ERR(list_insert_after(&My_List, 1, 1), INSERTION_ERROR);
    // text_dump(My_List.list, General_Dump.TXT_DUMP);
    // graph_dump(My_List, General_Dump.GRAPH_DUMP);

    LIST_ERR(list_insert_after(&My_List, 2, 121), INSERTION_ERROR);
    // text_dump(My_List.list, General_Dump.TXT_DUMP);
    // graph_dump(My_List, General_Dump.GRAPH_DUMP);
    my_dump(My_List, General_Dump);

    LIST_ERR(list_insert_after(&My_List, 1, 72), INSERTION_ERROR);
    // text_dump(My_List.list, General_Dump.TXT_DUMP);
    // graph_dump(My_List, General_Dump.GRAPH_DUMP);
    my_dump(My_List, General_Dump);

    LIST_ERR(list_insert_after(&My_List, 2, 90), INSERTION_ERROR);
    // text_dump(My_List.list, General_Dump.TXT_DUMP);
    // graph_dump(My_List, General_Dump.GRAPH_DUMP);
    my_dump(My_List, General_Dump);

    close_file_html(General_Dump.HTML_DUMP);

    LIST_ERR(dtor_list(&My_List), LIST_DTOR_ERR);

    return 0;
}