#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) != (State*)NULL)
        printf("initNFAStates returned correctly\n");

    //test setNFAStateRelation function
    printf("adding 1 symbol to 128 consecutive states, should print ascii table\n");
    State* start = getCurrState();
    int j;
    for(j = 0;j < 10;j++)
    {
        for(i = 32;i < 40;i++)
        {
            setNFAStateRelation((char)i,getCurrState(),getNextState(1)); 
            if(setCurrState(getNextState(1)) == -1)
                printf("set current state failed %d\n",i);
        }
    }
    setCurrState(start);
    for(i = 32;i < 160;i++)
    {
        if(getCurrState()->rool != (Rule*)NULL)
            printf("%c",(char)getCurrState()->rool->rule);
        if(setCurrState(getNextState(1)) == -1)
                printf("set current state failed %d\n",i);
    }
    printf("\n");
}
