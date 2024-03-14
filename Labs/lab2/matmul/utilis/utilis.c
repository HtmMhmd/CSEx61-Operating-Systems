#include "utilis.h"

void open_txt_File(char *filename, FILE **file, open_file_t open_type)
{
    /*
    open txt file using filename
    @params
    filename    : sring which the formated matrix presents
    file        : double pointer to a FILE type          ( to use dynamic memory allocation)
    open_file_t : enum type to specify the open file type read or write
    */
    if      (READ_TXT == open_type)
    {
        *file = fopen(filename, "r");
    }
    else if (WRITE_TXT == open_type)
    {
        *file = fopen(filename, "w");
    }
    else
    {
        printf("WRONG OPEN FILE TYPE");
        exit(1);
    }
    if (*file == NULL) 
    {

        printf("CANNOT OPEN FILE %s\n", filename);
        exit(1);
    }
}