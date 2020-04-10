#include "meshell.h"

MeshStatus loadConfig(MeshConfig* config) {
  config->hostname = getNotNULLString(3, getenv("HOSTNAME"), getenv("HOST"), getenv("NAME"));
  config->username = getNotNULLString(1, getenv("LOGNAME"));
  return RETURN_SUCCESS;
}
