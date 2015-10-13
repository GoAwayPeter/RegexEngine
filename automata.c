#include <stdlib.h>
#include <stdio.h>
#include "automata.h"

static states **symbols;
static long int numStates;

void initNFAStates()
{
    /* NFA state table is a 2D array of unsigned long (states) types, 
     * where each unsigned long is 8 bytes, and each byte of the 
     * long is used as a number in its own right, representing
     * a state change. This removes the need for a 3D array, which 
     * would be incredibly messy and horrible. Ew.
     * 
     */
    int i,j;
    numStates = 256;
    symbols = malloc(numStates * sizeof(*symbols));
    for(i = 0;i < numStates;i++)
    {
        symbols[i] = malloc(NUMSYMBOLS * sizeof(states));
        for(j = 0;j < NUMSYMBOLS;j++)
            symbols[i][j] = EPSILON;
    }
}

void freeNFAStates()
{
    int i,j;
    for(i = 0;i < numStates;i++)
    {
        free(symbols[i]);
    }
}

void printNFAStateTable()
{
    printf("\n");
    int i, j; 
    for(i = 0;i < numStates;i++)
    {
        printf("%d \t",i);
        for(j = 0;j < NUMSYMBOLS;j++)
        {
            printf("%ld",symbols[i][j]);
        }
        printf("\n");
    }
}

state getNFAStateRelation(states toGet, char ch)
{
    /*
     * TODO
     * THIS IS JUST PLACEHOLDER CODE
     */
    return symbols[(int)toGet][(int)ch];
}

state setNFAStateRelation(char ch, states from, states to)
{
    if(from >= 0 && from < numStates &&
        to >= 0 && to < numStates)
    {
        symbols[from][ch] = to;

        return to;
    }
    else
    {
        printf(" %ld %ld \n",from,to);
        return -1;
    }
}
