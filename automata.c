#include <stdlib.h>
#include <stdio.h>
#include "automata.h"
/*
 * TODO
 * - optimisations (not really)
 * - nfa to dfa conversion (important!)
 */

/*
 * ## Internal function
 * Allocates memory for nfa states - this is called in
 * the initialisation of the states, and if we request
 * the 'next' state, but it doesn't exist yet
 */
State* allocStates(int statesToAlloc)
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

/*
 * Initialise the automata library
 */
State* initNFAStates(int numStates)
{
    __automata_currNFAState = (State*)NULL;
    if(numStates < 0)
    {
        printf("Error initialising NFA states: incorrect numstates arg\n");
        exit(1);
    }
    __automata_currNFAState = allocStates(numStates);
    __automata_statesAllocated = numStates;
    return __automata_currNFAState;
}

/*
 * Returns a pointer to the current State
 */
State* getCurrNFAState()
{
    return __automata_currNFAState;
}

/*
 * Change the current state
 */
int setCurrNFAState(State* s)
{
    if(s == (State*)NULL)
    {
        printf("Error setting current state, arg passed is null\n");
        exit(1);
    }
    __automata_currNFAState = s;
    return 0;
}

/*
 * Gets the next State from the current State
 */
State* getNextNFAState(int n)
{   int i;
    int hitEnd = 0;
    State* last;
    State* next = __automata_currNFAState;
    if(n > 0)
    {
        for(i = 0;i < n;i++)
        {
            if(next != (State*)NULL)
            {
                last = next;
                next = next->next;
            }
            else
            {
                next = allocStates(2 * __automata_statesAllocated);
                last->next = next;
                next->prev = last;
            }
        }
    }
    return next;
}

/*
 * Get the previous state from the current State
 */
State* getPrevNFAState(int n)
{   int i;
    int hitEnd = 0;
    State* t = __automata_currNFAState;
    for(i = 0;i < n;i++)
    {
        if(t != NULL)
            t = t->prev;
        else
        {
            hitEnd = 1;
            break;
        }
    }
    if(hitEnd == 1 && DEBUG)
        printf("Warning; hit beginning of states, returning null pointer");
    return t;
}

/* 
 * TODO implement later, nobody likes cleaning up
 */
void freeNFAStates()
{
    int i,j;
}

/* 
 * Returns array of pointers to states reachable by symbol 
 * from the current State
 */
List* getNFAStates(char symbol)
{
    List* startList = NULL, *currList = NULL, *lastList = NULL;
    Rule* rule = NULL;
    Move* move = NULL;
    int count = 0;

    if(__automata_currNFAState->rool != NULL)
    {
        rule = __automata_currNFAState->rool;
        while(rule != (Rule*)NULL) 
        {
            if(rule->symbol == symbol)
            {
                move = rule->mov;
                while(move != (Move*)NULL)
                {
                    if(startList == (List*)NULL)
                    {
                        startList = malloc(sizeof(List));
                        currList = startList;
                        lastList = startList;
                        startList->next = (List*)NULL;
                        startList->prev = (List*)NULL;
                    }
                    if(currList == (List*)NULL)
                    {
                        currList = malloc(sizeof(List));
                        currList->prev = lastList;
                        currList->next = (List*)NULL;
                        lastList->next = currList;
                        if(DEBUG)
                            printf("getNFAStates(): adding state to list\n"); 
                    }
                    currList->state = move->to;
                    lastList = currList;
                    currList = currList->next;
                    move = move->next;
                    ++count;
                }
            }
            rule = rule->next;
        }
        if(DEBUG)
            printf("Found %d states for symbol %c\n",count, symbol);
    }
    return startList;
}

/*
 * Sets a relation between 2 states
 */
int setNFAStateRelation(char symbol, State* from, State* to)
{
    if((( symbol < 127 && symbol >= 32) || symbol == EPSILON || symbol == '.')
            && from != NULL)
    {
        if(from->rool == (Rule*)NULL) //rule doesn't exist yet
        {
            from->rool = malloc(sizeof(Rule));
            from->rool->symbol = symbol;
            from->rool->mov = malloc(sizeof(Move));
            from->rool->mov->to = to;
            from->rool->mov->next = (Move*)NULL;
            from->rool->next = (Rule*)NULL;
        }
        else //rule exists but we don't know if our symbol is in Rule list
        {
            //find if symbol is already in Rule list
            int found = 0;
            Rule* lastRule;
            Rule* t = from->rool;
            while(t != (Rule*)NULL)
            {
                if(t->symbol == symbol)
                {
                    found = 1;
                    break;
                }
                lastRule = t;
                t = t->next;
            }
            if(found == 0) //symbol is not in Rule list, add it
            {
                t = malloc(sizeof(Rule)); 
                lastRule->next = t;
                t->symbol = symbol;
                t->mov = malloc(sizeof(Move));
                t->mov->to = to;
                t->mov->next = (Move*)NULL;
                t->next = (Rule*)NULL;
            }
            else //symbol is in Rule list, add new move.
            {
                Move* lastMov;
                Move* s = t->mov;
                while(s != (Move*)NULL)
                {
                    if(s->to == to)
                    {
                        if(DEBUG)
                            printf("Move already exists\n");
                        return 0; //move already exists
                    }
                    lastMov = s;
                    s = s->next;
                }
                s = malloc(sizeof(Move));
                s->to = to;
                s->next = (Move*)NULL;
                lastMov->next = s;
            }
        }
        return 0;
    }
    printf("Setting NFA state failed. Invalid Character\n");
    return -1;
}

/* 
 * Builds DFA from the complete NFA 
 */
State* buildDFA()
{
    State* state;
    return state;
}
