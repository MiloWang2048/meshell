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

// macros
#define SIGNAL_EXIT -1

// structures
typedef struct MeshConfig {
  string cwd;
  string username;
  string hostname;
} MeshConfig;

// functions
int cmd_loop(MeshConfig* config);
string getNotNULLString(int num, ...);
int execute_cmd(string cmd);
void loadConfig(MeshConfig* config);