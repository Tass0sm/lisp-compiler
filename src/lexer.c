#ifndef LEXER
#define LEXER

#include <stdio.h>
#include <ctype.h>

enum TokenType {
  OPENSYM, CLOSESYM, ADDSYM, SUBSYM, MULSYM, DIVSYM, NUM
};

struct Token {
  enum TokenType type;
  int value;
};

char peek;

struct Token getNextToken(FILE * inStream) {
  //Read all the whitespace until arriving at a possible token.
  char c;

  do {
    c = fgetc(inStream);
  } while (c == ' ' || c == '\t' || c == '\n');

#ifdef DEBUG
  printf("Read character %c\n", c);
#endif

  peek = fgetc(inStream);
  
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
  case '-':
    result.type = SUBSYM;
    break;
  case '*':
    result.type = MULSYM;
    break;
  case '/':
    result.type = DIVSYM;
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

    int val = c - '0';

    while (isdigit(peek)) {
      val *= 10;
      val += peek - '0';
      peek = fgetc(inStream);
    }

    result.value = val;
    break;
  default:
    printf("Error, Unexpected Character: %c\n", c);
    break;
  }

  ungetc(peek, inStream);
  
  return result;
}

#endif // lexer.c
