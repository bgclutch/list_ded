#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>


#include "../list_headers/dumps.h"
#include "../list_headers/list.h"




Dump_Errors text_dump(List *list, const char* const text_dump)
{
    assert(list);
    assert(text_dump);

    FILE* text_dump_file = fopen(text_dump, "w");

    if(text_dump == nullptr)
        return TXT_DUMP_OPEN_ERR;


    fprintf(text_dump_file, "\n\nvalue\tindex\t prev\t next\n\n");

    for(int index_list = LIST_PHANTOM_INDEX; index_list < LIST_SIZE; index_list++)
    {
        List* place = list + index_list;

        fprintf(text_dump_file, "%5d\t%5d\t%5d\t%5d\t\n", place->data, index_list, place->prev, place->next);
    }

    if(fclose(text_dump_file))
        return TXT_DUMP_CLOSE_ERR;


    return DUMP_IS_OKAY;
}



Dump_Errors graph_dump_preparing(const char* const graph_dump)
{
    FILE* graph_dump_file = fopen(graph_dump, "w");

    if(graph_dump_file == nullptr)
        return GRAPH_DUMP_OPEN_ERR;


    fprintf(graph_dump_file,
            "digraph LIST{\n"
            "harset=\"UTF-8\";\n"
            "label = \"MY LIST)\";\n"
            "rankdir=TB;\n"
            "node=[fontsize = 9];\n"
            "bgcolor=\"#0000aa\";\n"
            "fontcolor=black;\n"
            "fontsize=18;\n"
            "style=\"italic\";\n"
            "margin=0.3;\n"
            "splines=ortho;\n"
            "ranksep=1.0;\n"
            "nodesep=0.9;\n"
            "bgcolor=\"#ff9c8c\";\n"
            "edge[color=\"#e8e6a5\"]\n;");

    return DUMP_IS_OKAY;
}



Dump_Errors dumps_cleaning(const My_Dump_St General_Dump)
{
    fprintf(stderr, "penis dumps cleaning\n");

    FILE* first  = fopen(General_Dump.TXT_DUMP, "w");
    FILE* second = fopen(General_Dump.GRAPH_DUMP, "w");

    if(fclose(first) || fclose(second))
        return TXT_DUMP_CLOSE_ERR;

    return DUMP_IS_OKAY;
}



Dump_Errors graph_dump(const Node_Array My_List, const char* const graph_dump)
{
    FILE* graph_dump_file = fopen(graph_dump, "w");

    if(graph_dump_file == nullptr)
    {
        fprintf(stderr, "graph dump file open err\n");
        return GRAPH_DUMP_OPEN_ERR;
    }

    fprintf(graph_dump_file,
            "digraph LIST{\n"
            "harset = \"UTF-8\";\n"
            "rankdir = TB;\n"
            "bgcolor = \"#0000aa\";\n"
            "fontcolor = black;\n"
            "fontsize = 18;\n"
            "style = \"italic\";\n"
            "margin = 0.3;\n"
            "splines = ortho;\n"
            "ranksep = 0.5;\n"
            "nodesep = 0.9;\n"
            "bgcolor = \"#ff9c8c\";\n");



    for(int dump_index = 0; dump_index < LIST_SIZE; dump_index++)
    {
        fprintf(graph_dump_file,
                "node%d [shape = record, style = rounded, label = \"{phys index: %d | <f1> data: %d | "
                "<f2> next: %d | <f3> prev %d}\"];\n",
                dump_index, dump_index, My_List.list[dump_index].data,
                My_List.list[dump_index].next, My_List.list[dump_index].prev);
    }


    fprintf(graph_dump_file, "\n");

    for(int dump_index = 0; dump_index < LIST_SIZE - 1; dump_index++)
    {
        fprintf(graph_dump_file,
                "node%d:f3 -> node%d:f3[weight = 1000; color = \"#ff9c8c\"; headport = n];\n",
                dump_index, dump_index + 1);

    }

    fprintf(graph_dump_file, "\n");


    for(int dump_index = 0; dump_index < LIST_SIZE; dump_index++)
    {
        fprintf(graph_dump_file,
                "node%d:s:f1 -> node%d:s:f1[constraint=false, color = \"#176617\"];\n",
                dump_index, My_List.list[dump_index].next);
    }


    for(int dump_index = 0; dump_index < LIST_SIZE; dump_index++)
    {
        if(My_List.list[dump_index].prev != LIST_FREE_ATTR && My_List.list[dump_index].prev != dump_index)
        {
            fprintf(graph_dump_file,
                    "node%d:n:f1 -> node%d:n:f1[constraint=false, color = \"blue\"];\n",
                    dump_index, My_List.list[dump_index].prev);
        }
    }

    fprintf(graph_dump_file, "\n");

    fprintf(graph_dump_file, "FREE [fontcolor = \"red\", fontsize = 20, fontstyle = \"bold\", shape = record, label = \"free -> nodes%d\", style = rounded];", My_List.free);
    fprintf(graph_dump_file, "FREE -> node%d [color = \"red\", headport=n];\n", My_List.free);

    fprintf(graph_dump_file, "\n");


    fprintf(graph_dump_file,
            "{rank = same; node0; node1; node2; node3; node4; node5; node6; node7; node8; node9;}\n"
    );


    fprintf(graph_dump_file, "}");


    if(fclose(graph_dump_file))
        return GRAPH_DUMP_CLOSE_ERR;

    return DUMP_IS_OKAY;
}


Dump_Errors my_dump(const Node_Array My_List, const My_Dump_St General_Dump)
{
    assert(General_Dump.GRAPH_DUMP);
    assert(General_Dump.TXT_DUMP);

    graph_dump(My_List, General_Dump.GRAPH_DUMP);

    text_dump(My_List.list, General_Dump.TXT_DUMP);

    make_html_file(General_Dump.HTML_DUMP);

    dot_to_png(General_Dump.GRAPH_DUMP);


    return DUMP_IS_OKAY;
}


Dump_Errors dump_is_error(const Dump_Errors result, const char* name, const size_t line)
{
    assert(name);

    if(result != DUMP_IS_OKAY)
    {
        fprintf(stderr, "Error here: %s:%lu\n\n", name, line);
        return MACRO_DUMP_IS_ERR;
    }

    return MACRO_DUMP_IS_GOOD;
}


void dot_to_png(const char* name, const char* dump_filename)
{
    assert(name);

    char filename[300] = {};

    char pngname[200] = {};

    long dump_time = rand();

    strcat(pngname, PATH);
    strcat(pngname, GRAPH);

    int offset = sizeof(PATH) + sizeof(GRAPH);

    snprintf(pngname + offset, sizeof(dump_time), "%ld", dump_time);

    strcat(pngname, PNGXT);

    strcat(filename, DOT);
    strcat(filename, SPACE);
    strcat(filename, name);
    strcat(filename, SPACE);
    strcat(filename, TPNG);
    strcat(filename, SPACE);
    strcat(filename, OBJXT);
    strcat(filename, SPACE);
    strcat(filename, pngname);

    system(filename);

    fill_file_html();
}

void make_html_file(const char* filename)
{
    FILE* dump_file = fopen(filename, "w");

    fprintf(dump_file,
            "<!DOCTYPE html>\n"
            "<html lang="en">\n\n"
            "<head>\n"
            "\t<meta charset="utf-8">\n"
            "\t<meta name="viewport" content="width=device-width, initial-scale=1">\n"
            "\t<title>list dump</title>\n"
            "\t<link rel="stylesheet" href="styles.css">\n"
            "</head>\n\n"
            "<body>\n");

    fclose(dump_file);
}


void fill_file_html(const char* filename, const char* pngname)
{
    FILE* dump_file = fopen(filename, "w");
    fprintf(dump_file,
            "%s\n",
            pngname);

    fclose(dump_file);
}


void close_file_html(const char* filename)
{
    FILE* dump_file = fopen(filename, "w");
    fprintf(dump_file,
            "<body>\n\n"
            "</html>\n", );

    fclose(dump_file);
}

