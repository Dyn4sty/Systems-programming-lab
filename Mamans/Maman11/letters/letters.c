/**
 * Program manipulate characters that it receives from the user
 *
 * 
 * @author Lior Kashanovsky
 */

#include <stdio.h>
#include <ctype.h>

#define DOT '.'
#define QUOTES '"'

/* The main function that reads infinite input */
int main()
{

    /* Flags to indicate whether the letter should be capitalize */
    int lineStart = 1, inQuotes = 0;

    /* Current char */
    int c;
    while ((c = getchar()) != EOF)
    {

        if ((lineStart || inQuotes) && !isspace(c))
        {
            if (isalpha(c))
                c = toupper(c);
            lineStart = 0;
        }
        else
            c = tolower(c);

        if (c == DOT && !inQuotes)
            lineStart = 1;
        if (c == QUOTES)
            inQuotes = inQuotes ? 0 : 1;
        if (!isdigit(c))
            putchar(c);
    }
    return 0;
}
