#include "lexer.h"
#define SIZE 4096

char buffer[SIZE];
int position = SIZE;
int end = 0;

FILE * getStream(FILE * fp)
{

    /* In the case that EOF has been reached and nothing is left to be read
    from the file, the buffer is not updated. So in this situation it contains
    the contents of the previous file read. */

    if (feof(fp))
        return NULL;

    int size = fread(buffer, 1, SIZE, fp);

    int i;

    for(i = size; i < SIZE; i++)
        buffer[i] = '\0';

    return fp;
}

char getNextChar(FILE * fp)
{
    if (position == SIZE)
    {
        fp = getStream(fp);

        if (fp)
        {
            position = 1;
            return buffer[0];
        }

        return '\0';
    }

    return buffer[position++];
}

void removeComments(FILE * fp, char * cleanFile)
{
    int i = 0;

    char c = getNextChar(fp);

    while(c != '\0')
    {
        if (c == '#')
        {
            c = getNextChar(fp);

            while(c != '\n' && c != '\0')
                c = getNextChar(fp);

            if (c == '\0')
                return;
        }

        cleanFile[i++] = c;

        c = getNextChar(fp);
    }
}

// int main()
// {
//     FILE * fp = fopen("testcases/testcase2.txt", "r");
//
//     char output[1024];
//
//     removeComments(fp, output);
//
//     printf("%s", output);
//
//     return 0;
// }
