// header files
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// global macros
#define EXIT_FAIL -1
#define EXIT_SUCCESS 0

// utilities.cpp
int cmd_loop();
char* getNotNULLString(int num, ...);