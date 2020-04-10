// c header files
#include <unistd.h>

// cpp header files
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

// namespaces
using namespace std;

// structures
typedef struct MeshConfig {
  string username;
  string hostname;
} MeshConfig;

// enums
enum MeshStatus {
  RETURN_SUCCESS,
  RETURN_FAIL,
  SIGNAL_EXIT
};
enum CommandStatus {
  CMD_CAPTURED,
  CMD_FALLTHROUGH
};

// aliases
typedef vector<string> Args;

// global vars
extern char** environ;

// utilities
string getNotNULLString(int num, ...);
char getch(void);

// life cycle
MeshStatus cmd_loop(MeshConfig* config);
MeshStatus execute_cmd(MeshConfig* config, string cmd);
MeshStatus loadConfig(MeshConfig* config);

// built in commands
CommandStatus built_in_cmds(MeshConfig* config, Args args);