#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 27

/*
 * Globals
 */
struct State;
static struct State* __automata_currNFAState;
static unsigned int __automata_statesAllocated;

/* 
 * NFA data structure
 */
typedef struct Move{
    struct State* to;
    struct Move* next;
} Move;

/*
 * List of possible states to change to on given rule
 * possibly rename to Rule?
 */
typedef struct Rule{
//    int (*rule)(char);  //TODO why was I going to do this?
    char symbol;
    struct Move* mov;
    struct Rule* next;
} Rule;

typedef struct State{
    struct Rule* rool;
    struct State* next;
    struct State* prev;
} State;

/*
 * NFA related functions
 */

State* initNFAStates(int numStates);
//State* advanceState(int n); //advances current state n times
/*
 * Go forward n states
 */
State* getNextState(int n);  
/*
 * Go back n states
 */
State* getPrevState(int n); 
int setCurrState(State* s);
State* getCurrState();
/* 
 * Is this necessary?
 */
State* getNFAStateRelation(State* toGet, char symbol);
/* 
 * Sets NFA state relation
 */
int setNFAStateRelation(char symbol, State* from, State* to);
/* 
 * Returns linked list of States can move to from 'from' State on
 * symbol 
 */
State* moveState(State* from, char symbol);
void printStates();

#endif
