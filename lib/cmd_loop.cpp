#include "meshell.h"

void printPrompt(MeshConfig* config);

int cmd_loop(MeshConfig* config) {
  printPrompt(config);
  string cmd;
  getline(cin, cmd);
  return execute_cmd(cmd);
}

void printPrompt(MeshConfig* config) {
  // \e[xxm changes terminal font color. 34: fore-blue, 32: fore-green, 0:
  // default.
  cout << "\e[34m" << config->username
       << "@" << config->hostname
       << "\e[0m:\e[32m" << config->cwd
       << "\e[0m$ ";
}