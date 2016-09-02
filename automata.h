#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 27
#define DEBUG 0

/*
 * Globals
 */
struct State;
static struct State* __automata_currNFAState;
static unsigned int __automata_statesAllocated;

/* 
 * Automata data structure
 */
typedef struct Move{
    struct State* to;
    struct Move* next;
} Move;

typedef struct Rule{
    char symbol;
    struct Move* mov;
    struct Rule* next;
} Rule;

typedef struct State{
    struct Rule* rool;
    struct State* next;
    struct State* prev;
} State;


/* Linked list of pointers to States */

typedef struct List{
    struct State* state;
    struct List* next;
} List;

/************
 * Functions!
 ************/

/*
 * Initialisation function. Call before doing anything
 */
State* initNFAStates(int numStates);
/*
 * Go forward n states
 */
State* getNextNFAState(int n);  
/*
 * Go back n states
 */
State* getPrevNFAState(int n); 
/*
 * Sets the current state to the one specified
 */
int setCurrNFAState(State* s);
/*
 * Returns pointer to current state
 */
State* getCurrNFAState();
/* 
 * Returns linked list of pointers to states reachable by symbol 
 */
List* getNFAStates(char symbol);
/* 
 * Sets NFA state relation
 */
int setNFAStateRelation(char symbol, State* from, State* to);

/* 
 * Builds DFA state from current NFA. Ensure current state
 * is set to the initial state of the NFA. Only call once the
 * NFA is finished!
 */
State* buildDFA();

#endif
