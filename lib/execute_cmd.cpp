#include "meshell.h"

Args splitCommand(string cmd);
MeshStatus cmd_sequece(MeshConfig* config, Args& args);
MeshStatus bg_cmd_sequece(MeshConfig* config, Args& args);

MeshStatus execute_cmd(MeshConfig* config, string cmdString) {
  Args args = splitCommand(cmdString);
  RedirectParams redirectParams;
  MeshStatus status = handle_redirect(args, redirectParams);
  if (args.size() == 0)
    status = RETURN_SUCCESS;
  else if (args[0] == "exit")
    status = SIGNAL_EXIT;
  else if (args[args.size() - 1] == "&") {
    status = bg_cmd_sequece(config, args);
  } else {
    status = cmd_sequece(config, args);
  }
  restore_std_stream(redirectParams);
  return status;
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

MeshStatus cmd_sequece(MeshConfig* config, Args& args) {
  CommandStatus stat = built_in_cmds(config, args);
  //puts(stat == CMD_FALLTHROUGH ? "falltrough" : "captured");
  if (stat == CMD_FALLTHROUGH) {
    stat = outer_cmds(config, args);
  }

  return RETURN_SUCCESS;
}

MeshStatus bg_cmd_sequece(MeshConfig* config, Args& args) {
  args.erase(args.end() - 1);
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