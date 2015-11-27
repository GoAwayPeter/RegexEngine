#include <stdio.h>
#include <time.h>
#include "cradle.h"
#include "automata.h"

void chars();
void factor();
void term();
void regex();

static State* currNFAState;
/* 
 * Recursive descent parser to parse regex expressions,
 * uses syntax directed translation to translate
 * the regex to an NFA, and then hopefully I'll figure out
 * how to convert the NFA to a DFA
 * */
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
            if(setNFAStateRelation(getCurrChar(),currNFAState,nextState(currNFAState)) == -1)
                printf(" Error setting NFA state, currNFAState is %ld \n",currNFAState);

            currNFAState = nextState(nextState(currNFAState));
            getNextChar();
        }
        else
            parseError("\n Expected char");
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
        /* This check quite possibly needs removing
         */
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
    currNFAState = 0;
    initNFAStates();

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

        printNFAStateTable();

        printf("\n Regex parsed in %f ms\n",timeTaken);
    }
    else 
        printf("Not enough arguments given\n");

    return 0;
}
