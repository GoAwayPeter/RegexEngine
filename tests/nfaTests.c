#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) == (State*)NULL)
        printf("Failed to initialise NFA states\n");

    //Test 1 for setNFAStateRelation 
    printf("Test1: adding 1 symbol to 94 consecutive states, should print all ascii chars\n");

    State* start = getCurrState();
    int j;
    for(j = 32;j < 127;j++)
    {
        setNFAStateRelation((char)j, getCurrState(), getNextState(1)); 
        if(setCurrState(getNextState(1)) == -1)
            printf("set current state failed %d\n",j);
    }
    setCurrState(start);
    for(i = 32;i < 127;i++)
    {
        if(getCurrState()->rool != (Rule*)NULL)
            printf("%c", (char)getCurrState()->rool->symbol);
        if(setCurrState(getNextState(1)) == -1)
            printf("set current state failed %d\n",i);
    }
    printf("\nSuccess!\n\n\n");

    //Test 2 for setNFAStateRelation
    printf("Test2: Adding lots of different symbols to the same rule\n");
    setCurrState(getPrevState(40));
    printf("current char is %c\n", (char)getCurrState()->rool->symbol);
    char currentChar = (char)getCurrState()->rool->symbol;
    for(i = 2;i < 92;i++)
    {
        setNFAStateRelation((currentChar + i) % 94 + 32, getCurrState(), getNextState(1));
    }
    printf("\nSuccess!\n\n\n");
}
