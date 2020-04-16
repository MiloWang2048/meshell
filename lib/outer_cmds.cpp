#include "meshell.h"

CommandStatus outer_cmds(MeshConfig* config, Args args) {
  char** argMatrix = stringVectorToCharMatrix(args);
  char** p = argMatrix;
  /*while (*p) {
    puts(*p);
    p++;
  }*/
  pid_t pid = fork();
  if (pid == 0) {
    // child process
    //printf("child:%d\n", getpid());
    execvp(args[0].c_str(), argMatrix);
    puts("command not fount");
    exit(-1);
    //exit(0);
  } else if (pid < 0) {
    puts("error: cannot fork.");
  } else {
    // parent process
    int res;
    wait(&res);
    //printf("res:%d\n", res);
    //printf("parent:%d\n", getpid());
  }
  //puts("after:");
  freeCharMatrix(argMatrix);
  return CMD_CAPTURED;
}
