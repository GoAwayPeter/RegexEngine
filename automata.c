#include <stdlib.h>
#include <stdio.h>
#include "automata.h"

/*
* State table is a linked list of arrays of linked
* lists.
* This removes the need for a 3D array, which 
* would be incredibly messy and horrible. Ew.
*/

State* initNFAStates(int numStates)
{

    int i,j;
    numStates = 256;
    State *this, *prev, *start;
    for(i = 0;i < numStates;i++)
    {
        this = malloc(sizeof(State));    
        if(i == 0)
            start = this;
        this->prev = prev;
        if(prev != (State*)NULL)
            prev->next = this;
        this->symbolArray = malloc(NUMSYMBOLS * sizeof(Symbol));
        prev = this;
    }
    return start;
}

State* addNFAStates(State toAdd)
{
    State a;
    return &a;
}

State* nextState(State* s)
{
    if(s != NULL)
        return s->next;
    printf("Error, null pointer given during state change\n");
    return (State*)-1;
}

State* prevState(State* s)
{
    if(s != NULL)
        return s->prev;
    printf("Error, null pointer given during state change\n");
    return (State*)-1;
}

void freeNFAStates()
{
    int i,j;
}

void printNFAStateTable()
{
}

State* getNFAStateRelation(State* toGet, char symbol)
{
    State a;
    return &a;
}

State* setNFAStateRelation(char symbol, State* from, State* to)
{
    State a;
    return &a;
}
