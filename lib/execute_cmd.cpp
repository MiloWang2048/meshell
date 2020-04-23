#include "meshell.h"

Args splitCommand(string cmd);

MeshStatus execute_cmd(MeshConfig* config, string cmdString) {
  Args args = splitCommand(cmdString);
  MeshStatus status = RETURN_SUCCESS;
  if (args.size() == 0)
    status = RETURN_SUCCESS;
  else if (args[0] == "exit")
    status = SIGNAL_EXIT;
  else if (args[args.size() - 1] == "&") {
    status = bg_cmd_sequence(config, args);
  } else {
    status = cmd_sequence(config, args);
  }
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
