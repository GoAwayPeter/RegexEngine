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
        this->rool = (Rule*)NULL;
    }
    this->next = (State*)NULL;
    return start;
}

State* initNFAStates(int numStates)
{   
    currNFAState = (State*)NULL;
    if(numStates < 0)
    {
        printf("Error initialising NFA states: incorrect numstates arg\n");
        exit(1);
    }
    currNFAState = allocNFAStates(numStates);
    statesAllocated = numStates;
    return currNFAState;
}

State* getCurrState()
{
    return currNFAState;
}

int setCurrState(State* s)
{
    if(s == (State*)NULL)
    {
        printf("Error setting current state, arg passed is null\n");
        exit(1);
    }
    currNFAState = s;
    return 0;
}

State* getNextState(int n)
{   int i;
    int hitEnd = 0;
    State* last;
    State* t = currNFAState;
    if(n > 0)
    {
        for(i = 0;i < n;i++)
        {
            if(t != (State*)NULL)
            {
                last = t;
                t = t->next;
            }
            else
            {
                t = allocNFAStates(2 * statesAllocated);
                last->next = t;
                t->prev = last;
            }
        }
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

//implement later, nobody likes cleaning up
void freeNFAStates()
{
    int i,j;
}


State* getNFAStateRelation(State* toGet, char symbol)
{
    //TODO
    return malloc(sizeof(State));
}

int setNFAStateRelation(char symbol, State* from, State* to)
{   
    if((( symbol < 127 && symbol >= 32) || symbol == EPSILON) 
            && from != NULL)
    {
        if(from->rool == (Rule*)NULL)
        {
            from->rool = malloc(sizeof(Rule));
//            from->rool->val = rool; //TODO
            from->rool->mov = malloc(sizeof(Move));
            from->rool->mov->change = to;
            from->rool->mov->next = (Move*)NULL;
            from->rool->next = (Rule*)NULL;
        }
        else
        {
            //find if symbol is already in Rule
            int found = 0;
            Rule* lastList;
            Rule* t = from->rool;
            while(t != (Rule*)NULL)
            {
                if(t->rule(symbol))
                {
                    found = 1;
                    break;
                }
                lastList = t;
                t = t->next;
            }
            if(found == 0)
            {
               t = malloc(sizeof(Rule)); 
               lastList->next = t;
//               t->val = rule; //TODO
               t->mov = malloc(sizeof(Move));
               t->mov->change = to;
               t->mov->next = (Move*)NULL;
               t->next = (Rule*)NULL;
            }

            Move* lastSym;
            Move* s = t->mov;
            while(s != (Move*)NULL)
            {
                lastSym = s;
                s = s->next;
            }
            s = malloc(sizeof(Move));
            lastSym->next = s; 
        }
        return 0;
    }
    printf("Setting NFA state failed. Invalid Character\n");
    return -1;
}
