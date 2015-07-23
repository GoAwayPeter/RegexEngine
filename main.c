#include <stdio.h>
#include <time.h>
#include "cradle.h"

void chars();
void factor();
void term();
void regex();

void chars()
{
    /* This must parse at least minMatch characters or matchable
     * sub expression, prints an error and exits if not
     */

    while(isAlpha(getCurrChar()) || getCurrChar() == '\\')
    {
        if(getCurrChar() == '\\')
        {
            getNextChar();
            //handle escaped char
            getNextChar();
            continue;
        }
        else if(isAlpha(getCurrChar()) || isDigit(getCurrChar()))
        {
            //handle normal char
            getNextChar();
        }
    }
}

void factor()
{
    chars(); //eats all characters
    if(getCurrChar() == '(')
    {
        getNextChar();
        regex();
        if(getCurrChar() == ')')
        {
            getNextChar();
            getNextChar();
        }
        else
            parseError("\n Unbalanced parantheses");
    }
}

void term()
{
    factor();
    if(getCurrChar() == '*')
    {
        if(!isAlpha(getPrevChar()) && !isDigit(getPrevChar()) &&
           (getPrevChar() != ')'))
            parseError("\n Expression must precede repetition operator ");

        if(getCurrChar() == '?') //makes rep ops ungreedy
            getNextChar();
        /*
         * Do something
         */
    }
    factor();
}

void regex()
{
    term();
    if(getCurrChar() == '|') //TODO check sub expression is not empty
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
