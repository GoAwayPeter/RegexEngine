#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 27

/* 
 * NFA data structure
 */
struct State;

typedef struct Move{
    struct State* change;
    struct Move* next;
} Move;

/*
 * List of possible states to change to on given rule
 * possibly rename to Rule?
 */
typedef struct Rule{
    int (*rule)(char); 
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
State* advanceState(int n); //advances current state n times
State* getNextState(int n); //gets nth state in front of current 
int setCurrState(State* s);
State* getCurrState();
State* getPrevState(int n); //goes back n times
State* getNFAStateRelation(State* toGet, char symbol);
int setNFAStateRelation(char symbol, State* from, State* to);

#endif
