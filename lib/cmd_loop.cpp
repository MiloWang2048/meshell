#include "meshell.h"

void printPrompt();

int cmd_loop() {
    printPrompt();
    string cmd;
    getline(cin, cmd);
    return execute_cmd(cmd);
}

void printPrompt() {
    string cwd = getcwd(NULL, 0);
    string hostName =
        getNotNULLString(3, getenv("HOSTNAME"), getenv("HOST"), getenv("NAME"));
    string userName = getenv("LOGNAME");
    // \e[xxm changes terminal font color. 34: fore-blue, 32: fore-green, 0:
    // default.
    cout << "\e[34m" << userName << "@" << hostName << "\e[0m:\e[32m" << cwd
         << "\e[0m$ ";
}