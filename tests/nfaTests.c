#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) != (State*)NULL)
        printf("initNFAStates returned correctly\n");

    //test setNFAStateRelation function
    printf("adding 1 symbol to 128 consecutive states, should print \
            ascii table\n");
    State* start = getCurrState();
    for(i = 0;i < 128;i++)
    {
        setNFAStateRelation((char)i,getCurrState(),getNextState(1)); 
        if(setCurrState(getNextState(1)) == (State*)NULL)
            printf("Null curr state! ARghhhh!!!");
    }
    setCurrState(start);
    for(i = 0;i < 128;i++)
    {
        printf("%c",getCurrState()->symbol->val);
        setCurrState(getNextState(1));
    }

}
