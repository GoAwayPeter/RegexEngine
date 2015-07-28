#include <stdlib.h>
#include <stdio.h>
#include "automata.h"

static state **symbols;
static int numRows;

void initStates()
{
    int i,j;
    symbols = (state**)malloc(200 * sizeof(char));
    for(i = 0;i < 200;i++)
    {
        symbols[i] = (state*)malloc(NUMSYMBOLS * sizeof(state));
        for(j = 0;j < 128;j++)
            symbols[i][j] = 0;
    }
}

void printStateTable()
{
    int i, j; 
    for(i = 0;i < 200;i++)
    {
        for(j = 0;j < NUMSYMBOLS;j++)
            printf("%ld",symbols[i][j]);
        printf("\n");
    }
}

state getStateRelation(state toGet, char ch)
{
    //TODO 
    return symbols[(int)toGet][(int)ch];
}

state setState(state toGet, char ch, state input)
{
    symbols[(int)toGet][(int)ch] = input;
    return input;
}
