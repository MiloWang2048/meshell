// c header files
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// cpp header files
#include <algorithm>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <fstream>
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
void splashPrint();
char** stringVectorToCharMatrix(Args args);
void freeCharMatrix(char** m);

// life cycle
MeshStatus cmd_loop(MeshConfig* config);
MeshStatus execute_cmd(MeshConfig* config, string cmd);
MeshStatus loadConfig(MeshConfig* config);

// command handlers
CommandStatus built_in_cmds(MeshConfig* config, Args& args);
CommandStatus outer_cmds(MeshConfig* config, Args& args);

// io redirection
typedef struct RedirectParams {
  ifstream* infile = NULL;
  ofstream* outfile = NULL;
  streambuf* stdinBackup = NULL;
  streambuf* stdoutBackup = NULL;
} RedirectParams;

MeshStatus handle_redirect(Args& args, RedirectParams& params);
void restore_std_stream(RedirectParams& params);