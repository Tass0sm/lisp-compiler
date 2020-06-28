#include <stdio.h>

#include "lexer.c"
#include "parser.c"
#include "generator.c"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No input file.\n");
    return 1;
  }
  
  FILE * script = fopen(argv[1], "r");

  if (script == NULL) {
    printf("Error opening file.\n");
  }

  struct Expression expr = getNextExpression(script);
  int result = evalExpression(expr);

  printf("Result: %d\n", result);
  
  return 0;
}
