#include "meshell.h"

void loadConfig(MeshConfig* config) {
  config->cwd = getNotNULLString(1, getcwd(NULL, 0));
  config->hostname = getNotNULLString(3, getenv("HOSTNAME"), getenv("HOST"), getenv("NAME"));
  string userName = getNotNULLString(1, getenv("LOGNAME"));
}
