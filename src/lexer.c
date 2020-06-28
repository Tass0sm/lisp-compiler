#ifndef LEXER
#define LEXER

#include <stdio.h>

enum TokenType {
  OPENSYM, CLOSESYM, ADDSYM, NUM
};

struct Token {
  enum TokenType type;
  int value;
};
  
struct Token getNextToken(FILE * inStream) {
  //Read all the whitespace until arriving at a possible token.
  char c;

  do {
    c = fgetc(inStream);
  } while (c == ' ' || c == '\t' || c == '\n');

#ifdef DEBUG
  printf("Read character %c\n", c);
#endif

  struct Token result;
  
  switch (c) {
  case '(':
    result.type = OPENSYM;
    break;
  case ')':
    result.type = CLOSESYM;
    break;
  case '+':
    result.type = ADDSYM;
    break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    result.type = NUM;
    int val = (c - '1') + 1;
    result.value = val;
    break;
  default:
    printf("Error, Unexpected Character: %c\n", c);
    break;
  }

  return result;
}

#endif // lexer.c