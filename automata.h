#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 0
#define NOMOVE //TODO

/* 
 * Position in symbolArray is Symbol value
 */
struct State;

typedef struct Symbol{
    struct State* change;
    struct Symbol* next;
} Symbol;

typedef struct SymList{
    char val;
    struct Symbol* sym;
    struct SymList* next;
} SymList;

typedef struct State{
    struct SymList* symbols;
    struct State* next;
    struct State* prev;
} State;

/*
 * NFA related functions
 */

State* initNFAStates();
State* getNextState(int n); //advances current state n times 
State* getCurrState();
State* getPrevState(int n); //goes back n times and sets curr state
State* getNFAStateRelation(State* toGet, char symbol);
State* setNFAStateRelation(char symbol, State* from, State* to);
void printNFAStateTable();

#endif
