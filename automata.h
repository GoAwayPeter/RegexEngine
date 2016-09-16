#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 27
#define DEBUG 0

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
    int finishing;
} State;


/* Linked list of pointers to States */

typedef struct List{
    struct State* state;
    struct List* next;
    struct List* prev;
} List;

/* Struct to pass to functions */
typedef struct Params{
    State* currentState;
    State* firstState;
    int statesAllocated;
    State* returned;
} Params;

/************
 * Functions!
 ************/

/*
 * Initialisation function. Call before doing anything
 */
Params* initNFAStates(int numStates);
/*
 * Go forward n states
 */
State* getNextNFAState(int n, Params* params);  
/*
 * Go back n states
 */
State* getPrevNFAState(int n, Params* params); 
/* 
 * Returns linked list of pointers to states reachable by symbol 
 */
List* getNFAStates(char symbol, Params* params);
/* 
 * Sets NFA state relation
 */
int setNFAStateRelation(char symbol, State* to, Params* params);

/* 
 * Builds DFA state from current NFA. Ensure current state
 * is set to the initial state of the NFA. Only call once the
 * NFA is finished!
 */
List* buildDFA(Params* params);

#endif
