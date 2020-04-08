#include "meshell.h"

int main(int argc, char** argv) {
  // Load config files, if any.
  // Run command loop.
  while (1) {
    cmd_loop();
  }
  // Perform any shutdown/cleanup.
  return 0;
}