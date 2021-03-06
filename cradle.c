#include "cradle.h"
#include <stdio.h>
#include <stdlib.h>

char *getChars(int argc, char **argv)
{
    if(argc > 1)
    {
        regexData = (char *)malloc(100 * sizeof(char));

        int i = 0;
        while(i < 99)
        {
            regexData[i] = argv[1][i];
            if(regexData[i] == '\0')
                break;
            i++;
        }

//        file = argv[2];

        look = regexData;
        lookBegin = look;
    }
    else
        return NULL;
    return regexData;
}
char getPrevChar()
{
    if(look - 1 != NULL && look - 1 >= lookBegin)
        return *(look - 1);
    return 0;
}

char getNextChar()
{
    if(*look != '\0')
    {
        look++;
        if(look != NULL)
        {
            printf("%c",*look);
            return *look;
        }
    }
    return 0;
}

char getCurrChar()
{
    if(look != NULL)
        return *look;
    return 0;
}

/* 
 * TODO Loadfiles 
 *
 *
 */

int isAlpha(char alpha)
{
    if((alpha > 0x40 && alpha < 0x5B) ||
       (alpha > 0x60 && alpha < 0x7B))
        return 1;
    return 0;
}

int isDigit(char digit)
{
    if(digit > 0x2F && digit < 0x3A)
        return 1;
    return 0;
}

int isUpperCase(char alpha)
{
    return 1;
}

int isLowerCase(char alpha)
{
    return 1;
}

int isRepOp(char op)
{
    switch(op)
    {
        case '*':
            return 1;
        case '+':
            return 1;
    }
    return 0;
}

void parseError(char *s)
{
    printf("Parse Error: %s\n",s);
    printf(" Curr char is %c %d \n", getCurrChar(),getCurrChar());
    printf(" Prev char is %c %d \n", getPrevChar(),getPrevChar());
    printf(" Next char is %c %d \n", getNextChar(),getCurrChar());

    exit(1);
}

void memoryError(char *s)
{
    printf("Memory Error: %s\n",s);

    exit(1);
}
