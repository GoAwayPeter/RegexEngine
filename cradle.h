#ifndef _CRADLE_H_
    #define _CRADLE_H_

#define REGEXDATASIZE 100
/*
 * Global data;
 */
char *__cradle_look;
static char *__cradle_lookBegin;
char *__cradle_regexData;
char *__cradle_file;

char *getChars(int argc, char **argv);

char getCurrChar();

char getNextChar();

char getPrevChar();

int isWildCard(char wildcard);

int isAlpha(char alpha);

int isDigit(char digit);

int isUpperCase(char alpha);

int isLowerCase(char alpha);

int isRepOp(char op);

void parseError(char *s);

void memoryError(char *s);

#endif

