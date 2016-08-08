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
 * - reuse this structure for DFA's?
 *   too flexible - will allow invalid DFA states
 */
typedef struct Move{
    struct State* to;
    struct Move* next;
} Move;

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


/* List of pointers to States */

typedef struct List{
    struct State* state;
    struct List* next;
    struct List* prev;
} List;

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
 * Returns array of pointers to states reachable by symbol 
 */
List* getNFAStates(char symbol);
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
