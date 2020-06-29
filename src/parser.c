#ifndef PARSER
#define PARSER

#include <stdlib.h>

#include "lexer.c"

enum FuncType {
  ADD, SUB, MUL, DIV
};

enum ExpressionType {
  SEXP, FUNC, ARGS, EPSILON
};

struct Expression {
  enum ExpressionType type;
  struct Expression * func;
  struct Expression * args;
  int value;
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
    printf("Slurped Addsym.\n");
#endif
    
    // Get Args Expression
    result.args = malloc(sizeof(struct Expression));
    *(result.args) = getNextExpression(inStream);


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
    result.type = ARGS;
    result.value = nextToken.value;

    result.args = malloc(sizeof(struct Expression));
    *(result.args) = getNextExpression(inStream);

    if ((result.args)->type == EPSILON) {
      free(result.args);
      result.args = NULL;
    }
    
    break;
  }
  case CLOSESYM: {

#ifdef DEBUG
    printf("Slurped Closesym\n");
#endif
    
    // End the args descent.
    result.type = EPSILON;
    result.args = NULL;
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
