#include <stdio.h>
#include <time.h>
#include "cradle.h"
#include "automata.h"

/*
 * Recursive descent parser to parse regex expressions,
 * uses syntax directed translation to translate
 * the regex to an NFA, and then hopefully I'll figure out
 * how to convert the NFA to a DFA
 *
 * Simple grammar for regex in BNF form, TODO expand
 * 
 *  <regex>     ::= <term> '|' <regex> | <term>
 *  <term>      ::= <factor><term> | <factor> '*' | <factor>
 *  <factor>    ::= '(' <regex> ')' | <chars>
 *  <chars>     ::= <chars><char> | '\'<chars><char> | <char>
 *  <char>      ::= 'a' | 'b' | 'c' | 'd' | ...
 **/

void chars();
void factor();
void term();
void regex();

void chars()
{
    while(isAlpha(getCurrChar()) || getCurrChar() == '\\' || isWildCard(getCurrChar()))
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
            if(setNFAStateRelation(getCurrChar(),getCurrState(),getNextState(1)) == -1)
               printf(" Error setting NFA state, currNFAState is %d \n",
                                                    (int)getCurrState());
            setCurrState(getNextState(2));
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
{   int i;
    clock_t begin, end;
    double timeTaken;
    initNFAStates(128);

    if(getChars(argc,argv) != NULL)
    {
        begin = clock();
        printf("%c",getCurrChar());
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


        printf("\n Regex parsed in %f ms\n",timeTaken);
    }
    else 
        printf("Not enough arguments given\n");

    printStates(10);
    return 0;
}
