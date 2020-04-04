#include "meshell.h"

void printPrompt();

int cmd_loop() {
  printPrompt();
  getchar();
  return EXIT_SUCCESS;
}

void printPrompt() {
  char* cwd = getcwd(NULL, 0);
  char* hostName = getNotNULLString(3, getenv("HOSTNAME"), getenv("HOST"), getenv("NAME"));
  char* userName = getenv("LOGNAME");
  // \e[xxm changes terminal font color. 34: fore-blue, 32: fore-green, 0: default.
  printf("\e[34m%s@%s\e[0m:\e[32m%s\e[0m$ ", userName, hostName, cwd);
}