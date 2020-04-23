#include <dirent.h>

#include "meshell.h"

CommandStatus mesh_cd(MeshConfig* config, Args& args);
CommandStatus mesh_echo(MeshConfig* config, Args& args);
CommandStatus mesh_ls(MeshConfig* config, Args& args);
CommandStatus mesh_clear(MeshConfig* config, Args& args);
CommandStatus mesh_env(MeshConfig* config, Args& args);
CommandStatus mesh_help(MeshConfig* config, Args& args);

CommandStatus built_in_cmds(MeshConfig* config, Args& args) {
  string cmd = args[0];
  if (cmd == "cd") {
    return mesh_cd(config, args);
  } else if (cmd == "echo") {
    return mesh_echo(config, args);
  } else if (cmd == "ls") {
    return mesh_ls(config, args);
  } else if (cmd == "clear") {
    return mesh_clear(config, args);
  } else if (cmd == "env") {
    return mesh_env(config, args);
  } else if (cmd == "help") {
    return mesh_help(config, args);
  } else if (cmd == "pause") {
    cout << "press any key to continue" << endl;
    getch();
    return CMD_CAPTURED;
  } else
    return CMD_FALLTHROUGH;
}

CommandStatus mesh_cd(MeshConfig* config, Args& args) {
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

CommandStatus mesh_echo(MeshConfig* config, Args& args) {
  for (int i = 1; i < args.size(); i++) {
    cout << args[i] << endl;
  }
  return CMD_CAPTURED;
}

CommandStatus mesh_ls(MeshConfig* config, Args& args) {
  DIR* dir;
  struct dirent* ptr;
  int i;
  const char* path = (args.size() == 1) ? getcwd(NULL, 0) : args[1].c_str();
  dir = opendir(path);
  if (!dir) {
    puts("directory not exist.");
    return CMD_CAPTURED;
  }
  while ((ptr = readdir(dir)) != NULL) {
    printf("%s\n", ptr->d_name);
  }
  closedir(dir);
  return CMD_CAPTURED;
}

CommandStatus mesh_clear(MeshConfig* config, Args& args) {
  fflush(stdout);
  printf("\x1b[2J\x1b[H");
  return CMD_CAPTURED;
}

CommandStatus mesh_env(MeshConfig* config, Args& args) {
  char** p = environ;
  while (*p) {
    puts(*p);
    p++;
  }
  return CMD_CAPTURED;
}

CommandStatus mesh_help(MeshConfig* config, Args& args) {
  ifstream file("./resources/help.txt");
  string helpText;
  while (!file.eof()) {
    getline(file, helpText);
    cout << helpText << endl;
  }
  file.close();
  return CMD_CAPTURED;
}