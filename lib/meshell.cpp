#include "meshell.h"

int main(int argc, char** argv) {
  // Load config files, if any.
  MeshConfig* config = new MeshConfig;
  loadConfig(config);
  // Run command loop.
  while (1) {
    int result = cmd_loop(config);
    if (result == SIGNAL_EXIT) break;
  }
  // Perform any shutdown/cleanup.
  return 0;
}