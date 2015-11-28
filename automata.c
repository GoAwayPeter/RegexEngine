#include <stdlib.h>
#include <stdio.h>
#include "automata.h"
//TODO Optimise later

static State* currNFAState;
static unsigned int statesAllocated;


/*
* State table is a linked list of arrays of linked
* lists.
* This removes the need for a 3D array, which 
* would be incredibly messy and horrible. Ew.
*/

State* allocNFAStates(int statesToAlloc)
{   int i,j;
    State *this, *prev, *start;
    prev = (State*)NULL;
    for(i = 0;i < statesToAlloc;i++)
    {
        this = malloc(sizeof(State));    
        if(i == 0)
            start = this;
        this->prev = prev;
        if(prev != (State*)NULL)
            prev->next = this;
        prev = this;
        this->symbol = (SymList*)NULL;
    }
    this->next = (State*)NULL;
    return start;
}

State* initNFAStates(int numStates)
{   
    currNFAState = (State*)NULL;
    if(numStates > 0)
    {
        currNFAState = allocNFAStates(numStates);
        statesAllocated = numStates;
    }
    return currNFAState;
}

State* getCurrState()
{
    return currNFAState;
}

State* setCurrState(State* s)
{
    if(s != (State*)NULL)
        currNFAState = s;
    return currNFAState;
}

State* getNextState(int n)
{   int i;
    int hitEnd = 0;
    State* last;
    State* t = currNFAState;
    for(i = 0;i < n;i++)
    {
        if(t != (State*)NULL)
            t = t->next;
        else
            hitEnd = 1;
    }
    if(hitEnd == 1)
    {
        t = allocNFAStates(2 * statesAllocated);
        last->next = t;
        t->prev = last;
    }
    return t;
}

State* getPrevState(int n)
{   int i;
    int hitEnd = 0;
    State* t = currNFAState;
    for(i = 0;i < n;i++)
    {
        if(t != NULL)
            t = t->prev;
        else
            hitEnd = 1;
    }
    if(hitEnd == 1)
        printf("Warning; hit beginning of states, returning null pointer");
    return t;
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
    //TODO
    return malloc(sizeof(State));
}

State* setNFAStateRelation(char symbol, State* from, State* to)
{
    if((int)symbol < 128 && (int)symbol >= 0 &&
        from != NULL)
    {
        if(from->symbol == (SymList*)NULL)
        {
            from->symbol = malloc(sizeof(SymList));
            from->symbol->val = symbol;
            from->symbol->sym = malloc(sizeof(Symbol));
            from->symbol->sym->change = to;
            from->symbol->sym->next = (Symbol*)NULL;
            from->symbol->next = (SymList*)NULL;
        }
        else
        {
            //find if symbol is already in SymList
            int found = 0;
            SymList* lastList;
            SymList* t = from->symbol;
            while(t != (SymList*)NULL)
            {
                if(t->val == symbol)
                {
                    found = 1;
                    break;
                }
                lastList = t;
                t = t->next;
            }
            if(found == 0)
            {
               t = malloc(sizeof(SymList)); 
               lastList->next = t;
               t->val = symbol;
               t->sym = malloc(sizeof(Symbol));
               t->sym->change = to;
            }

            Symbol* lastSym;
            Symbol* s = t->sym;
            while(s != NULL)
            {
                lastSym = s;
                s = s->next;
            }
            s = malloc(sizeof(Symbol));
            lastSym->next = s;
        }
    }
    return malloc(sizeof(State));
}
