// closh.c - CS 377, Fall 2013
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
  cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
  int i = 0;
  cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
  while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
    cmdTokens[i] = strtok(NULL, " ");
  }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
  char c = getchar();
  while (getchar() != '\n');
  return c;
}

/**
 * Parallel execution
 * @param count - how many times to execute
 * @param cmd - what the command is
 */
void parallel_exec(int count, char* cmdTokens[]) {
  pid_t pid;
  int counter = 0;
  int j = 0;
  while (counter < count) {
    pid = fork();

    if (pid == 0) {
      for (; j<100; j++) {
        printf ("%d\n", j);
        sleep(1);
      }
      execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
    } else if (pid < 0) {
      printf("Fork failed!\n");
    } else {
      counter++;
    }
  }    
}

/**
 * Sequential execution
 * @param count - how many times to execute
 * @param cmd - what the cmd is
 */
void sequential_exec(int count, char* cmdTokens[]) {
  pid_t pid;
  int counter = 0;
  int j = 0;
  while (counter < count) {
    pid = fork();

    if (pid == 0) {
      for (; j<100; j++) {
        printf ("%d\n", j);
        sleep(1);
      }
      execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
    } else if (pid < 0) {
      printf("Fork failed!\n");
    } else {
      waitpid(pid, NULL, 0);
      counter++;
    }
  }    
}

// main method - program entry point
int main() {
  char cmd[81]; // array of chars (a string)
  char* cmdTokens[20]; // array of strings
  int count; // number of times to execute command
  int parallel; // whether to run in parallel or sequentially
  int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)

  while (TRUE) { // main shell input loop

    // begin parsing code - do not modify
    printf("closh> ");
    fgets(cmd, sizeof(cmd), stdin);
    if (cmd[0] == '\n') continue;
    readCmdTokens(cmd, cmdTokens);
    do {
      printf("  count> ");
      count = readChar() - '0';
    } while (count <= 0 || count > 9);
    printf("  [p]arallel or [s]equential> ");
    parallel = (readChar() == 'p') ? TRUE : FALSE;
    do {
      printf("  timeout> ");
      timeout = readChar() - '0';
    } while (timeout < 0 || timeout > 9);
    // end parsing code
    
    ////////////////////////////////////////////////////////
    //                                                    //
    // TODO: use cmdTokens, count, parallel, and timeout  //
    // to implement the rest of closh                     //
    //                                                    //
    // /////////////////////////////////////////////////////

    if (parallel) {
      parallel_exec(count, cmdTokens);
    } else {
      sequential_exec(count, cmdTokens);
    } 

    // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
    exit(1);
  }
}
