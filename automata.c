#include <stdlib.h>
#include <stdio.h>
#include "automata.h"
/*
 * TODO
 * - optimisations (not really)
 *   - fix commented allocStates() function
 * - nfa to dfa conversion (important!)
 */

/*
 * ## Internal function
 * Allocates memory for nfa states - this is called in
 * the initialisation of the states, and if we request
 * the 'next' state, but it doesn't exist yet
 */
State* allocStates(int statesToAlloc)
{   int i; //this took 4.4s to run tests with last test creating 10000 states
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
    /*  /// THIS BREAKS EVERYTHING ////
     *  TODO: make this work.
     *
    int i; 
    State *this, *prev, *start;
    prev = (State*)NULL;
    this = malloc(statesToAlloc * sizeof(State));
    start = this;
    for(i = 0;i < statesToAlloc;i++)
    {
        this->next = this + sizeof(State);
        this->prev = prev;
        prev = this;
        this = this->next;
    }
    this->next = (State*)NULL;
    this->prev = prev;
    return start;
    */
}

/*
 * Initialise the automata library
 */
Params* initNFAStates(int numStates)
{
    Params* params = malloc(sizeof(Params));
    params->currentState = allocStates(numStates);
    params->firstState   = params->currentState;
    params->statesAllocated = numStates;
    if(params->currentState == (State*)-1) 
    {
        printf("Error initialising NFA states\n");
        exit(1);
    }
    return params;
}

/*
 * Gets the next State from the current State
 */
State* getNextNFAState(int n, Params* params)
{   int i;
    int hitEnd = 0;
    State* last;
    State* state = params->currentState;
    if(n > 0)
    {
        for(i = 0;i < n;i++)
        {
            if(state->next != (State*)NULL)
            {
                last = state;
                state = state->next;
            }
            else
            {
                if(DEBUG)
                    printf("\nAllocating more NFA states\n");
                params->statesAllocated = 2 * params->statesAllocated;
                state->next = allocStates(2 * params->statesAllocated);
                state->next->prev = state->next;
            }
        }
    }
    return state;
}

/*
 * Get the previous state from the current State
 */
State* getPrevNFAState(int n, Params* params)
{   int i;
    int hitEnd = 0;
    State* t = params->currentState;
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
 * Returns 1 if state has move on symbol, 0 if not
 */
int hasMove(State* state, char symbol)
{
    if(state == NULL)
        return -1;
    Rule* rule = state->rool;
    while(rule != NULL)
    {
        if(rule->symbol == symbol)
            return 1;
        rule = rule->next;
    }
    return 0;
}

/* 
 * Returns linked list of pointers to states reachable by symbol 
 * from the current State
 * TODO does not take into account epsilon moves after symbol
 */
List* getNFAStates(char symbol, Params* params)
{
    List* startList = NULL, *currList = NULL, *lastList = NULL;
    Rule* rule = NULL;
    Move* move = NULL;
    int count = 0;

    if(params->currentState->rool != NULL)
    {
        rule = params->currentState->rool;
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
                    }
                    currList->state = move->to;
                    lastList = currList;
                    currList = currList->next;
                    ++count;
                    move = move->next;
                }
            }
            rule = rule->next;
        }
        if(DEBUG)
            printf("Found %d states for symbol %c\n",count, symbol);
    }
    // Recursively call this function to get all EPSILON moves
    if(hasMove(params->currentState->next,EPSILON))
    {
        Params params_copy;
        params_copy.currentState = params->currentState->next;
        currList->next = getNFAStates(EPSILON, &params_copy);
    }
    return startList;
}

/*
 * Sets a relation between 2 states, from current state
 * returns 0 on success, -1 on failure
 */
int setNFAStateRelation(char symbol, State* to, Params* params)
{
    State* from = params->currentState;
    if(from == NULL || to == NULL)
    {
        if(DEBUG)
        {
            if(from == NULL)
                printf("Error: 'from' state is NULL!\n");
            if(to == NULL)
                printf("Error: 'to' state is NULL!\n");
        }
        return -1;
    }
    if(( symbol < 127 && symbol >= 32) || symbol == EPSILON || symbol == '.')
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
            int count = 0;
            while(t != (Rule*)NULL)
            {
                if(t->symbol == symbol)
                {
                    found = 1;
                    break;
                }
                lastRule = t;
                count++;
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
                        return -1; //move already exists
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
    printf("Error: setting NFA state failed. Invalid Character\n");
    return -1; 
}

/* 
 * Builds DFA from the complete NFA 
 *
 *
 * Allocate new set of states //necessary?
 * epsilon closure
 * then step through converting 
 */
List* buildDFA(Params* params)
{
    List* startStateList = malloc(sizeof(List));
    List* currStateList = startStateList;
    currStateList->state = params->firstState;
    Rule* currRool = currStateList->state->rool;
    while(currStateList != NULL)
    {
        while(currRool != NULL)
        {
             if(currRool->next != NULL)
                 currRool = currRool->next;
             else
                 break;
        }
        if(currStateList->next != NULL)
            currStateList = currStateList->next;
        else 
            break;
    }
    return currStateList;
}
