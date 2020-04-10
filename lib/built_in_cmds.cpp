#include <dirent.h>

#include "meshell.h"

CommandStatus mesh_cd(MeshConfig* config, Args args);
CommandStatus mesh_echo(MeshConfig* config, Args args);
CommandStatus mesh_ls(MeshConfig* config, Args args);

CommandStatus built_in_cmds(MeshConfig* config, Args args) {
  string cmd = args[0];
  if (cmd == "cd") {
    return mesh_cd(config, args);
  } else if (cmd == "echo") {
    return mesh_echo(config, args);
  } else if (cmd == "ls") {
    return mesh_ls(config, args);
  } else if (cmd == "pause") {
    cout << "press any key to continue" << endl;
    getch();
    return CMD_CAPTURED;
  } else
    return CMD_FALLTHROUGH;
}

CommandStatus mesh_cd(MeshConfig* config, Args args) {
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

CommandStatus mesh_echo(MeshConfig* config, Args args) {
  for (int i = 1; i < args.size(); i++) {
    cout << args[i] << endl;
  }
  return CMD_CAPTURED;
}

CommandStatus mesh_ls(MeshConfig* config, Args args) {
  DIR* dir;
  struct dirent* ptr;
  int i;
  const char* path = (args.size() == 1) ? getcwd(NULL, 0) : args[1].c_str();
  dir = opendir(path);
  while ((ptr = readdir(dir)) != NULL) {
    printf("%s\n", ptr->d_name);
  }
  closedir(dir);
  return CMD_CAPTURED;
}