#ifndef GENERATOR
#define GENERATOR

#include <stdlib.h>

#include "parser.c"

int evalExpression(struct Expression expr) {
  int result;
  
  switch (expr.type) {
  case SEXP:
    {

#ifdef DEBUG
      printf("Evaluating Sexp.\n");
#endif
      
      struct Expression * argsPointer = expr.args;
      result = 0;

#ifdef DEBUG
      printf("Beginning the arg linked list.\n");
      printf("First Pointer: %p\n", argsPointer);
#endif

      while (argsPointer != NULL) {

#ifdef DEBUG
      printf("Started one arg.\n");
      printf("Current val: %d\n", argsPointer->argValue);
      printf("Current type: %d\n", argsPointer->type);
#endif
	
	int currentArg = evalExpression(*argsPointer);
	result += currentArg;

	void * tmp = argsPointer;
	argsPointer = argsPointer->args;
	free(tmp);

#ifdef DEBUG
	printf("Finished one arg.\n");
	printf("Next Pointer: %p\n", argsPointer);
#endif
      }

#ifdef DEBUG
      printf("Finished Sexp.\n");
#endif // DEBUG
      
    }
    break;
  case ARGS:
    result = expr.argValue;

#ifdef DEBUG
    printf("Evaluated Args.\n");
#endif // DEBUG
    
    break;
  case EPSILON:
    result = 0;
    break;
  default:
    printf("Error, Unknown Expression.\n");
    result = 0;
    break;
  }

  return result;
}


#endif // generator.c
