#ifndef DUMPS_H_
#define DUMPS_H_

#include "list.h"


#define DUMP_ERR(result, error) if(dump_is_error(result, __FILE__, __LINE__) != DUMP_IS_OKAY) return error

static const size_t DEFAULT_DUMP_ARR_SIZE = 10;
static const size_t DUMP_ARR_REALLOC_COEF = 2;


static const char* const GRAPH  = "graph_dump";
static const char* const DOT    = "dot";
static const char* const DOTXT  = ".dot";
static const char* const HTMLXT = ".html";
static const char* const PNGXT  = ".png";
static const char* const PATH   = "dumps/html/";
static const char* const TPNG   = "-Tpng";
static const char* const OBJXT  = "-o";
static const char* const SPACE  = " ";


enum Dump_Errors
{
    DUMP_IS_OKAY             = 0x00,
    GRAPHIC_DUMP_ERR         = 0x01,
    TEXT_DUMP_ERR            = 0x02,
    TXT_DUMP_OPEN_ERR        = 0x03,
    TXT_DUMP_CLOSE_ERR       = 0x04,
    GRAPH_DUMP_OPEN_ERR      = 0x05,
    GRAPH_DUMP_CLOSE_ERR     = 0x06,
    DUMP_ST_INIT_ERROR       = 0x07,
    MACRO_DUMP_IS_GOOD       = 0x10,
    MACRO_DUMP_IS_ERR        = 0x20,
};


struct My_Dump_St
{
    const char* const TXT_DUMP   = "dumps/txt_dump.txt";
    const char* const GRAPH_DUMP = "dumps/graph_dump.dot";
    const char* const HTML_DUMP  = "dumps/html/html_dump.html";
    int filenum = 0;
};


Dump_Errors text_dump(List *list, const char* const text_dump);

Dump_Errors graph_dump(const Node_Array My_List, const char* const graph_dump);

Dump_Errors my_dump(const Node_Array My_List, My_Dump_St* General_Dump);

Dump_Errors dump_st_init(My_Dump_St*);

Dump_Errors dump_is_error(const Dump_Errors result, const char* name, const size_t line);

Dump_Errors dumps_cleaning(const My_Dump_St General_Dump);

void dot_to_png(const char* name, My_Dump_St* General_Dump);

void make_html_file(const char* filename);

void fill_file_html(const char* filename, const char* pngname);

void close_file_html(const char* filename);


#endif // DUMPS_H_