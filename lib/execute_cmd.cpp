#include "meshell.h"

vector<string> splitCommand(string cmd);

int execute_cmd(string cmd) {
  vector<string> args = splitCommand(cmd);
  vector<string>::iterator p = args.begin();
  while (p != args.end()) {
    cout << *p << endl;
    p++;
  }
  return EXIT_SUCCESS;
}

vector<string> splitCommand(string cmd) {
  vector<string> args;
  string::iterator wordStart, wordEnd;
  wordStart = wordEnd = cmd.begin();
  while (wordStart != cmd.end() && wordEnd != cmd.end()) {
    while ((isspace(*wordStart)) && (wordStart != cmd.end()))
      wordStart++;
    wordEnd = wordStart;
    while ((wordEnd != cmd.end()) && (!isspace(*wordEnd)))
      wordEnd++;
    if (wordStart != wordEnd)
      args.push_back(cmd.substr(wordStart - cmd.begin(), wordEnd - cmd.begin()));
    wordStart = wordEnd;
  }
  return args;
}