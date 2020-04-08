// header files
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using namespace std;

// utilities.cpp
int cmd_loop();
string getNotNULLString(int num, ...);
int execute_cmd(string cmd);