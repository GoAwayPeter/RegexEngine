#include "../automata.h"
#include <stdio.h>

int main(int argc, char** argv)
{   int i;
    //test init func
    Params* params = initNFAStates(128);
    if(params->currentState == (State*)NULL)
        printf("Failed to initialise NFA states\n");

    printf("Test 0: Are states properly linked?\n");
    int x = 0;
    State* state = params->currentState;
    int testStates = 127;
    for(i = 0;i < testStates;i++)
    {
        state = state->next;
        x++;
//        printf("%d ",x);  //weird behaviour seen with this with alternative allocation scheme
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

    State* start = params->currentState;
    int j;
    for(j = 32;j < 128;j++)
    {
        setNFAStateRelation((char)j, getNextNFAState(1, params), params); 
        if((params->currentState = getNextNFAState(1, params)) == (State*)NULL)
            printf("set current state failed %d\n",j);
    }
    params->currentState = start;
    for(i = 32;i < 127;i++)
    {
        if(params->currentState->rool != (Rule*)NULL)
            printf("%c", (char)params->currentState->rool->symbol);
        if((params->currentState = getNextNFAState(1, params)) == (State*)NULL)
            printf("set current state failed %d\n",i);
    }
    printf("\nTest 1 completed successfully.\n\n\n");

    //Test 2 for setNFAStateRelation
    printf("Test 2: Adding lots of different symbols to the same rule\n");
    params->currentState = getPrevNFAState(40, params);
    printf("current char is %c\n", (char)params->currentState->rool->symbol);
    char currentChar = (char)params->currentState->rool->symbol;
    for(i = 0;i < 95;i++) 
    {
        setNFAStateRelation(((currentChar + i) % 94) + 32, getNextNFAState(1, params), params);
    }

    List* list;
    for(i = 0;i < 94;i++) 
        list = getNFAStates((currentChar + i) % 94 + 32, params);
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
    int stateToSet = 74;
    int startFrom = 0;
    Params params_copy;
    params_copy.currentState = params->currentState;
    for(i = startFrom;i < stateToSet;i++) 
    {
        printf("%0x ",params_copy.currentState->next);
        if(setNFAStateRelation(currentChar + 1, getNextNFAState(1, &params_copy), params) == -1)
            numFailedSetState++;
        params_copy.currentState = params_copy.currentState->next;

        List* s = getNFAStates(currentChar + 1, params);
    }

    printf("\nTest 4: Getting NFA States\n");
    List* s = getNFAStates(currentChar + 1, params);
    int o = 0;
    while(s->next != NULL)
    {
        o++;
        s = s->next;
    }
    if(o == stateToSet - startFrom - numFailedSetState)
        printf("\nTests 3 & 4 completed successfully\n\n");
    else
        printf("\n Test 3 or 4 failed, %d states found, %d states set\n\n", o, stateToSet - startFrom - numFailedSetState);
}
