#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) == (State*)NULL)
        printf("Failed to initialise NFA states\n");

    int x = 0;
    State* state = getCurrNFAState();
    while(state->next != NULL)
    {
        state = state->next;
        x++;
        printf("%d",x);
    }
    while(state->prev != NULL)
    {
        state = state->prev;
        x++;
    }
    if(x != 256)
        printf("States are not linked properly! %d\n",x);

    //Test 1 for setNFAStateRelation 
    printf("Test 1: adding 1 symbol to 94 consecutive states, should print all ascii chars\n");

    State* start = getCurrNFAState();
    int j;
    for(j = 32;j < 127;j++)
    {
        setNFAStateRelation((char)j, getNextNFAState(1)); 
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
        setNFAStateRelation(((currentChar + i) % 94) + 32, getNextNFAState(1));
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

    int offset = 0;
    State* nextState;
    State* lastState;
    for(i = 1;i < 5000;i++) //works with 100,000 but is a bit slow
    {
        setNFAStateRelation(currentChar, getNextNFAState(i)); //this fails at 329, and then every 256th call (every time states are allocated)
        List* s = getNFAStates(currentChar);
        int o = offset;
        while(s != NULL)
        {
            o++;
            s = s->next;
        }
        if(o != i)
        {
            printf("Warning, o and i not equal! o= %d, i= %d\n",o,i);
            offset++;
        }
    }


    printf("\nTest 3: Getting NFA States\n\n");
    List* s = getNFAStates(currentChar);
    int o = 0;
    while(s != NULL)
    {
        o++;
        s = s->next;
    }
    if(o == 4999)
        printf("\nTest 4 completed successfully\n\n");
    else
        printf("\n Test 4 failed, %d states found\n\n", o);
}
