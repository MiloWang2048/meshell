#include "meshell.h"

Args splitCommand(string cmd);

MeshStatus execute_cmd(MeshConfig* config, string cmdString) {
  Args args = splitCommand(cmdString);
  if (args.size() == 0)
    return RETURN_SUCCESS;
  if (args[0] == "exit")
    return SIGNAL_EXIT;
  CommandStatus stat = built_in_cmds(config, args);
  //puts(stat == CMD_FALLTHROUGH ? "falltrough" : "captured");
  if (stat == CMD_FALLTHROUGH) {
    stat = outer_cmds(config, args);
  }
  return RETURN_SUCCESS;
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