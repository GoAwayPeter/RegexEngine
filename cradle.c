#include "cradle.h"
#include <stdio.h>
#include <stdlib.h>

char *getChars(int argc, char **argv)
{
    if(argc > 1)
    {
        __cradle_regexData = (char *)malloc(REGEXDATASIZE * sizeof(char));

        int i = 0;
        while(i < REGEXDATASIZE)
        {
            __cradle_regexData[i] = argv[1][i];
            if(__cradle_regexData[i] == '\0')
                break;
            i++;
        }

//        file = argv[2];

        __cradle_look = __cradle_regexData;
        __cradle_lookBegin = __cradle_look;
    }
    else
        return NULL;
    return __cradle_regexData;
}

char getPrevChar()
{
    if(__cradle_look - 1 != NULL && __cradle_look - 1 >= __cradle_lookBegin)
        return *(__cradle_look - 1);
    return 0;
}

char getNextChar()
{
    if(*__cradle_look != '\0')
    {
        __cradle_look++;
        if(__cradle_look != NULL)
        {
            printf("%c",*__cradle_look);
            return *__cradle_look;
        }
    }
    return *__cradle_look = *__cradle_lookBegin;
}

char getCurrChar()
{
    if(__cradle_look != NULL)
        return *__cradle_look;
    return 0;
}

/* 
 * TODO Loadfiles 
 *
 *
 */
int isWildCard(char wildcard)
{
    return wildcard == 0x56 ? 1 : 0;
}

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
