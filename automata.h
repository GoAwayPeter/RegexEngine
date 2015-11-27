#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 0
#define NOMOVE //TODO

typedef struct State {
    struct State* symbolArray;
    struct State* next;
    struct State* prev;
} State;

/* 
 * Position in symbolArray is Symbol value
 */
typedef struct Symbol{
    State* changeTo;
    struct Symbol* next;
} Symbol;


/*
 * NFA related functions
 */
State* initNFAStates();
State* addNFAStates();
State* nextState(State* s);
State* prevState(State* s);
State* getNFAStateRelation(State* toGet, char symbol);
State* setNFAStateRelation(char symbol, State* from, State* to);
void printNFAStateTable();

#endif
