#include "meshell.h"

MeshStatus mesh_cd(MeshConfig* config, Args args);
MeshStatus mesh_echo(MeshConfig* config, Args args);

MeshStatus built_in_cmds(MeshConfig* config, Args args) {
  string cmd = args[0];
  if (cmd == "cd") {
    return mesh_cd(config, args);
  } else if (cmd == "echo") {
    return mesh_echo(config, args);
  }
  return CMD_FALLTHROUGH;
}

MeshStatus mesh_cd(MeshConfig* config, Args args) {
  if (args.size() == 2) {
    string errmsg = "";
    int res = chdir(args[1].c_str());
    if (res == -1)
      cout << "invalid directory." << endl;
  } else {
    chdir(("/home/" + config->username).c_str());
  }
  return CMD_CAPTURED;
}

MeshStatus mesh_echo(MeshConfig* config, Args args) {
  for (int i = 1; i < args.size(); i++) {
    cout << args[i] << endl;
  }
  return CMD_CAPTURED;
}
