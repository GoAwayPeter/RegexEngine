#include <stdio.h>
#include <time.h>
#include "cradle.h"

void chars();
void factor();
void term();
void regex();

void chars(int mustMatch)
{
    /* This must parse at least minMatch characters or matchable
     * sub expression, prints an error and exits if not
     */

    int charCount = 0;
    while(isAlpha(getCurrChar()) || getCurrChar() == '\\')
    {
        if(getCurrChar() == '\\')
        {
            getNextChar();
            //handle escaped char
            getNextChar();
            charCount++;
            continue;
        }
        else if(isAlpha(getCurrChar()))
        {
            //handle normal char
            getNextChar();
            charCount++;
        }
    }
    if(charCount < mustMatch)
        parseError("\n Invalid operator or expression expected");
}

void factor(int mustMatch)
{
    if(getCurrChar() == '(')
    {
        getNextChar();
        regex();
        if(getCurrChar() == ')')
        {
            getNextChar();
        }
        else
            parseError("\n Unbalanced parantheses");
    }
    chars(mustMatch); //eats all characters
}

void term()
{
    factor(1);
    if(getCurrChar() == '*')
    {
        if(isRepOp(getNextChar()))
            parseError("\n Invalid repetition operator");
        if(getCurrChar() == '?') //makes rep ops ungreedy
            getNextChar();
        /*
         * Do something
         */
    }
    factor(0);
}

void regex()
{
    term();
    if(getCurrChar() == '|')
    {
        getNextChar();
        regex();
    }
}


int main(int argc, char **argv)
{
    int i;
    clock_t begin, end;
    double timeTaken;

    if(getChars(argc,argv) == NULL)
        printf("Not enough arguments given\n");
    begin = clock();
    regex();

    if(getCurrChar() == '\0')
        printf("\nSuccesfully parsed!");
    else
    {
        printf("\nError, chars remaining: %c",getCurrChar());
        while(getCurrChar() != '\0')
        {
            getNextChar();
        }
    }
    end = clock();
    timeTaken = (double)(end - begin)/CLOCKS_PER_SEC * 1000;

    printf("\n Regex parsed in %f ms",timeTaken);
    printf("\n");

    return 0;
}
