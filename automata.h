#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
#define EPSILON 0
#define NOMOVE //TODO
typedef unsigned long states;

/*
 * NFA related functions
 */
void initNFAStates();
void printNFAStateTable();
state getNFAStateRelation(state toGet, char ch);
state setNFAStateRelation(char ch,state toGet, state input);

#endif
