#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char c;
    fp = fopen(strcat(argv[0], ".c"), "r");
    if (fp)
    {
        while ((c = fgetc(fp)) != EOF)
            printf("%c", c);
        fclose(fp);
    }
    else
        printf("%s not found", argv[0]);
    return 0;
}