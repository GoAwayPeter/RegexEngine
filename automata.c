#include <stdlib.h>
#include <stdio.h>
#include "automata.h"

static State* currNFAState;

/*
* State table is a linked list of arrays of linked
* lists.
* This removes the need for a 3D array, which 
* would be incredibly messy and horrible. Ew.
*/

State* allocNFAStates(int statesToAlloc)
{   int i,j;
    State *this, *prev, *start;
    for(i = 0;i < statesToAlloc;i++)
    {
        this = malloc(sizeof(State));    
        if(i == 0)
            start = this;
        this->prev = prev;
        if(prev != (State*)NULL)
            prev->next = this;
        prev = this;
    }
    return start;
}

State* initNFAStates(int numStates)
{   
    currNFAState = allocNFAStates(256);
    return currNFAState;
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
    //TODO
    return malloc(sizeof(State));
}

State* setNFAStateRelation(char symbol, State* from, State* to)
{
    if((int)symbol < 128 && (int)symbol >= 0 &&
        from != NULL)
    {
        if(from->symbols != NULL)
        {
            from->symbols = malloc(sizeof(SymList));
            from->symbols->val = symbol;
            from->symbols->sym = malloc(sizeof(Symbol));
            from->symbols->sym->change = to;
            from->symbols->sym->next = NULL;
            from->symbols->next = NULL;
        }
        else
        {
            //find if symbol is already in SymList
            int found = 0;
            SymList* lastList;
            SymList* t = from->symbols;
            while(t != NULL)
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
    return malloc(sizeof(State*));
}
