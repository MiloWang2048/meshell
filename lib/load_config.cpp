#include "meshell.h"

void set_shell_env();

MeshStatus load_config(MeshConfig* config) {
  set_shell_env();
  config->hostname = getNotNULLString(3, getenv("HOSTNAME"), getenv("HOST"), getenv("NAME"));
  config->username = getNotNULLString(1, getenv("LOGNAME"));
  return RETURN_SUCCESS;
}

void set_shell_env() {
  string path(getcwd(NULL, 0));
  path += "mesh";
  setenv("shell", path.c_str(), 1);
}