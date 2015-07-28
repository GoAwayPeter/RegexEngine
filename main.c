#include <stdio.h>
#include <time.h>
#include "cradle.h"
#include "automata.h"

void chars();
void factor();
void term();
void regex();

/* 
 * Recursive descent parser to parse regex expressions,
 * uses syntax directed translation (I think) to translate
 * the regex to an NFA, and then hopefully I'll figure out
 * how to convert the NFA to a DFA and yayyy it'll all work wonderfully
 */
void chars()
{
    while(isAlpha(getCurrChar()) || getCurrChar() == '\\')
    {
        if(getCurrChar() == '\\')
        {
            getNextChar();
            //handle escaped char
            getNextChar();
            continue;
        }
        else if(!isRepOp(getCurrChar()))
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
            term();
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
        else
            getNextChar();

        if(getCurrChar() == '?') //makes rep ops ungreedy
            getNextChar();
        term();
        /*
         * Do something
         */
    }
}

void regex()
{
    term();
    if(getCurrChar() == '|') 
    {
        if(!getPrevChar())
            parseError(" \n Empty subexpression is not legal \n");
        getNextChar();
        regex();

        if(getPrevChar() == 0 || getPrevChar() == '|')
            parseError(" \n Empty subexpression is not legal \n");
    }
}

int main(int argc, char **argv)
{
    int i;
    clock_t begin, end;
    double timeTaken;

    if(getChars(argc,argv) != NULL)
    {
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
    }
    else 
        printf("Not enough arguments given\n");

    initStates();
//    printStateTable();

    return 0;
}
