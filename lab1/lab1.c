#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // char message[30];

  printf("Please enter some text: ");
  // scanf("%s", argv[i]); // taking in user string inputs
  // printf("have %d arguments\n", argc);

  printf("Tokens:\n");
  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }
  return 0;
}
