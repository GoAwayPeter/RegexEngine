#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    if(initNFAStates(128) == (State*)NULL)
        printf("Failed to initialise NFA states\n");

    printf("Test 0: Are states properly linked?\n");
    int x = 0;
    State* state = getCurrNFAState();
    int testStates = 127;
    for(i = 0;i < testStates;i++)
    {
        state = state->next;
        x++;
//        printf("%d ",x);  //segfaults if this is here.
    }
    if(state == NULL)
        printf("oh no! We've got to a NULL state\n\n");

    for(i = 0;i < testStates; i++)
    {
        if(state != NULL)
        {
            if(state->prev == NULL) {
                printf("Prev state pointer is NULL");
                break;
            }
            state = state->prev;
            x++;
        }
        else
            printf("state is null");
    }
    if(x == 2*testStates && state != NULL)
        printf("Test 0: States are linked properly!\n\n");

    //Test 1 for setNFAStateRelation 
    printf("Test 1: adding 1 symbol to 94 consecutive states, should print all ascii chars\n");

    State* start = getCurrNFAState();
    int j;
    for(j = 32;j < 128;j++)
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
    printf("Test 2: Adding lots of different symbols to the same rule\n");
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
        list = list->next;
    }
    printf("\nTest 2: completed successfully.\n");

    printf("\nTest 3: Adding lots of states to the same rule.\n");

    State* nextState;
    State* lastState;
    int numFailedSetState = 0;
    for(i = 2;i < 10000;i++) //works with 100,000 but is a bit slow
    {
        if(setNFAStateRelation(currentChar + 1, getNextNFAState(i)) == -1)
            numFailedSetState++;

        List* s = getNFAStates(currentChar + 1);
        int o = 0;
        while(s != NULL)
        {
            o++;
            s = s->next;
        }
        if(o + numFailedSetState != i)
        {
            printf("Warning, o and i not equal! o= %d, i= %d\n",o,i);
            printf("numFailedSetState %d\n",numFailedSetState);
            return 0;
        }
    }

    printf("\nTest 4: Getting NFA States\n");
    List* s = getNFAStates(currentChar + 1);
    int o = 0;
    while(s->next != NULL)
    {
        o++;
        s = s->next;
    }
    if(o == 9998 - numFailedSetState)
        printf("\nTests 3 & 4 completed successfully\n\n");
    else
        printf("\n Test 3 or 4 failed, %d states found, %d states set\n\n", o, 9998 - numFailedSetState);
}
