#ifndef PARSER
#define PARSER

#include <stdlib.h>

#include "lexer.c"

enum ExpressionType {
  SEXP, ARGS, EPSILON
};

struct Expression {
  enum ExpressionType type;
  struct Expression * args;
  int argValue;
};

struct Expression getNextExpression(FILE *inStream) {
  struct Token nextToken = getNextToken(inStream);

  struct Expression result;

  switch (nextToken.type) {
  case OPENSYM:
    result.type = SEXP;

#ifdef DEBUG
    printf("Parsing Sexp.\n");
#endif

    // Slurp function (ADDSYM).
    getNextToken(inStream);

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
  case NUM:
    result.type = ARGS;
    result.argValue = nextToken.value;

    result.args = malloc(sizeof(struct Expression));
    *(result.args) = getNextExpression(inStream);

    break;
  case CLOSESYM:

#ifdef DEBUG
    printf("Slurped Closesym\n");
#endif
    
    // End the args descent.
    result.type = EPSILON;
    result.args = NULL;
    break;
  default:
    printf("Error. Unexpected Token.");
    break;
  }

  return result;
}

#endif // parser.c
