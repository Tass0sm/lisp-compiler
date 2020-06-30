#ifndef GENERATOR
#define GENERATOR

#include <stdlib.h>
#include "parser.c"

int addArgs(struct Expression * argList[]);
int subArgs(struct Expression * argList[]);
int mulArgs(struct Expression * argList[]);
int divArgs(struct Expression * argList[]);

int evalExpression(struct Expression expr) {
  int result;
  
  switch (expr.type) {
  case SEXP: {
    
#ifdef DEBUG
    printf("Evaluating Sexp.\n");
#endif

    struct Expression * func = expr.func;
    enum FuncType funcType = evalExpression(*func);

    struct Expression ** argsArray = expr.args;

    switch (funcType) {
    case ADD: {
#ifdef DEBUG
      printf("Adding args.\n");
#endif
      result = addArgs(argsArray);
      break;
    }
    case SUB: {
      result = subArgs(argsArray);
      break;
    }
    case MUL: {
      result = mulArgs(argsArray);
      break;
    }
    case DIV: {
      result = divArgs(argsArray);
      break;
    }
    default:
      printf("Unknown function.\n");
      break;
    }

#ifdef DEBUG
    printf("Finished Sexp.\n");
#endif // DEBUG
      
    break;
  }
  case FUNC: {
    result = expr.value;
    break;
  }
  case ARG: {
    result = expr.value;

#ifdef DEBUG
    printf("Evaluated Arg.\n");
#endif // DEBUG
    
    break;
  }
  default:
    printf("Error, Unknown Expression.\n");
    result = 0;
    break;
  }

  return result;
}

/* Built-in Functions */ 

int addArgs(struct Expression * pArg[]) {
  int result = 0;
  int argIndex = 0;

#ifdef DEBUG
  printf("pArg[0] = %p\n", pArg[0]);
#endif // DEBUG
  
  while (pArg[argIndex] != NULL) {
    result += evalExpression(*(pArg[argIndex]));

#ifdef DEBUG
    printf("Current Result: %d\n", result);
#endif // DEBUG
    
    free(pArg[argIndex]);
    argIndex++;
  }
  
  return result;
}

int subArgs(struct Expression * pArg[]) {
  int result = 0;

  int argIndex = 0;
  if (pArg[argIndex] != NULL) {
    result += evalExpression(*(pArg[argIndex]));
    free(pArg[argIndex]);
    argIndex++;
  }

  while (pArg[argIndex] != NULL) {
    result += evalExpression(*(pArg[argIndex]));
    free(pArg[argIndex]);
    argIndex++;
  }
  
  return result;
}

int mulArgs(struct Expression * pArg[]) {
  int result = 1;

  int argIndex = 0;
  while (pArg[argIndex] != NULL) {
    result *= evalExpression(*(pArg[argIndex]));
    free(pArg[argIndex]);
    argIndex++;
  }
  
  return result;
}

int divArgs(struct Expression * pArg[]) {
  int result = 1;

  int argIndex = 0;
  if (pArg[argIndex] != NULL) {
    result *= evalExpression(*(pArg[argIndex]));
    free(pArg[argIndex]);
    argIndex++;
  }

  while (pArg[argIndex] != NULL) {
    result /= evalExpression(*(pArg[argIndex]));
    free(pArg[argIndex]);
    argIndex++;
  }
  
  return result;
}

#endif // generator.c
