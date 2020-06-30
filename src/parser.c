#ifndef PARSER
#define PARSER

#include <stdlib.h>
#include "lexer.c"

enum FuncType {
  ADD, SUB, MUL, DIV
};

enum ExpressionType {
  SEXP, FUNC, ARG
};

struct Expression {
  enum ExpressionType type;
  int value;
  struct Expression * func;
  struct Expression * args[10];
};

struct Expression getNextExpression(FILE *inStream) {
  struct Token nextToken = getNextToken(inStream);

  struct Expression result;

  switch (nextToken.type) {
  case OPENSYM: {
    result.type = SEXP;

#ifdef DEBUG
    printf("Parsing Sexp.\n");
#endif

    // Get Function Expression
    result.func = malloc(sizeof(struct Expression));
    *(result.func) = getNextExpression(inStream);

#ifdef DEBUG
    printf("Parsed func.\n");
#endif

    int argIndex = 0;
    while (peek != ')') {
      // Get Args Expression
      result.args[argIndex] = malloc(sizeof(struct Expression));
      *(result.args[argIndex]) = getNextExpression(inStream);
      argIndex++;
    }

    result.args[argIndex] = NULL;

    // Slurp Close Sym
    getNextToken(inStream);

#ifdef DEBUG
    printf("Stored the args linked list and slurped close sym.\n");
#endif
    break;
  }
  case ADDSYM: {
    result.type = FUNC;
    result.value = ADD;
    break;
  }
  case SUBSYM: {
    result.type = FUNC;
    result.value = SUB;
    break;
  }
  case MULSYM: {
    result.type = FUNC;
    result.value = MUL;
    break;
  }
  case DIVSYM: {
    result.type = FUNC;
    result.value = DIV;
    break;
  }
  case NUM: {
    result.type = ARG;
    result.value = nextToken.value;
    
#ifdef DEBUG
    printf("Parsed one arg.\n");
#endif // DEBUG
    break;
  }
  default: {
    printf("Error. Unexpected Token.");
    break;
  }
  }

  return result;
}

#endif // parser.c
