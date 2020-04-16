#include "meshell.h"

Args splitCommand(string cmd);
MeshStatus cmd_sequece(MeshConfig* config, Args args);
MeshStatus bg_cmd_sequece(MeshConfig* config, Args args);

MeshStatus execute_cmd(MeshConfig* config, string cmdString) {
  Args args = splitCommand(cmdString);
  if (args.size() == 0)
    return RETURN_SUCCESS;
  if (args[0] == "exit")
    return SIGNAL_EXIT;
  if (args[args.size() - 1] == "&") {
    // backgroud task
    Args newArgs = args;
    newArgs.erase(newArgs.end() - 1);
    bg_cmd_sequece(config, newArgs);
  } else {
    // foreground task
    return cmd_sequece(config, args);
  }
}

Args splitCommand(string cmdString) {
  Args args;
  int wordStart = 0, wordEnd = 0, size = cmdString.size();
  while (wordStart != size && wordEnd != size) {
    while ((isspace(cmdString[wordStart])) && (wordStart != size))
      wordStart++;
    wordEnd = wordStart;
    while ((wordEnd != size) && (!isspace(cmdString[wordEnd])))
      wordEnd++;
    if (wordStart != wordEnd) {
      args.push_back(cmdString.substr(wordStart, wordEnd - wordStart));
    }
    wordStart = wordEnd;
  }
  return args;
}

MeshStatus cmd_sequece(MeshConfig* config, Args args) {
  CommandStatus stat = built_in_cmds(config, args);
  //puts(stat == CMD_FALLTHROUGH ? "falltrough" : "captured");
  if (stat == CMD_FALLTHROUGH) {
    stat = outer_cmds(config, args);
  }
}

MeshStatus bg_cmd_sequece(MeshConfig* config, Args args) {
  pid_t pid = fork();
  if (pid == 0) {
    // child
    MeshStatus stat = cmd_sequece(config, args);
    exit(stat);
  } else if (pid < 0) {
    // error
    puts("error: cannot fork");
    return RETURN_FAIL;
  } else {
    // parent
    return RETURN_SUCCESS;
  }
  return RETURN_SUCCESS;
}