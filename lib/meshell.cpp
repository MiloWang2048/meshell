#include "meshell.h"

int main(int argc, char** argv) {
  splashPrint();
  // Load config files, if any.
  MeshConfig* config = new MeshConfig;
  load_config(config);
  // Run command loop.
  while (1) {
    int result = cmd_loop(config);
    if (result == SIGNAL_EXIT) break;
    if (cin.fail() || cin.eof()) break;
  }
  // Perform any shutdown/cleanup.
  delete config;
  return 0;
}