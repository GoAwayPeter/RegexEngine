#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) == (State*)NULL)
        printf("Failed to initialise NFA states\n");

    //Test 1 for setNFAStateRelation 
    printf("Test 1: adding 1 symbol to 94 consecutive states, should print all ascii chars\n");

    State* start = getCurrNFAState();
    int j;
    for(j = 32;j < 127;j++)
    {
        setNFAStateRelation((char)j, getCurrNFAState(), getNextNFAState(1)); 
        if(setCurrNFAState(getNextNFAState(1)) == -1)
            printf("set current state failed %d\n",j);
    }
    setCurrNFAState(start);
    for(i = 32;i < 127;i++)
    {
        if(getCurrNFAState()->rool != (Rule*)NULL)
            printf("%c", (char)getCurrNFAState()->rool->symbol);
        if(setCurrNFAState(getNextNFAState(1)) == -1)
            printf("set current state failed %d\n",i);
    }
    printf("\nTest 1 completed successfully.\n\n\n");

    //Test 2 for setNFAStateRelation
    printf("Test2: Adding lots of different symbols to the same rule\n");
    setCurrNFAState(getPrevNFAState(40));
    printf("current char is %c\n", (char)getCurrNFAState()->rool->symbol);
    char currentChar = (char)getCurrNFAState()->rool->symbol;
    for(i = 0;i < 95;i++) 
    {
        setNFAStateRelation(((currentChar + i) % 94) + 32, getCurrNFAState(), getNextNFAState(1));
    }

    List* list;
    for(i = 0;i < 94;i++) 
        list = getNFAStates((currentChar + i) % 94 + 32);
    while(list != (List*)NULL)
    {
        Rule* ruleptr = list->state->prev->rool;
        while(ruleptr != NULL)
        {
            printf("%c",ruleptr->symbol); //printing added symbols
            ruleptr = ruleptr->next;
        }
        printf("\n");
        list = list->next;
    }
    printf("\nTest 2: completed successfully.\n\n");

    printf("\nTest 3: Adding lots of states to the same rule.\n\n");

    for(i = 0;i < 10000;i++) //works with 100,000 but is a bit slow
    {
        setNFAStateRelation(currentChar, getCurrNFAState(), getNextNFAState(i));
    }

    printf("\nTest 3 completed successfully.\n\n");
}
