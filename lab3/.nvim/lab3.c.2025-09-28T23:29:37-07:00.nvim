#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *history[5] = {NULL};
  int count = 0;
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("enter input: ");

    if (getline(&line, &len, stdin) == -1)
      break;

    // did user entered "print"
    if (strncmp(line, "print\n", 6) == 0 || strcmp(line, "print") == 0) {
      int pos = count % 5;
      if (history[pos] != NULL) free(history[pos]);
      history[pos] = strdup(line);
      count++;
      
      // decide where to start printing
      int start;
      if (count > 5) {
        start = count - 5;
      } else {
        start = 0;
      }

      // print last 5 entries
      for (int i = start; i < count; i++) {
        printf("%s", history[i % 5]);
      }
    } else {
      // adding the rest of the inputs to history
      int pos = count % 5;
      if (history[pos] != NULL) free(history[pos]);
      history[pos] = strdup(line);
      count++;
    }
  }
  // free all memory in our history
  for (int i = 0; i < 5; i++) {
    if (history[i] != NULL) free(history[i]);
  }

  free(line);
  return 0;
}
