#include "utilis.h"

/**
 * Opens the txt file.
 *
 * @param filename   : string (path) of the txt file.
 * @param open_type  : enum indicating the type of file operation.
 * @return file      : pointer to the opened file.
 */
FILE *open_txt_File(char *filename, open_file_t open_type)
{
    FILE *file;
    if (open_type == READ_TXT)
    {
        file = fopen(filename, "r");
    }
    else if (open_type == WRITE_TXT)
    {
        file = fopen(filename, "w");
    }
    return file;
}