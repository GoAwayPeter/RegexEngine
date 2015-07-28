#ifndef _AUTOMATA_H_
    #define _AUTOMATA_H_

#define NUMSYMBOLS 128
typedef long int state;

void initStates();
void printStateTable();
state getState(state toGet);
state setState(state toGet, char ch, state input);


#endif
