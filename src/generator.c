#ifndef GENERATOR
#define GENERATOR

#include <stdlib.h>

#include "parser.c"

int addArgs(struct Expression * argList);
int subArgs(struct Expression * argList);
int mulArgs(struct Expression * argList);
int divArgs(struct Expression * argList);

int evalExpression(struct Expression expr) {
  int result;
  
  switch (expr.type) {
  case SEXP: {
    
#ifdef DEBUG
    printf("Evaluating Sexp.\n");
#endif

    struct Expression * func = expr.func;
    enum FuncType funcType = evalExpression(*func);

    struct Expression * argsPointer = expr.args;

    switch (funcType) {
    case ADD: {
      result = addArgs(argsPointer);
      break;
    }
    case SUB: {
      result = subArgs(argsPointer);
      break;
    }
    case MUL: {

#ifdef DEBUG
      printf("Multiplying Args\n");
#endif // DEBUG
      
      result = mulArgs(argsPointer);
      break;
    }
    case DIV: {
      result = divArgs(argsPointer);
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
  case ARGS: {
    result = expr.value;

#ifdef DEBUG
    printf("Evaluated Args.\n");
#endif // DEBUG
    
    break;
  }
  case EPSILON: {
    result = 0;
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

int addArgs(struct Expression * pArg) {
  int result = 0;

  while (pArg != NULL) {
    result += evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }
  
  return result;
}

int subArgs(struct Expression * pArg) {
  int result = 0;

  if (pArg != NULL) {
    result += evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }

  while (pArg != NULL) {
    result -= evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }
  
  return result;
}

int mulArgs(struct Expression * pArg) {
  int result = 1;

  while (pArg != NULL) {
    result *= evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }
  
  return result;
}

int divArgs(struct Expression * pArg) {
  int result = 1;

  if (pArg != NULL) {
    result *= evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }

  while (pArg != NULL) {
    result /= evalExpression(*pArg);
    void * tmp = pArg;
    pArg = pArg->args;
    free(tmp);
  }
  
  return result;
}

#endif // generator.c
